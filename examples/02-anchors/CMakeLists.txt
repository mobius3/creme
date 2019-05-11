find_package(SDL2 REQUIRED)

add_executable(02-anchors
  src/main.c
)

target_link_libraries(02-anchors
  creme::core
  creme::widgets
  creme::x-sdl2
  c-rez::tilesets
  SDL2
)
set_target_properties(02-anchors PROPERTIES
  C_STANDARD 99
  OUTPUT_NAME "creme-example-02-anchors"
)

target_compile_options(02-anchors PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>)