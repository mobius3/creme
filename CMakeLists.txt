cmake_minimum_required(VERSION 3.0)
project(creme LANGUAGES C VERSION 1.0.0)

include(GNUInstallDirs)

# Setup bin/lib/executable folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

# other useful options
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# add debug sufix to lib
if(MSVC)
  set(CMAKE_DEBUG_POSTFIX "d")
endif()

# enforce a build type
if(NOT CMAKE_CONFIGURATION_TYPES)
  if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Debug")
  endif()
endif()

option(CREME_BUILD_EXTRAS "Build extras (inside extras/ folder)" OFF)
option(CREME_BUILD_EXAMPLES "Build examples (inside examples/ folder). It will also turn on all extras" OFF)
option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# keep it sorted, directories first.
set(CREME_HEADERS
  include/widget/frame.h
  include/widget/label.h
  include/area.h
  include/circular-queue.h
  include/rect.h
  include/render-command.h
  include/render-queue.h
  include/tile.h
  include/value.h
  include/size.h
)

set(CREME_SOURCES
  src/widget/frame.c
  src/widget/label.c
  src/area.c
  src/rect.c
  src/render-command.c
  src/render-queue.c
  src/tile.c
  src/value.c
  src/size.c)

add_library(creme ${CREME_SOURCES} ${CREME_HEADERS})
add_library(creme::creme ALIAS creme)

set_target_properties(creme PROPERTIES
  C_STANDARD 90
  VERSION ${creme_VERSION}
  PUBLIC_HEADER "${CREME_HEADERS}"
)

target_include_directories(creme PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/creme>)

target_compile_options(creme PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall,-Wextra,-pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)

install(TARGETS creme
  EXPORT creme-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/creme
)

if (CREME_BUILD_EXAMPLES AND NOT CREME_BUILD_EXTRAS)
  set(CREME_BUILD_EXTRAS ON)
  set(CREME_BUILD_EXTRAS_SDL2 ON)
  set(CREME_BUILD_EXTRAS_FONT ON)
endif()

if (CREME_BUILD_EXTRAS)
  add_subdirectory(third-party EXCLUDE_FROM_ALL)
  add_subdirectory(extras)
endif()

if (CREME_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

include(cmake/setup-exports.cmake)
