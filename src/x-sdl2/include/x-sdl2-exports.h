#ifndef CREME_X_SDL2_VISIBILITY_MACRO_H
#define CREME_X_SDL2_VISIBILITY_MACRO_H

#if defined _WIN32 || defined __CYGWIN__
  #define X_SDL2_HELPER_DLL_IMPORT __declspec(dllimport)
  #define X_SDL2_HELPER_DLL_EXPORT __declspec(dllexport)
#else
  #if __GNUC__ >= 4
    #define X_SDL2_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define X_SDL2_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
  #else
    #define X_SDL2_HELPER_DLL_EXPORT
    #define X_SDL2_HELPER_DLL_IMPORT
  #endif
#endif

#ifdef x_sdl2_EXPORTS
  #define X_SDL2_API X_SDL2_HELPER_DLL_EXPORT
#else
  #define X_SDL2_API X_SDL2_HELPER_DLL_IMPORT
#endif

#endif /* CREME_X_SDL2_VISIBILITY_MACRO_H */
