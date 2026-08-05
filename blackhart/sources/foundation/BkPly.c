// Standard headers.
#include <stdlib.h>

// RPly library headers.
#include <rply.h>

// Blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkPly.h"
#include "foundation/BkPoint3.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* const __BkPly_LoadAborted =
    "Point cloud was not loaded; _BkPly_LoadPoints returned NULL";

static int __BkPly_VertexCallback(p_ply_argument argument) {
  long axis = 0;
  long index = 0;
  struct BkArray* points = NULL;

  ply_get_argument_user_data(argument, (void**)&points, &axis);
  ply_get_argument_element(argument, NULL, &index);

  struct BkPoint3* point = &((struct BkPoint3*)points->data)[index];
  real const value = BK_REAL(ply_get_argument_value(argument));

  if (axis == 0)
    point->x = value;
  else if (axis == 1)
    point->y = value;
  else
    point->z = value;

  return 1;
}

static void __BkPly_ReleasePoints(struct BkArray** points) {
  if (BK_ISNULL(points) || BK_ISNULL(*points)) return;

  BkArray_Destroy(*points);
  free(*points);
  *points = NULL;
}

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkArray* _BkPly_LoadPoints(char const* filename) {
  BK_ERROR(BK_ISNULL(filename),
           ((struct BkErrorInfo){
               .what = "Cannot load PLY points",
               .why = "filename argument is NULL",
               .how = "Pass a non-NULL path to an existing PLY file",
               .result = __BkPly_LoadAborted,
           }),
           NULL);

  p_ply ply = ply_open(filename, NULL, 0, NULL);
  BK_ERROR(
      BK_ISNULL(ply),
      ((struct BkErrorInfo){
          .what = "Cannot open PLY file",
          .why = "File does not exist, is not readable, or is not a valid PLY",
          .where = filename,
          .how = "Check the path, file permissions, and that the file starts "
                 "with 'ply'",
          .result = __BkPly_LoadAborted,
      }),
      NULL);

  if (ply_read_header(ply) == 0) {
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot parse PLY header",
                 .why = "Header is missing, incomplete, or malformed (expected "
                        "'end_header')",
                 .where = filename,
                 .how = "Re-export the asset with a complete PLY header ending "
                        "with 'end_header'",
                 .result = __BkPly_LoadAborted,
             }),
             NULL);
  }

  struct BkArray* points = malloc(sizeof(struct BkArray));
  if (BK_ISNULL(points)) {
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot allocate point buffer",
                 .why = "Out of memory while allocating BkArray for vertices",
                 .where = filename,
                 .how = "Free memory or reduce the size of the point cloud",
                 .result = __BkPly_LoadAborted,
             }),
             NULL);
  }
  BkArray_Initialize(points, (uint8)sizeof(struct BkPoint3));

  long const nvertices =
      ply_set_read_cb(ply, "vertex", "x", __BkPly_VertexCallback, points, 0);
  if (nvertices <= 0 ||
      ply_set_read_cb(ply, "vertex", "y", __BkPly_VertexCallback, points, 1) <=
          0 ||
      ply_set_read_cb(ply, "vertex", "z", __BkPly_VertexCallback, points, 2) <=
          0) {
    __BkPly_ReleasePoints(&points);
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot find PLY vertex positions",
                 .why = "Missing element 'vertex' or properties 'x'/'y'/'z', "
                        "or vertex count is 0",
                 .where = filename,
                 .how = "Export with 'element vertex N' (N > 0) and scalar "
                        "properties x, y, z",
                 .result = __BkPly_LoadAborted,
             }),
             NULL);
  }

  struct BkPoint3 const zero = BkPoint3_Zero();
  BkArray_Resize_t(points, (size_t)nvertices, (char const*)&zero);

  if (ply_read(ply) == 0) {
    __BkPly_ReleasePoints(&points);
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot read PLY vertex data",
                 .why = "Payload after the header is corrupt or does not match "
                        "the header",
                 .where = filename,
                 .how = "Re-export the PLY or verify vertex count and property "
                        "types match the header",
                 .result = __BkPly_LoadAborted,
             }),
             NULL);
  }

  ply_close(ply);
  return points;
}
