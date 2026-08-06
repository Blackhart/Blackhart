#ifndef __BK_PLY_TEST_H__
#define __BK_PLY_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void BkPly_RunTests(void);

extern void BkPly_LoadPoints_NullFilename_test(void);
extern void BkPly_LoadPoints_FileDoesNotExist_test(void);
extern void BkPly_LoadPoints_NoPermission_test(void);
extern void BkPly_LoadPoints_NotAPly_test(void);
extern void BkPly_LoadPoints_NoHeader_test(void);
extern void BkPly_LoadPoints_NoVertices_test(void);
extern void BkPly_LoadColors_Absent_test(void);
extern void BkPly_LoadColors_Present_test(void);

#endif
