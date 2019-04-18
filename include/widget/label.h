#ifndef CREME_WIDGET_LABEL_H
#define CREME_WIDGET_LABEL_H

#include "area.h"
#include "size.h"

struct cm_tileset;
struct cm_render_queue;

typedef struct cm_size (* cm_text_size_fn)(const char * text, void * priv);

struct cmw_label {
  struct cm_area area;
  char const * text;
  void * priv;
  cm_text_size_fn text_size_fn;
};

void cmw_label_construct(struct cmw_label * label);
void cmw_label_set_text(struct cmw_label * label, char const * text);
char const * cwm_label_get_text(struct cmw_label * label);

void cmw_label_set_size_fn(
  struct cmw_label * label,
  cm_text_size_fn text_size_fn,
  void * priv
);

void cmw_label_render(
  struct cmw_label const * label,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
);

#endif
