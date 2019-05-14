cmake_minimum_required(VERSION 3.0)
project(creme LANGUAGES C VERSION 1.0.0)

# request policies at version 3.12
cmake_policy(VERSION 3.12)

include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

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
#  set(CMAKE_DEBUG_POSTFIX "-debug")
endif()

# enforce a build type
if(NOT CMAKE_CONFIGURATION_TYPES)
  if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Debug")
  endif()
endif()

option(CREME_BUILD_EXTRAS "Build extras (inside extras/ folder)" OFF)
option(CREME_BUILD_EXTRAS_SDL2 "Build the SDL2 extra (if CMAKE_BUILD_EXTRAS is ON)" ON)
option(CREME_BUILD_EXTRAS_TRUETYPE "Build the truetype extra (if CMAKE_BUILD_EXTRAS is ON)" ON)
option(CREME_BUILD_EXAMPLES "Build examples (inside examples/ folder). It will also turn on all extras" OFF)
option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)
option(CREME_DEBUG_UPDATE_CYCLE "Prints in the console the update cycle of all cm_values" OFF)

if (CREME_BUILD_EXAMPLES)
  set(CREME_BUILD_EXTRAS ON)
  set(CREME_BUILD_EXTRAS_SDL2 ON)
  set(CREME_BUILD_EXTRAS_TRUETYPE ON)
endif()

if (CREME_BUILD_EXTRAS)
  add_subdirectory(third-party EXCLUDE_FROM_ALL)
endif()

if (CREME_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

add_subdirectory(src)

include(cmake/setup-exports.cmake)
