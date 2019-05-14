#ifndef CREME_WIDGET_BUTTON_H
#define CREME_WIDGET_BUTTON_H

#include "creme-core.h"
#include "label.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cmw_button {
  struct cm_area area;
  struct cmw_label label;
};

WIDGETS_API extern void cmw_button_construct(struct cmw_button * button);

WIDGETS_API extern void cmw_button_set_text(
  struct cmw_button * button,
  unsigned char const * text
);

WIDGETS_API extern unsigned char const *
cwm_button_get_text(struct cmw_button * button);

WIDGETS_API extern void cmw_button_set_label_size_fn(
  struct cmw_button * button,
  cm_text_size_fn text_size_fn,
  void * text_size_fn_data
);

WIDGETS_API extern uint16_t cmw_button_render(
  struct cmw_button const * button,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
);

#ifdef __cplusplus
}
#endif

#endif /* CREME_WIDGET_BUTTON_H */
