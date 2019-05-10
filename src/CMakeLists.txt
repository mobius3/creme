add_subdirectory(core)
add_subdirectory(widgets)

if (CREME_BUILD_EXTRAS AND CREME_BUILD_EXTRAS_SDL2)
  add_subdirectory(x-sdl2)
endif()

if (CREME_BUILD_EXTRAS AND CREME_BUILD_EXTRAS_TRUETYPE)
  add_subdirectory(x-truetype)
endif()
