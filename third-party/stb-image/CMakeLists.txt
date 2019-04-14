project(stb-image)
add_library(stb-image STATIC src/stb_image.c)
target_include_directories(stb-image PUBLIC include/)