project(creme::truetype C)

include(GNUInstallDirs)

set(CREME_X_TRUETYPE_HEADERS
  include/character-mapping.h
  include/font.h
  include/font-size.h
  include/packed-block.h
  include/unicode-block.h
)

set(CREME_X_TRUETYPE_SOURCES
  src/font.c
  src/font-size.c
  src/unicode-block.c
)

add_library(x-truetype ${CREME_X_TRUETYPE_SOURCES} ${CREME_X_TRUETYPE_HEADERS})
add_library(creme::x-truetype ALIAS x-truetype)

set_target_properties(x-truetype PROPERTIES
  C_STANDARD 90
  VERSION ${creme_VERSION}
  PUBLIC_HEADER "${CREME_X_TRUETYPE_HEADERS}"
  OUTPUT_NAME "creme-x-truetype"
)

target_include_directories(x-truetype PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/x/truetype>)

target_compile_options(x-truetype PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)

target_link_libraries(x-truetype PUBLIC creme PRIVATE stb::truetype utf8-decode)

install(TARGETS x-truetype
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/x/truetype/
)
