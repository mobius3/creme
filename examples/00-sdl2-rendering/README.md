# Creme example: SDL2 rendering

This example shows how to use SDL2 to render the commands produced by Creme.

- A `state` structure is used to hold all relevant SDL data, including the
  `SDL_Window`, `SDL_Renderer` and the `SDL_Texture` used for the tileset.
- After all this is loaded, four linked frames are constructed.
- In the main loop, the [creme::x-sdl2] extra library is used to render all
  passed commands.
  
[creme::x-sdl2]: ../extras/sdl2
