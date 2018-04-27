#ifndef __BK_MATRIX4X4_TEST_H__
#define __BK_MATRIX4X4_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkMatrix4x4_RunTests(void);

extern void	BkMatrix4x4_Identity_test(void);
extern void	BkMatrix4x4_Copy_test(void);
extern void	BkMatrix4x4_Assign_test(void);
extern void	BkMatrix4x4_Transpose_test(void);
extern void	BkMatrix4x4_Mul_real_test(void);
extern void	BkMatrix4x4_Mul_BkMatrix4x4_test(void);
extern void	BkMatrix4x4_Mul_BkVector3_test(void);
extern void	BkMatrix4x4_Mul_BkPoint3_test(void);
extern void	BkMatrix4x4_Mul_BkPoint4_test(void);
extern void	BkMatrix4x4_Scaling_Uniform_test(void);
extern void	BkMatrix4x4_Scaling_Nonuniform_test(void);
extern void	BkMatrix4x4_Scaling_Axis_test(void);
extern void	BkMatrix4x4_Translation_XYZ_test(void);
extern void	BkMatrix4x4_Translation_BkVector3_test(void);
extern void	BkMatrix4x4_Translation_BkPoint3_test(void);
extern void	BkMatrix4x4_Determinant_test(void);
extern void	BkMatrix4x4_Inverse_test(void);
extern void	BkMatrix4x4_FromAngleAxis_test(void);
extern void	BkMatrix4x4_FromEulerAngles_test(void);
extern void	BkMatrix4x4_FromBkQuaternion_test(void);

#endif