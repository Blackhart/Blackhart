// Standard headers.
#include <stdlib.h>

// Blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkPly.h"
#include "renderer/BkPointCloud.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* const __BkPointCloud_CreateAborted =
    "Point cloud was not created; BkPointCloud_CreateFromPlyFile returned NULL";

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkPointCloud* BkPointCloud_CreateFromPlyFile(char const* filename) {
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

  struct BkPointCloud* pointCloud = malloc(sizeof(struct BkPointCloud));
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
  return pointCloud;
}

void BkPointCloud_Release(struct BkPointCloud** pointCloud) {
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
