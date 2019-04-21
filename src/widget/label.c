#include "widget/label.h"
#include "render-command.h"
#include "render-queue.h"
#include <stdlib.h>

void cmw_label_update_text_size(struct cmw_label * label);

void cmw_label_construct(struct cmw_label * label) {
  cm_area_construct(&label->area);
  cm_value_construct(&label->text_width);
  cm_value_construct(&label->text_height);
  label->text_size_fn_data = NULL;
  label->text = NULL;
  label->text_size_fn = NULL;
}

void cmw_label_set_text(struct cmw_label * label, char const * text) {
  label->text = text;
  cmw_label_update_text_size(label);
}

void cmw_label_update_text_size(struct cmw_label * label) {
  if (label->text_size_fn == NULL) return;
  struct cm_size size = label->text_size_fn(label->text, label->text_size_fn_data);
  cm_value_set(&label->text_width, size.width);
  cm_value_set(&label->text_height, size.height);
}

void
cmw_label_set_size_fn(
  struct cmw_label * label,
  cm_text_size_fn text_size_fn,
  void * text_size_fn_data
) {
  label->text_size_fn = text_size_fn;
  label->text_size_fn_data = text_size_fn_data;
  cmw_label_update_text_size(label);
}

char const * cmw_label_get_text(struct cmw_label * label) {
  return label->text;
}

uint16_t
cmw_label_render(
  struct cmw_label const * label,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
) {
  (void) tileset;
  struct cm_render_command cmd;
  cm_render_command_construct(&cmd);
  cm_render_command_set_text(
    &cmd,
    label->text,
    cm_size_make(
      cm_value_get(&label->text_width),
      cm_value_get(&label->text_height)
    ),
    cm_area_to_rect(&label->area)
  );
  cm_render_queue_enqueue(queue, &cmd);
  return 1;
}

