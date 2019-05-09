#ifndef CREME_EXTRAS_TRUETYPE_FONT_H
#define CREME_EXTRAS_TRUETYPE_FONT_H

#include <stdlib.h>
#include <stdint.h>

#include "rect.h"
#include "size.h"
#include "color.h"

#include "unicode-block.h"
#include "font-size.h"
#include "character-mapping.h"
#include "packed-block.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A cmx_truetype_font struct represents all data and metadata about a font and it's
 * pixels at a certain font size and color. It should be treated as an opaque
 * structure.
 */
struct cmx_truetype_font {
  struct {
    unsigned char const * font_data;
    struct cmx_truetype_font_size size;
    struct cm_color color;
    void * data;
  } metadata;

  struct {
    struct cmx_truetype_packed_block * packed_blocks;
    size_t packed_block_count;
  } packing;

  struct {
    unsigned char * data;
    struct cm_size dimensions;
  } pixels;
};

/**
 * Constructs a `cmx_truetype_font` value with a font data,
 * a size (either in pixels or points) and a font color in RGBA.
 * It does not have any pixel data yet, you
 * need to call cmx_truetype_pack to add unicode ranges and produce a 4 bytes
 * per pixel, RGBA, bitmap.
 * @param font A pointer to the `cmx_truetype_font` value to construct
 * @param font_data A pointer to the in-memory font-data (it will NOT be managed
 *                  nor free'd by creme).
 * @param font_size A size either in pixels or points to apply when packing
 * @param font_color The color of the characters in the rendered bitma[
 */
extern void cmx_truetype_font_construct(
  struct cmx_truetype_font * font,
  unsigned char const * font_data,
  struct cmx_truetype_font_size font_size,
  struct cm_color font_color
);

/**
 * Packs the given unicode blocks, producing a bitmap containing all glyphs
 * in the specified range. You must do this before calling `cmx_truetype_render`.
 *
 * Note that calling this function multiple times will *replace* the current
 * packing instead of adding more to it.
 * @param font A pointer to the `cmx_truetype_font` instance
 * @param blocks An array of unicode blocks to pack
 * @param block_count How many unicode blocks are in the array
 */
extern void cmx_truetype_font_pack(
  struct cmx_truetype_font * font,
  struct cmx_truetype_unicode_block * blocks,
  size_t block_count
);

/**
 * Produces a list of source and target rectangles that can be used as clipping
 * rects (or UV maps) for the source texture and as space coordinates.
 *
 * This function uses data produced by `cmx_truetype_font_pack` and
 * information inside
 * the font data to map all the characters passed in to a list of source and
 * target coordinates. It also takes in consideration the kerning for each
 * character pair.
 *
 * Also observe that the source rect is in pixel coordinates (from 0,0 to w,h),
 * not from 0 to 1.
 *
 * @param font A pointer to a `cmx_truetype_font` value that will be used
 * @param text A pointer to a character array containing the text to map
 * @param text_length How many bytes are there in the text array
 * @param mapping An array of `cmx_truetype_character_mapping` values that
 *                       must be at least `text_length` long.
 * @return the actual number of glyphs rendered.
 */
extern int cmx_truetype_font_render(
  struct cmx_truetype_font const * font,
  unsigned char const * text,
  size_t text_length,
  struct cmx_truetype_character_mapping * mapping
);

/**
 * Returns the expected width and height of a text rendering with the given font.
 * @param font A pointer to a `cmx_truetype_font` value
 * @param text A pointer to the character sequence containing the text
 * @param text_length The length of the text (in bytes, not in characters)
 * @return A `cm_size` value containing width and height
 */
extern struct cm_size cmx_truetype_text_size(
  struct cmx_truetype_font const * font,
  unsigned const char * text,
  size_t text_length
);

/**
 * Destroys and frees all memory allocated by this library. You *must* call
 * this once done with a `cmx_truetype_font` value else your memory will leak.
 * @param font Pointer to the `cmx_truetype_font` value that will be destroyed.
 */
extern void cmx_truetype_font_destruct(struct cmx_truetype_font * font);

#ifdef __cplusplus
};
#endif

#endif