#ifndef __BK_VECTOR3_TEST_H__
#define __BK_VECTOR3_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkVector3_RunTests(void);

extern void	BkVector3_Zero_test(void);
extern void	BkVector3_FromXYZ_test(void);
extern void	BkVector3_Set_test(void);
extern void	BkVector3_Copy_test(void);
extern void	BkVector3_Assign_test(void);
extern void	BkVector3_Negated_test(void);
extern void	BkVector3_Negate_test(void);
extern void	BkVector3_Mul_Real_test(void);
extern void	BkVector3_Div_Real_test(void);
extern void	BkVector3_Add_BkVector3_test(void);
extern void	BkVector3_Sub_BkVector3_test(void);
extern void	BkVector3_Magnitude_test(void);
extern void	BkVector3_Normalized_test(void);
extern void	BkVector3_Normalize_test(void);
extern void	BkVector3_Dot_test(void);
extern void	BkVector3_AbsDot_test(void);
extern void	BkVector3_Cross_test(void);
extern void	BkVector3_Angle_test(void);
extern void	BkVector3_Lerp_test(void);
extern void	BkVector3_Max_test(void);
extern void	BkVector3_Min_test(void);

#endif