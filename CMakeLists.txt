cmake_minimum_required(VERSION 3.0)
project(creme C)

add_library(creme
  src/value.c
  src/area.c
  src/render-command.c
  src/tile.c
  src/render-queue.c
  src/rect.c
  src/widget/frame.c
  )

set_target_properties(creme PROPERTIES C_STANDARD 90)
target_include_directories(creme PUBLIC include)
target_compile_options(creme PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)

add_executable(creme-sandbox creme-sandbox.c)
target_link_libraries(creme-sandbox PUBLIC creme)