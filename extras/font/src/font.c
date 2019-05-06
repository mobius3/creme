#include "font.h"
#include "stb_truetype.h"
#include <math.h>

void cmx_font_colorify(
  unsigned char * old_pixels,
  unsigned char * new_pixels,
  struct cm_size dimensions,
  struct cm_color color
);

/* http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 */
static unsigned long upper_power_of_two(unsigned long v) {
  v--;
  v |= v >> 1U;
  v |= v >> 2U;
  v |= v >> 4U;
  v |= v >> 8U;
  v |= v >> 16U;
  v++;
  return v;
}

struct cm_size cmx_font_calculate_pixel_buffer_size(
  struct cmx_font_unicode_block * blocks,
  size_t block_count,
  float font_height
) {
  int i = 0;
  float expected_size = 0;
  for (i = 0; i < block_count; i++) {
    expected_size +=
      (blocks[i].last - blocks[i].first);
  }
  expected_size *= font_height * font_height;
  struct cm_size size = {
    .width = (float) sqrt(upper_power_of_two((int) expected_size)),
    .height = size.width
  };
  return size;
}

void cmx_font_construct(
  struct cmx_font * font,
  unsigned char const * font_data,
  struct cmx_font_size font_size,
  struct cm_color font_color
) {
  font->metadata.font_data = font_data;
  font->metadata.size = font_size;
  font->metadata.color = font_color;
  font->pixels.data = NULL;
  font->pixels.dimensions.width = font->pixels.dimensions.height = .0f;
  font->packing.packed_block_count = 0;
  font->packing.packed_blocks = NULL;
  font->metadata.data = malloc(sizeof(stbtt_fontinfo));
  stbtt_InitFont(font->metadata.data, font->metadata.font_data, 0);
}

void cmx_font_pack(
  struct cmx_font * font,
  struct cmx_font_unicode_block blocks[],
  size_t block_count
) {
  stbtt_pack_context pack_context;
  struct cm_size dimensions = cmx_font_calculate_pixel_buffer_size(
    blocks,
    block_count,
    font->metadata.size.value
  );
  size_t pixel_count = (size_t) (dimensions.width * dimensions.height);
  unsigned char * pixels_1bpp = malloc(pixel_count);
  unsigned char * pixels_4bpp = malloc(pixel_count * 4);

  stbtt_pack_range * ranges = malloc(sizeof(*ranges) * block_count);
  float size = font->metadata.size.value;
  if (font->metadata.size.type == cmx_font_size_type__pt)
    size = STBTT_POINT_SIZE(size);

  font->packing.packed_blocks = malloc(
    sizeof *(font->packing.packed_blocks) * block_count
  );
  font->packing.packed_block_count = block_count;

  int i = 0;
  size_t char_count_in_block;
  for (i = 0; i < block_count; i++) {
    char_count_in_block = blocks[i].count;
    font->packing.packed_blocks[i].first = blocks[i].first;
    font->packing.packed_blocks[i].last = blocks[i].last;
    font->packing.packed_blocks[i].mapping = malloc(
      sizeof(struct cmx_font_character_mapping) * (char_count_in_block)
    );

    ranges[i].font_size = size;
    ranges[i].array_of_unicode_codepoints = NULL;
    ranges[i].first_unicode_codepoint_in_range = blocks[i].first;
    ranges[i].num_chars = char_count_in_block;
    ranges[i].chardata_for_range = malloc(
      sizeof(stbtt_packedchar) * (char_count_in_block));
  }

  stbtt_PackBegin(
    &pack_context, pixels_1bpp,
    (int) dimensions.width, (int) dimensions.height,
    0, 1, NULL
  );
  stbtt_PackFontRanges(&pack_context, font->metadata.font_data, 0, ranges, block_count);

  /* map all the stbtt_packedchar to render_mapping */
  for (i = 0; i < block_count; i++) {
    struct cmx_font_packed_block * packed_block = &font->packing.packed_blocks[i];
    struct cmx_font_character_mapping * mappings = packed_block->mapping;
    stbtt_packedchar * chardata = ranges[i].chardata_for_range;

    int character = 0;
    for (character = 0; character < (packed_block->last - packed_block->first); character++) {
      float x = 0, y = 0;
      stbtt_aligned_quad quad;
      struct cmx_font_character_mapping * mapping = &mappings[character];
      struct cm_rect * src = &mapping->source;
      struct cm_rect * dst = &mapping->target;
      stbtt_GetPackedQuad(
        chardata,
        (int) dimensions.width,
        (int) dimensions.height,
        character,
        &x,
        &y,
        &quad,
        1
      );

      src->left = quad.s0;
      src->top = quad.t0;
      src->right = quad.s1;
      src->bottom = quad.t1;
      /* empty characters seems to not be returning a valid target, compute
       * from x and y */
      if (quad.x1 - quad.x0 == 0.0f) quad.x1 = x;
      if (quad.y1 - quad.y0 == 0.0f) quad.y1 = y;

      dst->left = quad.x0;
      dst->top = font->metadata.size.value + quad.y0;
      dst->right = quad.x1;
      dst->bottom = dst->top + (quad.y1 - quad.y0);
    }

    free(chardata);
  }


  stbtt_PackEnd(&pack_context);

  cmx_font_colorify(pixels_1bpp, pixels_4bpp, dimensions, font->metadata.color);

  font->pixels.data = pixels_4bpp;
  font->pixels.dimensions = dimensions;
  free(ranges);
  free(pixels_1bpp);
}

void cmx_font_destruct(struct cmx_font * font) {
  free(font->pixels.data);
  free(font->metadata.data);
  int i = 0;
  for (i = 0; i < font->packing.packed_block_count; i++) {
    free(font->packing.packed_blocks[i].mapping);
  }
  free(font->packing.packed_blocks);
}

/* converts 1bpp pixels generated by stbtt to 4bpp, applying the color value */
void cmx_font_colorify(
  unsigned char * old_pixels,
  unsigned char * new_pixels,
  struct cm_size dimensions,
  struct cm_color color
) {
  unsigned char * src;
  unsigned char * dst;

  int i = 0, j = 0,
    w = (int) dimensions.width, h = (int) dimensions.height;

  for (j = 0; j < h; ++j) {
    src = old_pixels + j * w;
    dst = new_pixels + j * w * 4;
    for (i = w - 1; i >= 0; --i, src += 1, dst += 4) {
      dst[0] = color.r;
      dst[1] = color.g;
      dst[2] = color.b;
      dst[3] = src[0];
    }
  }
}

struct cmx_font_packed_block *
cmx_font_locate_block(struct cmx_font const * font, uint32_t point) {
  int i;
  for (i = 0; i < font->packing.packed_block_count; i++) {
    if (point >= font->packing.packed_blocks[i].first &&
        point <= font->packing.packed_blocks[i].last)
      return &font->packing.packed_blocks[i];
  }
  return NULL;
}

static float get_kern(struct cmx_font const * font, uint32_t ch1, uint32_t ch2) {
  float scale = 0;
  if (font->metadata.size.type == cmx_font_size_type__pt) {
    scale = stbtt_ScaleForMappingEmToPixels(font->metadata.data, font->metadata.size.value);
  } else {
    scale = stbtt_ScaleForPixelHeight(font->metadata.data, font->metadata.size.value);
  }
  return scale * stbtt_GetCodepointKernAdvance(font->metadata.data, ch1, ch2);
}

void cmx_font_render(
  struct cmx_font const * font,
  char const * text,
  size_t text_length,
  struct cmx_font_character_mapping mapping[]
) {
  int i = 0;
  struct cmx_font_packed_block * block;
  float x = 0;
  float expected_height = 0.0f, offset_height;

  /* the following loop calculates the maximum character height and then creates
   * an offset to be used when rendering. We cannot use the actual size because
   * that can be much higher than the actual rendering height. */
  for (i = 0; i < text_length; i++) {
    block = cmx_font_locate_block(font, text[i]);
    int mapping_buffer_index = text[i] - block->first;
    float current_height = cm_rect_height(&block->mapping[mapping_buffer_index].target);
    if (current_height > expected_height) expected_height = current_height;
  }
  offset_height = font->metadata.size.value - expected_height;

  float kern = 0;
  for (i = 0; i < text_length; i++) {
    block = cmx_font_locate_block(font, text[i]);
    struct cmx_font_character_mapping * source_mapping = block->mapping;
    int mapping_buffer_index = text[i] - block->first;

    mapping[i].source = source_mapping[mapping_buffer_index].source;
    mapping[i].target = source_mapping[mapping_buffer_index].target;
    mapping[i].target.left += x + kern;
    mapping[i].target.right += x + kern;
    mapping[i].target.top -= offset_height;
    mapping[i].target.bottom -= offset_height;
    x += cm_rect_width(&source_mapping[mapping_buffer_index].target);
    if (i + 1 < text_length) kern += get_kern(font, text[i], text[i + 1]);
  }
}

struct cm_size cmx_font_text_size(struct cmx_font const * font, const char * text, size_t text_length) {
  int i = 0;
  struct cmx_font_packed_block * block;
  struct cm_size result = {0, 0};
  float min_top = 0.0f, max_bottom = 0.0f;

  float total_kern = 0;
  for (i = 0; i < text_length; i++) {
    block = cmx_font_locate_block(font, text[i]);
    struct cmx_font_character_mapping * source_mapping = block->mapping;
    int mapping_buffer_index = text[i] - block->first;
    struct cm_rect * target = &source_mapping[mapping_buffer_index].target;
    if (target->top < min_top || i == 0) min_top = target->top;
    if (target->bottom > max_bottom || i == 0) max_bottom = target->bottom;
    result.width += cm_rect_width(&source_mapping[mapping_buffer_index].target);
    if (i + 1 < text_length) total_kern += get_kern(font, text[i], text[i+1]);
  }

  result.width += total_kern;
  result.height = max_bottom - min_top;
  return result;
}