#ifndef CREME_EXTRAS_FONT_PACKED_BLOCK_H
#define CREME_EXTRAS_FONT_PACKED_BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This structure is internally used to represent a block packed inside a
 * `cmx_font` value.
 */
struct cmx_font_packed_block {
  uint32_t first;
  uint32_t last;
  struct cmx_font_character_mapping * mapping;
};

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_FONT_PACKED_BLOCK_H */
