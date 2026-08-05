#ifndef __BK_SCENE_TEST_H__
#define __BK_SCENE_TEST_H__

extern void BkScene_RunTests(void);

extern void BkScene_CreateRelease_test(void);
extern void BkScene_AddGetRemoveCloud_test(void);
extern void BkScene_RemoveCloud_NotInScene_test(void);
extern void BkScene_GetCloud_OutOfRange_test(void);
extern void BkScene_Release_DoesNotFreeClouds_test(void);

#endif
