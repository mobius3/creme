option(CREME_BUILD_EXTRAS_SDL2_RENDERER "Build the SDL2 extra" OFF)

if (CREME_BUILD_EXTRAS_SDL2)
  add_subdirectory(sdl2)
endif()

if (CREME_BUILD_EXTRAS_TRUETYPE)
  add_subdirectory(truetype)
endif()