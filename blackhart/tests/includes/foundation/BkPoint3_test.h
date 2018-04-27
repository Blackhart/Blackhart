#ifndef __BK_POINT3_TEST_H__
#define __BK_POINT3_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkPoint3_RunTests(void);

extern void	BkPoint3_Zero_test(void);
extern void	BkPoint3_FromXYZ_test(void);
extern void	BkPoint3_Set_test(void);
extern void	BkPoint3_Copy_test(void);
extern void	BkPoint3_Assign_test(void);
extern void	BkPoint3_Add_BkVector3_test(void);
extern void	BkPoint3_Sub_BkVector3_test(void);
extern void	BkPoint3_Sub_BkPoint3_test(void);
extern void	BkPoint3_Lerp_test(void);
extern void	BkPoint3_Distance_test(void);

#endif