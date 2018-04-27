#ifndef __BK_MATH_TEST_H__
#define __BK_MATH_TEST_H__

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkMath_RunTests(void);

extern void	BkMath_PI_test(void);
extern void	BkMath_RadFromDeg_test(void);
extern void	BkMath_DegFromRad_test(void);
extern void	BkMath_CosFromSin_test(void);
extern void	BkMath_SinFromCos_test(void);
extern void	BkMath_TanFromSinCos_test(void);
extern void	BkMath_Clamp_Real_test(void);

#endif