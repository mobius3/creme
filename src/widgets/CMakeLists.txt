set(CREME_WIDGETS_VERSION 1.0.0)

set(CREME_WIDGETS_INCLUDE_FILES
  include/creme-widgets.h
  include/frame.h
  include/label.h
  include/widgets-exports.h
)

set(CREME_WIDGETS_SOURCE_FILES
  src/frame.c
  src/label.c
)

add_library(widgets ${CREME_WIDGETS_SOURCE_FILES} ${CREME_WIDGETS_INCLUDE_FILES})
add_library(creme::widgets ALIAS widgets)

set_target_properties(widgets PROPERTIES
  C_STANDARD 99
  VERSION ${CREME_WIDGETS_VERSION}
  PUBLIC_HEADER "${CREME_WIDGETS_INCLUDE_FILES}"
  OUTPUT_NAME "creme-widgets")

target_link_libraries(widgets PUBLIC creme::core)

target_include_directories(widgets PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/widgets>)

target_compile_options(widgets PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>)

install(TARGETS widgets
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/widgets
  )
