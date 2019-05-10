#ifndef CREME_EXTRAS_TRUETYPE_FONT_SIZE_H
#define CREME_EXTRAS_TRUETYPE_FONT_SIZE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Used to tell if a `cmx_truetype_size` value is specified in pixels or in points
 */
enum cmx_truetype_font_size_type {
  cmx_truetype_size_type__pt,
  cmx_truetype_size_type__px
};

/**
 * Specifies the size of a font either in pixels or in points
 */
struct cmx_truetype_font_size {
  float value;
  enum cmx_truetype_font_size_type type;
};

/**
 * Constructs and returns a `cmx_truetype_size` value specified as points
 * @param value The size in floats
 * @return A `cmx_truetype_size` value using `cmx_truetype_size_type__pt`
 */
extern struct cmx_truetype_font_size cmx_truetype_font_size_pt(float value);

/**
 * Constructs and returns a `cmx_truetype_size` value specified as pixels
 * @param value The size in floats
 * @return A `cmx_truetype_size` value using `cmx_truetype_size_type__px`
 */
extern struct cmx_truetype_font_size cmx_truetype_font_size_px(float value);

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_TRUETYPE_FONT_SIZE_H */
