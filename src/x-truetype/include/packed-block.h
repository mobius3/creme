#ifndef CREME_EXTRAS_TRUETYPE_PACKED_BLOCK_H
#define CREME_EXTRAS_TRUETYPE_PACKED_BLOCK_H

#include "character-mapping.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This structure is internally used to represent a block packed inside a
 * `cmx_truetype_font` value.
 */
struct cmx_truetype_packed_block {
  uint32_t first;
  uint32_t last;
  struct cmx_truetype_character_mapping * mapping;
};

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_TRUETYPE_PACKED_BLOCK_H */
