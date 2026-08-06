// Standard headers.
#include <stdlib.h>
#include <string.h>

// RPly library headers.
#include <rply.h>

// Blackhart headers.
#include "foundation/BkColor3.h"
#include "foundation/BkError.h"
#include "foundation/BkPly.h"
#include "foundation/BkPoint3.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* const __BkPly_LoadPointsAborted =
    "Point cloud was not loaded; _BkPly_LoadPoints returned NULL";

static char const* const __BkPly_LoadColorsAborted =
    "Colors were not loaded; _BkPly_LoadColors returned NULL";

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

static int __BkPly_ColorCallback(p_ply_argument argument) {
  long channel = 0;
  long index = 0;
  struct BkArray* colors = NULL;

  ply_get_argument_user_data(argument, (void**)&colors, &channel);
  ply_get_argument_element(argument, NULL, &index);

  struct BkColor3* color = &((struct BkColor3*)colors->data)[index];
  uint8 const value = (uint8)ply_get_argument_value(argument);

  if (channel == 0)
    color->r = value;
  else if (channel == 1)
    color->g = value;
  else
    color->b = value;

  return 1;
}

static void __BkPly_ReleaseArray(struct BkArray** array) {
  if (BK_ISNULL(array) || BK_ISNULL(*array)) return;

  BkArray_Destroy(*array);
  free(*array);
  *array = NULL;
}

static bool __BkPly_HasVertexProperty(p_ply ply, char const* property_name) {
  p_ply_element element = NULL;

  while ((element = ply_get_next_element(ply, element)) != NULL) {
    char const* element_name = NULL;
    long ninstances = 0;
    ply_get_element_info(element, &element_name, &ninstances);

    if (element_name == NULL || strcmp(element_name, "vertex") != 0) {
      continue;
    }

    p_ply_property property = NULL;
    while ((property = ply_get_next_property(element, property)) != NULL) {
      char const* name = NULL;
      ply_get_property_info(property, &name, NULL, NULL, NULL);
      if (name != NULL && strcmp(name, property_name) == 0) {
        return true;
      }
    }
  }

  return false;
}

static p_ply __BkPly_OpenWithHeader(char const* filename,
                                    char const* const aborted_result) {
  BK_ERROR(BK_ISNULL(filename),
           ((struct BkErrorInfo){
               .what = "Cannot load PLY file",
               .why = "filename argument is NULL",
               .how = "Pass a non-NULL path to an existing PLY file",
               .result = aborted_result,
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
          .result = aborted_result,
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
                 .result = aborted_result,
             }),
             NULL);
  }

  return ply;
}

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkArray* _BkPly_LoadPoints(char const* filename) {
  p_ply ply = __BkPly_OpenWithHeader(filename, __BkPly_LoadPointsAborted);
  if (BK_ISNULL(ply)) {
    return NULL;
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
                 .result = __BkPly_LoadPointsAborted,
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
    __BkPly_ReleaseArray(&points);
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot find PLY vertex positions",
                 .why = "Missing element 'vertex' or properties 'x'/'y'/'z', "
                        "or vertex count is 0",
                 .where = filename,
                 .how = "Export with 'element vertex N' (N > 0) and scalar "
                        "properties x, y, z",
                 .result = __BkPly_LoadPointsAborted,
             }),
             NULL);
  }

  struct BkPoint3 const zero = BkPoint3_Zero();
  BkArray_Resize_t(points, (size_t)nvertices, (char const*)&zero);

  if (ply_read(ply) == 0) {
    __BkPly_ReleaseArray(&points);
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot read PLY vertex data",
                 .why = "Payload after the header is corrupt or does not match "
                        "the header",
                 .where = filename,
                 .how = "Re-export the PLY or verify vertex count and property "
                        "types match the header",
                 .result = __BkPly_LoadPointsAborted,
             }),
             NULL);
  }

  ply_close(ply);
  return points;
}

struct BkArray* _BkPly_LoadColors(char const* filename) {
  p_ply ply = __BkPly_OpenWithHeader(filename, __BkPly_LoadColorsAborted);
  if (BK_ISNULL(ply)) {
    return NULL;
  }

  bool const has_colors = __BkPly_HasVertexProperty(ply, "red") &&
                          __BkPly_HasVertexProperty(ply, "green") &&
                          __BkPly_HasVertexProperty(ply, "blue");
  if (!has_colors) {
    ply_close(ply);
    return NULL;
  }

  struct BkArray* colors = malloc(sizeof(struct BkArray));
  if (BK_ISNULL(colors)) {
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot allocate color buffer",
                 .why = "Out of memory while allocating BkArray for colors",
                 .where = filename,
                 .how = "Free memory or reduce the size of the point cloud",
                 .result = __BkPly_LoadColorsAborted,
             }),
             NULL);
  }
  BkArray_Initialize(colors, (uint8)sizeof(struct BkColor3));

  long const nvertices =
      ply_set_read_cb(ply, "vertex", "red", __BkPly_ColorCallback, colors, 0);
  if (nvertices <= 0 ||
      ply_set_read_cb(ply, "vertex", "green", __BkPly_ColorCallback, colors,
                      1) <= 0 ||
      ply_set_read_cb(ply, "vertex", "blue", __BkPly_ColorCallback, colors,
                      2) <= 0) {
    __BkPly_ReleaseArray(&colors);
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot bind PLY vertex colors",
                 .why = "red/green/blue properties were detected but could "
                        "not be registered",
                 .where = filename,
                 .how = "Re-export with uchar (or compatible) red, green, "
                        "blue vertex properties",
                 .result = __BkPly_LoadColorsAborted,
             }),
             NULL);
  }

  struct BkColor3 const black = BkColor3_FromRGB(0, 0, 0);
  BkArray_Resize_t(colors, (size_t)nvertices, (char const*)&black);

  if (ply_read(ply) == 0) {
    __BkPly_ReleaseArray(&colors);
    ply_close(ply);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot read PLY color data",
                 .why = "Payload after the header is corrupt or does not match "
                        "the header",
                 .where = filename,
                 .how = "Re-export the PLY or verify vertex count and property "
                        "types match the header",
                 .result = __BkPly_LoadColorsAborted,
             }),
             NULL);
  }

  ply_close(ply);
  return colors;
}
