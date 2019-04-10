project(creme::sdl2 C)

add_library(cmx-sdl2
  src/render.c
)

add_library(creme::sdl2 ALIAS cmx-sdl2)

set_target_properties(cmx-sdl2 PROPERTIES C_STANDARD 90)
target_include_directories(cmx-sdl2 PUBLIC include)
target_compile_options(cmx-sdl2 PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)
target_link_libraries(cmx-sdl2 PUBLIC creme)