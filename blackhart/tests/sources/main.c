// Unity headers.
#include <unity.h>

// Test headers
#include "foundation/BkAABB_test.h"
#include "foundation/BkAngleAxis_test.h"
#include "foundation/BkArray_test.h"
#include "foundation/BkColor3_test.h"
#include "foundation/BkEulerAngles_test.h"
#include "foundation/BkList_test.h"
#include "foundation/BkMath_test.h"
#include "foundation/BkMatrix4x4_test.h"
#include "foundation/BkPly_test.h"
#include "foundation/BkPoint3_test.h"
#include "foundation/BkQuaternion_test.h"
#include "foundation/BkQueue_test.h"
#include "foundation/BkString_test.h"
#include "foundation/BkVector3_test.h"
#include "renderer/BkGpuCache_test.h"
#include "renderer/BkPointCloud_test.h"
#include "renderer/BkScene_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

/*! Empty Initialization function needed by Unity
 */
void setUp() {}

/*! Empty Uninitialization function needed by Unity
 */
void tearDown() {}

int main(int argc, char** argv) {
  UNITY_BEGIN();

  BkArray_RunTests();
  BkAABB_RunTests();
  BkColor3_RunTests();
  BkList_RunTests();
  BkMath_RunTests();
  BkMatrix4x4_RunTests();
  BkPoint3_RunTests();
  BkPly_RunTests();
  BkPointCloud_RunTests();
  BkScene_RunTests();
  BkGpuCache_RunTests();
  BkQueue_RunTests();
  BkVector3_RunTests();
  BkString_RunTests();
  BkQuaternion_RunTests();
  BkAngleAxis_RunTests();
  BkEulerAngles_RunTests();

  return UNITY_END();
}