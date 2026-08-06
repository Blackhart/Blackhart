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
  BkArray* points;
  BkArray* colors; /**< NULL when the PLY had no RGB. */
  BkAABB aabb; /**< World-space AABB (cached). */
  bool aabb_dirty;
  struct BkTransform transform;
};

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* const __BkPointCloud_CreateAborted =
    "Point cloud was not created; BkPointCloud_CreateFromPlyFile returned NULL";

// ~~~~~ Def(PUBLIC) ~~~~~

BkPointCloud* BkPointCloud_CreateFromPlyFile(char const* filename) {
  BkArray* points = _BkPly_LoadPoints(filename);
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

  BkArray* colors = _BkPly_LoadColors(filename);

  BkPointCloud* pointCloud = malloc(sizeof(BkPointCloud));
  if (BK_ISNULL(pointCloud)) {
    BkArray_Release(&points);
    BkArray_Release(&colors);
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

  size_t const count = BkArray_Size(points);
  BkPoint3* pts = (BkPoint3*)BkArray_Data(points);

  BkAABB const file_aabb = BkAABB_FromPoints(pts, count);
  struct BkPoint3 const center = BkAABB_Center(&file_aabb);

  for (size_t i = 0; i < count; ++i) {
    pts[i].x -= center.x;
    pts[i].y -= center.y;
    pts[i].z -= center.z;
  }

  pointCloud->aabb_dirty = true;
  BkTransform_Initialize(&pointCloud->transform);
  BkTransform_SetPosition(&pointCloud->transform, &center);
  return pointCloud;
}

void BkPointCloud_Release(BkPointCloud** pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  BK_ASSERT(BK_ISNULL(*pointCloud));

  BkArray_Release(&(*pointCloud)->points);
  BkArray_Release(&(*pointCloud)->colors);

  free(*pointCloud);
  *pointCloud = NULL;
}

size_t BkPointCloud_GetCount(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (BK_ISNULL(pointCloud->points)) {
    return 0;
  }

  return BkArray_Size(pointCloud->points);
}

BkPoint3 const* BkPointCloud_GetPoints(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (BK_ISNULL(pointCloud->points) ||
      BK_ISNULL(BkArray_Data(pointCloud->points))) {
    return NULL;
  }

  return (BkPoint3 const*)BkArray_Data(pointCloud->points);
}

bool BkPointCloud_HasColors(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  return !BK_ISNULL(pointCloud->colors) &&
         !BK_ISNULL(BkArray_Data(pointCloud->colors));
}

BkColor3 const* BkPointCloud_GetColors(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (!BkPointCloud_HasColors(pointCloud)) {
    return NULL;
  }

  return (BkColor3 const*)BkArray_Data(pointCloud->colors);
}

BkAABB BkPointCloud_GetAABB(BkPointCloud* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));

  if (!pointCloud->aabb_dirty) {
    return pointCloud->aabb;
  }

  size_t const count = BkPointCloud_GetCount(pointCloud);
  BkPoint3 const* points = BkPointCloud_GetPoints(pointCloud);
  if (count == 0 || BK_ISNULL(points)) {
    pointCloud->aabb = BkAABB_Zero();
    pointCloud->aabb_dirty = false;
    return pointCloud->aabb;
  }

  struct BkMatrix4x4 const* model = BkTransform_Matrix(&pointCloud->transform);
  struct BkPoint3 world = BkMatrix4x4_Mul_BkPoint3(model, &points[0]);
  struct BkAABB aabb = BkAABB_FromMinMax(&world, &world);

  for (size_t i = 1; i < count; ++i) {
    world = BkMatrix4x4_Mul_BkPoint3(model, &points[i]);
    BkAABB_IncludePoint(&aabb, &world);
  }

  pointCloud->aabb = aabb;
  pointCloud->aabb_dirty = false;
  return pointCloud->aabb;
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
  pointCloud->aabb_dirty = true;
}

void BkPointCloud_SetOrientation(BkPointCloud* pointCloud,
                                 BkQuaternion const* orientation) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  BK_ASSERT(BK_ISNULL(orientation));
  BkTransform_SetOrientation(&pointCloud->transform, orientation);
  pointCloud->aabb_dirty = true;
}
