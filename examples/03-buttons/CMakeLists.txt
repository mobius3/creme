find_package(SDL2 REQUIRED)

add_executable(03-buttons
  src/main.c
)

target_link_libraries(03-buttons
  creme::core
  creme::widgets
  creme::x-sdl2
  creme::x-truetype
  c-rez::tilesets
  c-rez::fonts
  SDL2
)
set_target_properties(03-buttons PROPERTIES
  C_STANDARD 99
  OUTPUT_NAME "creme-example-03-buttons"
)

target_compile_options(03-buttons PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>)