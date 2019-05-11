#include "context.h"

#include "creme-core.h"
#include "creme-x-truetype.h"
#include "command-rendering.h"

#include <string.h>

void cmx_sdl2_context_destruct(struct cmx_sdl2_context * context) {
  SDL_DestroyTexture(context->tileset_texture);
  SDL_DestroyTexture(context->font_texture);
  SDL_DestroyRenderer(context->renderer);
  SDL_DestroyWindow(context->window);
}

void cmx_sdl2_context_init(struct cmx_sdl2_context * context) {
  int window_w, window_h;
  SDL_GetWindowSize(context->window, &window_w, &window_h);

  cm_area_construct(&context->area);
  cm_area_set(
    &context->area, 0, 0,
    (float) window_w,
    (float) window_h
  );
  context->left = &context->area.left;
  context->top = &context->area.top;
  context->right = &context->area.right;
  context->bottom = &context->area.bottom;
}

void cmx_sdl2_context_update(struct cmx_sdl2_context * context) {
  int window_w, window_h;
  SDL_GetWindowSize(context->window, &window_w, &window_h);
  cm_value_set(&context->area.right, (float) window_w);
  cm_value_set(&context->area.bottom, (float) window_h);

  SDL_PumpEvents();
}

void cmx_sdl2_context_render(struct cmx_sdl2_context * context) {
  struct cm_render_queue * queue = &context->queue;
  struct cm_tileset const * tileset = &context->tileset;
  struct SDL_Renderer * renderer = context->renderer;
  struct SDL_Texture * tileset_texture = context->tileset_texture;

  struct cm_render_command cmd;

  while (!cm_render_queue_is_empty(queue)) {
    cm_render_queue_dequeue(queue, &cmd);
    switch (cmd.type) {
      case cm_render_command__tile:
        cmx_sdl2_render_tile_command(&cmd, tileset, renderer, tileset_texture);
        break;
      case cm_render_command__text:
        cmx_sdl2_render_text_command(
          &cmd,
          context->font,
          context->renderer,
          context->font_texture
        );
      default:
        break;
    }
  }
}


