project(stb-image)
add_library(stb-image STATIC src/stb_image.c)

target_include_directories(stb-image PUBLIC include/)

if (NOT MSVC)
  target_link_libraries(stb-image PUBLIC "-lm")
endif()

add_library(stb::image ALIAS stb-image)