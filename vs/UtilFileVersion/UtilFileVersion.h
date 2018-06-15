#ifndef __UTIL_FILE_VERSION__
#define __UTIL_FILE_VERSION__

#ifdef UTIL_FILE_VER_EXPORTS
#define UTIL_FILE_VER_CPPAPI __declspec(dllexport)
#else
#define UTIL_FILE_VER_CPPAPI __declspec(dllimport)	
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif