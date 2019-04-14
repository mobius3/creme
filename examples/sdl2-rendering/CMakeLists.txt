add_executable(sdl2-rendering
  src/main.c
  src/state.c
)

target_link_libraries(sdl2-rendering
  creme::creme
  creme::x-sdl2
  c-rez::tilesets
  stb::image
)
target_include_directories(sdl2-rendering PRIVATE include/)

set_target_properties(sdl2-rendering PROPERTIES
  C_STANDARD 90
  OUTPUT_NAME "creme-example-sdl2-rendering"
)