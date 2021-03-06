set(CREME_CORE_VERSION 1.0.0)

set(CREME_CORE_INCLUDE_FILES
  include/area.h
  include/circular-queue.h
  include/creme-core.h
  include/color.h
  include/core-exports.h
  include/rect.h
  include/render-command.h
  include/render-queue.h
  include/size.h
  include/tile.h
  include/tileset.h
  include/value.h
  include/value-reduce.h
)

set(CREME_CORE_SOURCE_FILES
  src/area.c
  src/color.c
  src/rect.c
  src/render-command.c
  src/render-queue.c
  src/size.c
  src/tile.c
  src/value.c
  src/value-reduce.c
)

add_library(core ${CREME_CORE_SOURCE_FILES} ${CREME_CORE_INCLUDE_FILES})
add_library(creme::core ALIAS core)

set_target_properties(core PROPERTIES
  C_STANDARD 99
  VERSION ${CREME_CORE_VERSION}
  PUBLIC_HEADER "${CREME_CORE_INCLUDE_FILES}"
  OUTPUT_NAME "creme-core"
)

target_include_directories(core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme/core>)

target_compile_options(core PRIVATE
  $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
  $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>)

install(TARGETS core
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme/core
)

if (CREME_DEBUG_UPDATE_CYCLE)
  target_compile_definitions(core PRIVATE CREME_DEBUG_UPDATE_CYCLE)
endif()

if (NOT MSVC)
  target_link_libraries(core PUBLIC "-lm")
endif()
