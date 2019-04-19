#ifndef CREME_WIDGET_LABEL_H
#define CREME_WIDGET_LABEL_H

#include "area.h"
#include "size.h"

struct cm_tileset;
struct cm_render_queue;

typedef struct cm_size (* cm_text_size_fn)(const char * text, void * priv);

struct cmw_label {
  struct cm_area area;
  struct cm_value text_width;
  struct cm_value text_height;
  char const * text;
  void * priv;
  cm_text_size_fn text_size_fn;
};

extern void cmw_label_construct(struct cmw_label * label);
extern void cmw_label_set_text(struct cmw_label * label, char const * text);
extern char const * cwm_label_get_text(struct cmw_label * label);

extern void cmw_label_set_size_fn(
  struct cmw_label * label,
  cm_text_size_fn text_size_fn,
  void * priv
);

extern uint16_t cmw_label_render(
  struct cmw_label const * label,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
);

#endif
