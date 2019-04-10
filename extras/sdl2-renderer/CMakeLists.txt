project(creme::sdl2-renderer C)

add_library(xcreme-sdl2-renderer
  src/sdl2-renderer.c
)

add_library(creme::sdl2-renderer ALIAS xcreme-sdl2-renderer)

set_target_properties(xcreme-sdl2-renderer PROPERTIES C_STANDARD 90)
target_include_directories(xcreme-sdl2-renderer PUBLIC include)
target_compile_options(xcreme-sdl2-renderer PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)
target_link_libraries(xcreme-sdl2-renderer PUBLIC creme)