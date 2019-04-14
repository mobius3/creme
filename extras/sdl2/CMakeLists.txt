project(creme::sdl2 C)

find_package(SDL2 REQUIRED)
include(GNUInstallDirs)

set(CREME_X_SDL2_HEADERS
  include/render.h
)

set(CREME_X_SDL2_SOURCES
  src/render.c
)

add_library(creme-x-sdl2 ${CREME_X_SDL2_SOURCES})

add_library(creme::sdl2 ALIAS creme-x-sdl2)

set_target_properties(creme-x-sdl2 PROPERTIES
  C_STANDARD 90
  VERSION ${creme_VERSION}
  PUBLIC_HEADER "${CREME_X_SDL2_HEADERS}"
)
target_include_directories(creme-x-sdl2 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/x/sdl2>)

target_compile_options(creme-x-sdl2 PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)

target_link_libraries(creme-x-sdl2 PUBLIC creme SDL2)

install(TARGETS creme-x-sdl2
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/x/sdl2/
)
