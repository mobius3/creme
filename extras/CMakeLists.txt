option(CREME_BUILD_EXTRAS_SDL2_RENDERER "Build the SDL2 extra" OFF)

if (CREME_BUILD_EXTRAS_SDL2)
  add_subdirectory(sdl2)
endif()