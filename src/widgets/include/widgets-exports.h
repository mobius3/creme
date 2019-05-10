#ifndef CREME_WIDGETS_VISIBILITY_MACRO_H
#define CREME_WIDGETS_VISIBILITY_MACRO_H

#if defined _WIN32 || defined __CYGWIN__
  #define WIDGETS_HELPER_DLL_IMPORT __declspec(dllimport)
  #define WIDGETS_HELPER_DLL_EXPORT __declspec(dllexport)
#else
  #if __GNUC__ >= 4
    #define WIDGETS_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define WIDGETS_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define WIDGETS_HELPER_DLL_IMPORT
    #define WIDGETS_HELPER_DLL_EXPORT
  #endif
#endif

#ifdef widgets_EXPORTS
  #define WIDGETS_API WIDGETS_HELPER_DLL_EXPORT
#else
  #define WIDGETS_API WIDGETS_HELPER_DLL_IMPORT
#endif

#endif /* CREME_WIDGETS_VISIBILITY_MACRO_H */
