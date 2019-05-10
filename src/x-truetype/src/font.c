#include "font.h"
#include "stb_truetype.h"
#include "utf8-decode.h"
#include <math.h>

void cmx_truetype_colorify(
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

struct cm_size cmx_truetype_calculate_pixel_buffer_size(
  struct cmx_truetype_unicode_block * blocks,
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

void cmx_truetype_font_construct(
  struct cmx_truetype_font * font,
  unsigned char const * font_data,
  struct cmx_truetype_font_size font_size,
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

void cmx_truetype_font_pack(
  struct cmx_truetype_font * font,
  struct cmx_truetype_unicode_block * blocks,
  size_t block_count
) {
  stbtt_pack_context pack_context;
  struct cm_size dimensions = cmx_truetype_calculate_pixel_buffer_size(
    blocks,
    block_count,
    font->metadata.size.value
  );
  size_t pixel_count = (size_t) (dimensions.width * dimensions.height);
  unsigned char * pixels_1bpp = malloc(pixel_count);
  unsigned char * pixels_4bpp = malloc(pixel_count * 4);

  stbtt_pack_range * ranges = malloc(sizeof(*ranges) * block_count);
  float size = font->metadata.size.value;
  if (font->metadata.size.type == cmx_truetype_size_type__pt)
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
      sizeof(struct cmx_truetype_character_mapping) * (char_count_in_block)
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

  /* map all the stbtt_packedchar to character_mapping */
  for (i = 0; i < block_count; i++) {
    struct cmx_truetype_packed_block * packed_block = &font->packing.packed_blocks[i];
    struct cmx_truetype_character_mapping * mappings = packed_block->mapping;
    stbtt_packedchar * chardata = ranges[i].chardata_for_range;

    int character = 0;
    for (character = 0; character < (packed_block->last - packed_block->first); character++) {
      float x = 0, y = 0;
      stbtt_aligned_quad quad;
      struct cmx_truetype_character_mapping * mapping = &mappings[character];
      struct cm_rect * src = &mapping->source;
      struct cm_rect * dst = &mapping->target;
      stbtt_GetPackedQuad(
        chardata,
        (int) dimensions.width, (int) dimensions.height,
        character, &x, &y, &quad, 1
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
      dst->top = quad.y0;
      dst->right = quad.x1;
      dst->bottom = quad.y1;
    }

    free(chardata);
  }
  stbtt_PackEnd(&pack_context);

  cmx_truetype_colorify(pixels_1bpp, pixels_4bpp, dimensions, font->metadata.color);

  font->pixels.data = pixels_4bpp;
  font->pixels.dimensions = dimensions;
  free(ranges);
  free(pixels_1bpp);
}

void cmx_truetype_font_destruct(struct cmx_truetype_font * font) {
  free(font->pixels.data);
  free(font->metadata.data);
  int i = 0;
  for (i = 0; i < font->packing.packed_block_count; i++) {
    free(font->packing.packed_blocks[i].mapping);
  }
  free(font->packing.packed_blocks);
}

/* converts 1bpp pixels generated by stbtt to 4bpp, applying the color value */
void cmx_truetype_colorify(
  unsigned char * old_pixels,
  unsigned char * new_pixels,
  struct cm_size dimensions,
  struct cm_color color
) {
  unsigned char * src;
  unsigned char * dst;

  int i = 0, j = 0,
      w = (int) dimensions.width,
      h = (int) dimensions.height;

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

struct cmx_truetype_packed_block *
cmx_truetype_locate_block(struct cmx_truetype_font const * font, uint32_t point) {
  int i;
  for (i = 0; i < font->packing.packed_block_count; i++) {
    if (point >= font->packing.packed_blocks[i].first &&
        point <= font->packing.packed_blocks[i].last)
      return &font->packing.packed_blocks[i];
  }
  return NULL;
}

static float get_kern(struct cmx_truetype_font const * font, uint32_t ch1, uint32_t ch2) {
  float scale = 0;
  if (font->metadata.size.type == cmx_truetype_size_type__pt) {
    scale = stbtt_ScaleForMappingEmToPixels(font->metadata.data, font->metadata.size.value);
  } else {
    scale = stbtt_ScaleForPixelHeight(font->metadata.data, font->metadata.size.value);
  }
  return scale * stbtt_GetCodepointKernAdvance(font->metadata.data, ch1, ch2);
}

int cmx_truetype_font_render(
  struct cmx_truetype_font const * font,
  unsigned char const * text,
  size_t text_length,
  struct cmx_truetype_character_mapping * mapping
) {
  int i = 0, target_index = 0, source_index = 0;
  struct cmx_truetype_packed_block * block;
  float x = 0, kern = 0, top_offset = 0.0f;
  struct utf8_decode_result decode;

  /* decode all utf8 characters into unicode codepoints, find their
   * block, gets their rendering parameters, adds kerning */
  for (i = 0; i < text_length; i += decode.skip, target_index++) {
    decode = utf8_decode(text + i, text_length -i);

    block = cmx_truetype_locate_block(font, decode.codepoint);
    /* skips half the pixel "height" if block was not found */
    if (block == NULL) {
      x += font->metadata.size.value/2;
      continue;
    }

    /* gets the mapping done by cmx_truetype_font_pack and copies it into the result */
    struct cmx_truetype_character_mapping * source_mapping = block->mapping;
    source_index = decode.codepoint - block->first;
    mapping[target_index].source = source_mapping[source_index].source;
    mapping[target_index].target = source_mapping[source_index].target;
    mapping[target_index].target.left += x + kern;
    mapping[target_index].target.right += x + kern;

    /* stores the top offset to add it later to the mappings, to make sure
     * that rendering starts at 0 */
    if ((mapping[target_index].target.top < top_offset) || target_index == 0)
      top_offset = mapping[target_index].target.top;

    /* advances to the next character position */
    x += cm_rect_width(&source_mapping[source_index].target);

    /* checks to see if there is kerning to add to the next character, and
     * sets it to be used in the next iteration */
    if (i + decode.skip < text_length) {
      struct utf8_decode_result next = utf8_decode(text + i + decode.skip, text_length - (i + decode.skip));
      kern += get_kern(font, decode.codepoint, next.codepoint);
    }
  }

  /* characters are rendered around a baseline, which was set to 0 when
   * cmx_truetype_font_pack was called. the following loop goes through all glyph
   * mappings and adjusts them to remove the "empty" space on top caused
   * by that. */
  top_offset = fabs(top_offset);
  for (i = 0; i < target_index; i++) {
    mapping[i].target.top += top_offset;
    mapping[i].target.bottom += top_offset;
  }

  /* end of the loop, target_index will be the amount of decoded glyphs */
  return target_index;
}

struct cm_size cmx_truetype_text_size(struct cmx_truetype_font const * font, unsigned char const * text, size_t text_length) {
  /* renders the text to a temporary mapping then use that to calculate
   * text width and height */
  struct cmx_truetype_character_mapping * mapping = malloc(sizeof(*mapping) * text_length);
  int i = 0, total_glyphs = cmx_truetype_font_render(
    font,
    text,
    text_length,
    mapping
  );
  struct cm_size result = {0, 0};
  if (total_glyphs == 0) return result;

  struct cm_rect * target = &mapping[i].target;
  struct cm_rect bounds = *target;
  for (i = 1; i < total_glyphs; i++) {
    target = &mapping[i].target;
    if (target->left < bounds.left) bounds.left = target->left;
    if (target->top < bounds.top) bounds.top = target->top;
    if (target->right > bounds.right) bounds.right = target->right;
    if (target->bottom > bounds.bottom) bounds.bottom = target->bottom;
  }

  result.width = cm_rect_width(&bounds);
  result.height = cm_rect_height(&bounds);

  /* some characters have a base x start that is not 0. this code takes care of
   * that by adding the starting amount to the width */
  if (bounds.left != 0.0f) result.width += fabs(bounds.left);
  free(mapping);
  return result;
}