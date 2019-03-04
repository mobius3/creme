cmake_minimum_required(VERSION 3.0)
project(creme C)

set(CMAKE_C_STANDARD 90)

add_library(creme
  src/value.c
  src/area.c
  src/render-command.c
  src/tile.c
  src/render-queue.c
  src/rect.c
  )
target_include_directories(creme PUBLIC include)

add_executable(creme-sandbox creme-sandbox.c)
target_link_libraries(creme-sandbox PUBLIC creme)