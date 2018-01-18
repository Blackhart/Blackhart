#ifndef __INTERNAL_BK_EXPORT_H__
#define __INTERNAL_BK_EXPORT_H__

#ifdef BK_EXPORT
	#define BK_API	__declspec(dllexport)
#else
	#define BK_API	__declspec(dllimport)
#endif

#endif
