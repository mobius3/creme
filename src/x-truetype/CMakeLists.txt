project(creme::truetype C)

include(GNUInstallDirs)

set(CREME_X_TRUETYPE_HEADERS
  include/character-mapping.h
  include/creme-x-truetype.h
  include/font.h
  include/font-size.h
  include/packed-block.h
  include/unicode-block.h
  include/x-truetype-exports.h
)

set(CREME_X_TRUETYPE_SOURCES
  src/font.c
  src/font-size.c
  src/unicode-block.c
)

add_library(x-truetype ${CREME_X_TRUETYPE_SOURCES} ${CREME_X_TRUETYPE_HEADERS})
add_library(creme::x-truetype ALIAS x-truetype)

set_target_properties(x-truetype PROPERTIES
  C_STANDARD 99
  VERSION ${creme_VERSION}
  PUBLIC_HEADER "${CREME_X_TRUETYPE_HEADERS}"
  OUTPUT_NAME "creme-x-truetype"
)

target_include_directories(x-truetype PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/x/truetype>)

target_compile_options(x-truetype PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>)

target_link_libraries(x-truetype PUBLIC creme::core PRIVATE stb::truetype utf8-decode)

install(TARGETS x-truetype
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/x/truetype/
)
