#ifndef CREME_CORE_VISIBILITY_MACRO_H
#define CREME_CORE_VISIBILITY_MACRO_H

#if defined _WIN32 || defined __CYGWIN__
  #define CORE_HELPER_DLL_IMPORT __declspec(dllimport)
  #define CORE_HELPER_DLL_EXPORT __declspec(dllexport)
#else
  #if __GNUC__ >= 4
    #define CORE_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define CORE_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define CORE_HELPER_DLL_IMPORT
    #define CORE_HELPER_DLL_EXPORT
  #endif
#endif

#ifdef core_EXPORTS
  #define CORE_API CORE_HELPER_DLL_EXPORT
#else
  #define CORE_API CORE_HELPER_DLL_IMPORT
#endif

#endif /* CREME_CORE_VISIBILITY_MACRO_H */
