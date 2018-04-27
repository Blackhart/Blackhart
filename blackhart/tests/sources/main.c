// Unity headers.
#include <unity.h>

// Test headers
#include "foundation/BkArray_test.h"
#include "foundation/BkList_test.h"
#include "foundation/BkMath_test.h"
#include "foundation/BkMatrix4x4_test.h"
#include "foundation/BkPoint3_test.h"
#include "foundation/BkQueue_test.h"
#include "foundation/BkVector3_test.h"
#include "foundation/BkString_test.h"
#include "foundation/BkQuaternion_test.h"
#include "foundation/BkAngleAxis_test.h"
#include "foundation/BkEulerAngles_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

/*! Empty Initialization function needed by Unity
 */
void setUp()
{

}

/*! Empty Uninitialization function needed by Unity
*/
void tearDown()
{

}

int main(int argc, char** argv)
{
	UNITY_BEGIN();

	BkArray_RunTests();
	BkList_RunTests();
	BkMath_RunTests();
	BkMatrix4x4_RunTests();
	BkPoint3_RunTests();
	BkQueue_RunTests();
	BkVector3_RunTests();
	BkString_RunTests();
	BkQuaternion_RunTests();
	BkAngleAxis_RunTests();
	BkEulerAngles_RunTests();

	getchar();

	return UNITY_END();
}