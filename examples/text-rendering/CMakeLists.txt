add_executable(text-rendering
  src/main.c
)

target_link_libraries(text-rendering
  creme::creme
  creme::x-sdl2
  c-rez::tilesets
  c-rez::fonts
)
set_target_properties(text-rendering PROPERTIES
  C_STANDARD 90
  OUTPUT_NAME "creme-example-text-rendering"
)