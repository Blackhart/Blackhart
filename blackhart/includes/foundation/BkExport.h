#ifndef __INTERNAL_BK_EXPORT_H__
#define __INTERNAL_BK_EXPORT_H__

#ifdef _WIN32
#ifdef BK_EXPORT
#define BK_API __declspec(dllexport)
#else
#define BK_API __declspec(dllimport)
#endif
#else
#ifdef BK_EXPORT
#define BK_API __attribute__((visibility("default")))
#else
#define BK_API
#endif
#endif

#endif
