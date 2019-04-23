project(stb-truetype)
add_library(stb-truetype STATIC src/stb_truetype.c)

target_include_directories(stb-truetype PUBLIC include/)

add_library(stb::truetype ALIAS stb-truetype)