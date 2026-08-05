#ifndef __BK_GPU_CACHE_TEST_H__
#define __BK_GPU_CACHE_TEST_H__

extern void BkGpuCache_RunTests(void);

extern void BkGpuCache_CreateDestroy_test(void);
extern void BkGpuCache_HasEntry_Empty_test(void);
extern void BkGpuCache_MarkDirty_NoEntry_test(void);
extern void BkGpuCache_MarkDirty_NullArgs_test(void);
extern void BkGpuCache_FlushDirty_Empty_test(void);
extern void BkGpuCache_Remove_NoEntry_test(void);
extern void BkGpuCache_Clear_Empty_test(void);
extern void BkGpuCache_Query_NullArgs_test(void);

#endif
