// Standard headers.
#include <stdlib.h>

// Blackhart headers.
#include "foundation/BkArray.h"
#include "foundation/BkError.h"
#include "foundation/BkPly.h"
#include "foundation/BkPoint3.h"
#include "renderer/BkPointCloud.h"

// ~~~~~ Type Definitions ~~~~~

struct BkPointCloud {
  struct BkArray* points;
  BkAABB aabb;
};

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* const __BkPointCloud_CreateAborted =
    "Point cloud was not created; BkPointCloud_CreateFromPlyFile returned NULL";

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

  BkPointCloud* pointCloud = malloc(sizeof(BkPointCloud));
  if (BK_ISNULL(pointCloud)) {
    BkArray_Destroy(points);
    free(points);
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
  pointCloud->aabb =
      BkAABB_FromPoints((BkPoint3 const*)points->data, BkArray_Size((*points)));
  return pointCloud;
}

void BkPointCloud_Release(BkPointCloud** pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  BK_ASSERT(BK_ISNULL(*pointCloud));

  if ((*pointCloud)->points != NULL) {
    BkArray_Destroy((*pointCloud)->points);
    free((*pointCloud)->points);
    (*pointCloud)->points = NULL;
  }

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

BkAABB BkPointCloud_GetAABB(BkPointCloud const* pointCloud) {
  BK_ASSERT(BK_ISNULL(pointCloud));
  return pointCloud->aabb;
}
