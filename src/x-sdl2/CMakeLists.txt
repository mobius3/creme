project(creme::sdl2 C)

find_package(SDL2 REQUIRED)
include(GNUInstallDirs)

set(CREME_X_SDL2_HEADERS
  include/creme-x-sdl2.h
  include/context.h
  include/window.h
  include/renderer.h
  include/texture.h
)

set(CREME_X_SDL2_SOURCES
  src/context.c
  src/renderer.c
  src/window.c
  src/texture.c
)

add_library(x-sdl2 ${CREME_X_SDL2_SOURCES} ${CREME_X_SDL2_HEADERS})
add_library(creme::x-sdl2 ALIAS x-sdl2)

set_target_properties(x-sdl2 PROPERTIES
  C_STANDARD 90
  VERSION ${creme_VERSION}
  PUBLIC_HEADER "${CREME_X_SDL2_HEADERS}"
  OUTPUT_NAME "creme-x-sdl2"
)

target_include_directories(x-sdl2 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/x/sdl2>)

target_compile_options(x-sdl2 PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden>
  $<$<C_COMPILER_ID:MSVC>:/W4>)

target_link_libraries(x-sdl2 PUBLIC creme::core creme::x-truetype SDL2 PRIVATE stb::image)

install(TARGETS x-sdl2
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/x/sdl2/
)
