#include "context.h"

static void render_tile(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture);

void cmx_sdl2_context_init(struct cmx_sdl2_context * context) {
  int window_w, window_h;
  SDL_GetWindowSize(context->window, &window_w, &window_h);

  cm_area_construct(&context->area);
  cm_area_set(&context->area, 0, 0,
              (float) window_w,
              (float) window_h);
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
        render_tile(&cmd, tileset, renderer, tileset_texture);
        break;
      default:
        break;
    }
  }
}

void cmx_sdl2_context_destruct(struct cmx_sdl2_context * context) {
  SDL_DestroyTexture(context->tileset_texture);
  SDL_DestroyRenderer(context->renderer);
  SDL_DestroyWindow(context->window);
}

void render_tile(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture) {
  SDL_Rect src = {
    .x = command->tile.column * tileset->tile_width,
    .y = command->tile.row * tileset->tile_height,
    .w = tileset->tile_width,
    .h = tileset->tile_height
  };
  SDL_Rect dst = {
    .x = (int) command->target.left,
    .y = (int) command->target.top,
    .w = (int) cm_rect_width(&command->target),
    .h = (int) cm_rect_height(&command->target)
  };
  SDL_RenderCopy(renderer, tileset_texture, &src, &dst);
}


