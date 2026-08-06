// Standard headers.
#include <stdlib.h>

// Blackhart headers.
#include "foundation/BkArray.h"
#include "foundation/BkColor3.h"
#include "foundation/BkError.h"
#include "foundation/BkMatrix4x4.h"
#include "foundation/BkPly.h"
#include "foundation/BkPoint3.h"
#include "renderer/BkPointCloud.h"

// ~~~~~ Type Definitions ~~~~~

struct BkPointCloud {
  struct BkArray* points;
  struct BkArray* colors; /**< NULL when the PLY had no RGB. */
  BkAABB aabb;
  struct BkTransform transform;
};

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* const __BkPointCloud_CreateAborted =
    "Point cloud was not created; BkPointCloud_CreateFromPlyFile returned NULL";

static void __BkPointCloud_ReleaseArray(struct BkArray** array) {
  if (BK_ISNULL(array) || BK_ISNULL(*array)) return;

  BkArray_Destroy(*array);
  free(*array);
  *array = NULL;
}

// ~~~~~ Def(PUBLIC) ~~~~~

BkPointCloud* BkPointCloud_CreateFromPlyFile(char const* filename) {
  struct BkArray* points = _BkPly_LoadPoints(filename);
  BK_ERROR(
      BK_ISNULL(points),
      ((struct BkErrorInfo){
          .what = "Cannot create point cloud from PLY",
          .why = "Underlying PLY load failed (_BkPly_LoadPoints returned NULL)",
          .where = filename,
          .how = "Fix the PLY path or content; see the preceding BkPly error "
                 "for details",
          .result = __BkPointCloud_CreateAborted,
      }),
      NULL);

  struct BkArray* colors = _BkPly_LoadColors(filename);

  BkPointCloud* pointCloud = malloc(sizeof(BkPointCloud));
  if (BK_ISNULL(pointCloud)) {
    __BkPointCloud_ReleaseArray(&points);
    __BkPointCloud_ReleaseArray(&colors);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot allocate point cloud",
                 .why = "Out of memory while allocating BkPointCloud",
                 .where = filename,
                 .how = "Free memory or reduce the size of the point cloud",
                 .result = __BkPointCloud_CreateAborted,
             }),
             NULL);
  }

  pointCloud->points = points;
  pointCloud->colors = colors;
  pointCloud->aabb =
      BkAABB_FromPoints((BkPoint3 const*)points->data, BkArray_Size((*points)));
  BkTransform_Initialize(&pointCloud->transform);
  return pointCloud;
}

void BkPointCloud_Release(BkPointCloud** pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  BK_ASSERT(BK_ISNULL(*pointCloud));

  __BkPointCloud_ReleaseArray(&(*pointCloud)->points);
  __BkPointCloud_ReleaseArray(&(*pointCloud)->colors);

  free(*pointCloud);
  *pointCloud = NULL;
}

size_t BkPointCloud_GetCount(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (BK_ISNULL(pointCloud->points)) {
    return 0;
  }

  return BkArray_Size((*pointCloud->points));
}

BkPoint3 const* BkPointCloud_GetPoints(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (BK_ISNULL(pointCloud->points) || BK_ISNULL(pointCloud->points->data)) {
    return NULL;
  }

  return (BkPoint3 const*)pointCloud->points->data;
}

bool BkPointCloud_HasColors(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  return !BK_ISNULL(pointCloud->colors) && !BK_ISNULL(pointCloud->colors->data);
}

BkColor3 const* BkPointCloud_GetColors(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (!BkPointCloud_HasColors(pointCloud)) {
    return NULL;
  }

  return (BkColor3 const*)pointCloud->colors->data;
}

BkAABB BkPointCloud_GetAABB(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  return pointCloud->aabb;
}

BkAABB BkPointCloud_GetWorldAABB(BkPointCloud* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  struct BkMatrix4x4 const* model = BkTransform_Matrix(&pointCloud->transform);
  BkAABB const* local = &pointCloud->aabb;

  struct BkPoint3 corners[8] = {
      {local->min.x, local->min.y, local->min.z},
      {local->max.x, local->min.y, local->min.z},
      {local->min.x, local->max.y, local->min.z},
      {local->max.x, local->max.y, local->min.z},
      {local->min.x, local->min.y, local->max.z},
      {local->max.x, local->min.y, local->max.z},
      {local->min.x, local->max.y, local->max.z},
      {local->max.x, local->max.y, local->max.z},
  };

  for (size_t i = 0; i < 8; ++i) {
    corners[i] = BkMatrix4x4_Mul_BkPoint3(model, &corners[i]);
  }

  return BkAABB_FromPoints(corners, 8);
}

struct BkTransform* BkPointCloud_GetTransform(BkPointCloud* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  return &pointCloud->transform;
}

void BkPointCloud_SetPosition(BkPointCloud* pointCloud,
                              BkPoint3 const* position) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  BK_ASSERT(BK_ISNULL(position));
  BkTransform_SetPosition(&pointCloud->transform, position);
}

void BkPointCloud_SetOrientation(BkPointCloud* pointCloud,
                                 BkQuaternion const* orientation) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  BK_ASSERT(BK_ISNULL(orientation));
  BkTransform_SetOrientation(&pointCloud->transform, orientation);
}
