#ifndef __BK_EULER_ANGLES_TEST_H__
#define __BK_EULER_ANGLES_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkEulerAngles_RunTests(void);

extern void	BkEulerAngles_FromXYZ_test(void);
extern void	BkEulerAngles_FromBkQuaternion_test(void);
extern void	BkEulerAngles_FromBkMatrix4x4_test(void);
extern void	BkEulerAngles_Set_test(void);

#endif