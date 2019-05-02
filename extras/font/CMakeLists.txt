project(creme::font C)

include(GNUInstallDirs)

set(CREME_X_FONT_HEADERS
  include/font.h
  include/unicode-block.h
)

set(CREME_X_FONT_SOURCES
  src/font.c
  src/unicode-block.c
)

add_library(x-font ${CREME_X_FONT_SOURCES} ${CREME_X_FONT_HEADERS})
add_library(creme::x-font ALIAS x-font)

set_target_properties(x-font PROPERTIES
  C_STANDARD 90
  VERSION ${creme_VERSION}
  PUBLIC_HEADER "${CREME_X_FONT_HEADERS}"
  OUTPUT_NAME "creme-x-font"
)

target_include_directories(x-font PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/x/font>)

target_compile_options(x-font PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)

target_link_libraries(x-font PUBLIC creme PRIVATE stb::truetype)

install(TARGETS x-font
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/x/font/
)
