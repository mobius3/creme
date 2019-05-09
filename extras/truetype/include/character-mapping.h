#ifndef CREME_EXTRAS_TRUETYPE_CHARACTER_MAPPING_H
#define CREME_EXTRAS_TRUETYPE_CHARACTER_MAPPING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Specifies an unicode character mapping in terms of source texture and target
 * destination (screen or world-space).
 */
struct cmx_truetype_character_mapping {
  struct cm_rect source;
  struct cm_rect target;
};

#ifdef __cplusplus
}

#endif

#endif /* CREME_EXTRAS_TRUETYPE_CHARACTER_MAPPING_H */
