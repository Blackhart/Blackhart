#ifndef __BK_POINT_CLOUD_TEST_H__
#define __BK_POINT_CLOUD_TEST_H__

extern void BkPointCloud_RunTests(void);

extern void BkPointCloud_CreateFromPlyFile_Success_test(void);
extern void BkPointCloud_CreateFromPlyFile_NullFilename_test(void);
extern void BkPointCloud_CreateFromPlyFile_MissingFile_test(void);
extern void BkPointCloud_CreateFromPlyFile_InvalidPly_test(void);
extern void BkPointCloud_GetPoints_Contents_test(void);
extern void BkPointCloud_GetAABB_Identity_test(void);
extern void BkPointCloud_GetAABB_AfterSetPosition_test(void);
extern void BkPointCloud_GetAABB_AfterSetOrientation_test(void);
extern void BkPointCloud_GetAABB_TightAfterOrientation_test(void);
extern void BkPointCloud_Colors_Absent_test(void);
extern void BkPointCloud_Colors_Present_test(void);
extern void BkPointCloud_Release_SetsNull_test(void);

#endif
