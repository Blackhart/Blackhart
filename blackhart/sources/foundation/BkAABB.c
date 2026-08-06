// Blackhart headers.
#include "foundation/BkAABB.h"

#include "foundation/BkError.h"
#include "foundation/BkMath.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkAABB BkAABB_Zero(void) {
  struct BkAABB aabb;
  aabb.min = BkPoint3_Zero();
  aabb.max = BkPoint3_Zero();
  return aabb;
}

struct BkAABB BkAABB_FromMinMax(struct BkPoint3 const* min,
                                struct BkPoint3 const* max) {
  BK_ASSERT(BK_ISNULL(min));
  BK_ASSERT(BK_ISNULL(max));

  struct BkAABB aabb;
  aabb.min = BkPoint3_Copy(min);
  aabb.max = BkPoint3_Copy(max);
  return aabb;
}

void BkAABB_IncludePoint(struct BkAABB* aabb, struct BkPoint3 const* point) {
  BK_ASSERT(BK_ISNULL(aabb));
  BK_ASSERT(BK_ISNULL(point));

  aabb->min.x = BkMath_Min(point->x, aabb->min.x);
  aabb->min.y = BkMath_Min(point->y, aabb->min.y);
  aabb->min.z = BkMath_Min(point->z, aabb->min.z);
  aabb->max.x = BkMath_Max(point->x, aabb->max.x);
  aabb->max.y = BkMath_Max(point->y, aabb->max.y);
  aabb->max.z = BkMath_Max(point->z, aabb->max.z);
}

struct BkAABB BkAABB_FromPoints(struct BkPoint3 const* points,
                                size_t const count) {
  if (BK_ISNULL(points) || count == 0) {
    return BkAABB_Zero();
  }

  struct BkAABB aabb = BkAABB_FromMinMax(&points[0], &points[0]);
  for (size_t i = 1; i < count; ++i) {
    BkAABB_IncludePoint(&aabb, &points[i]);
  }
  return aabb;
}

struct BkPoint3 BkAABB_Center(struct BkAABB const* aabb) {
  BK_ASSERT(BK_ISNULL(aabb));

  return BkPoint3_FromXYZ((aabb->min.x + aabb->max.x) * BK_REAL(0.5),
                          (aabb->min.y + aabb->max.y) * BK_REAL(0.5),
                          (aabb->min.z + aabb->max.z) * BK_REAL(0.5));
}

struct BkVector3 BkAABB_Size(struct BkAABB const* aabb) {
  BK_ASSERT(BK_ISNULL(aabb));

  return BkVector3_FromXYZ(aabb->max.x - aabb->min.x, aabb->max.y - aabb->min.y,
                           aabb->max.z - aabb->min.z);
}

struct BkAABB BkAABB_Union(struct BkAABB const* a, struct BkAABB const* b) {
  BK_ASSERT(BK_ISNULL(a));
  BK_ASSERT(BK_ISNULL(b));

  struct BkAABB result;
  result.min = BkPoint3_FromXYZ(BkMath_Min(a->min.x, b->min.x),
                                BkMath_Min(a->min.y, b->min.y),
                                BkMath_Min(a->min.z, b->min.z));
  result.max = BkPoint3_FromXYZ(BkMath_Max(a->max.x, b->max.x),
                                BkMath_Max(a->max.y, b->max.y),
                                BkMath_Max(a->max.z, b->max.z));
  return result;
}
