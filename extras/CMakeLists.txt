option(CREME_BUILD_EXTRAS_SDL2_RENDERER "Build the SDL2 renderer" OFF)

if (CREME_BUILD_EXTRAS_SDL2_RENDERER)
  add_subdirectory(sdl2-renderer)
endif()