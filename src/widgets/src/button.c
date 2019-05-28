#include <tileset.h>
#include "button.h"

void cmw_button_construct(struct cmw_button * button) {
  cm_area_construct(&button->area);
  cm_area_set_tag(&button->area, "  btn");
  cmw_label_construct(&button->label);
  button->state = cmw_button__state_normal;
  cm_area_center_at(
    &button->label.area,
    &button->area.center.x,
    &button->area.center.y,
    &button->label.text_width,
    &button->label.text_height
  );
}

void cmw_button_set_text(
  struct cmw_button * button,
  unsigned char const * text
) {
  cmw_label_set_text(&button->label, text);
}

unsigned char const * cwm_button_get_text(struct cmw_button * button) {
  return cmw_label_get_text(&button->label);
}

void cmw_button_set_label_size_fn(
  struct cmw_button * button,
  cm_text_size_fn text_size_fn,
  void * text_size_fn_data
) {
  cmw_label_set_size_fn(&button->label, text_size_fn, text_size_fn_data);
}

uint16_t cmw_button_render(
  struct cmw_button const * button,
  struct cm_tileset const * tileset,
  struct cm_render_queue * queue
) {
  struct cm_tile tile = tileset->button.normal;
  switch (button->state) {
    case cmw_button__state_hovered:
      tile = tileset->button.hovered;
      break;
    case cmw_button__state_pressed:
      tile = tileset->button.pressed;
      break;
    case cmw_button__state_normal:
    default:
      break;
  }
  return cm_area_render(&button->area, tileset, queue, tile) +
  cmw_label_render(&button->label, tileset, queue);
}


