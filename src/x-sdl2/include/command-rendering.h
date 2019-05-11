#ifndef CREME_EXTRAS_SDL2_COMMAND_RENDERING_H
#define CREME_EXTRAS_SDL2_COMMAND_RENDERING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "x-sdl2-exports.h"
#include "creme-x-truetype.h"
#include "render-command.h"
#include "tileset.h"
#include "SDL.h"

X_SDL2_API extern void cmx_sdl2_render_text_command(
  struct cm_render_command const * command,
  struct cmx_truetype_font const * font,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * font_texture
);

X_SDL2_API extern void cmx_sdl2_render_tile_command(
  struct cm_render_command const * command,
  struct cm_tileset const * tileset,
  struct SDL_Renderer * renderer,
  struct SDL_Texture * tileset_texture
);

#ifdef __cplusplus
}
#endif

#endif /*CREME_EXTRAS_SDL2_COMMAND_RENDERING_H*/
