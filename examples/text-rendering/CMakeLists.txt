add_executable(text-rendering
  src/main.c
)

target_link_libraries(text-rendering
  creme::core
  creme::widgets
  creme::x-sdl2
  creme::x-truetype
  c-rez::tilesets
  c-rez::fonts
)
set_target_properties(text-rendering PROPERTIES
  C_STANDARD 99
  OUTPUT_NAME "creme-example-text-rendering"
)

target_compile_options(text-rendering PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>)