find_package(SDL2 REQUIRED)

add_executable(sdl2-rendering
  src/main.c
)

target_link_libraries(sdl2-rendering
  creme::core
  creme::widgets
  creme::x-sdl2
  c-rez::tilesets
  SDL2
)
set_target_properties(sdl2-rendering PROPERTIES
  C_STANDARD 99
  OUTPUT_NAME "creme-example-sdl2-rendering"
)

target_compile_options(sdl2-rendering PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W4 /Wall /WX>)