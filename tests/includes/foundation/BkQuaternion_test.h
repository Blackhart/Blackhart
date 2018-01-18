#ifndef __BK_QUATERNION_TEST_H__
#define __BK_QUATERNION_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

void	BkQuaternion_RunTests(void);

void	BkQuaternion_Identity_test(void);
void	BkQuaternion_FromAngleAxis_test(void);
void	BkQuaternion_FromEulerAngles_test(void);
void	BkQuaternion_FromBkMatrix4x4_test(void);
void	BkQuaternion_Mul_BkQuaternion_test(void);
void	BkQuaternion_Copy_test(void);
void	BkQuaternion_Set_test(void);
void	BkQuaternion_Normalize_test(void);
void	BkQuaternion_Negate_test(void);
void	BkQuaternion_Magnitude_test(void);
void	BkQuaternion_Conjugate_test(void);
void	BkQuaternion_Inverse_test(void);
void	BkQuaternion_Difference_test(void);
void	BkQuaternion_Dot_test(void);

#endif