#ifndef __BK_POINT3_H__
#define __BK_POINT3_H__

// Blackhart.foundation headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkVector3.h"

// Type definitions.
struct BkPoint3
{
	real	x;
	real	y;
	real	z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Constructs a BkPoint3 object with its x, y and z components set to 0.
 *
 * \return The new BkPoint3 object.
 */
extern BK_API struct BkPoint3	BkPoint3_Zero(void);

/*! \brief Constructs a BkPoint3 object with its x, y and z components filled.
 *
 * \param x The cartesian coordinate along the x axis.
 * \param y The cartesian coordinate along the y axis.
 * \param z The cartesian coordinate along the z axis.
 * \return The new BkPoint3 object.
 */
extern BK_API struct BkPoint3	BkPoint3_FromXYZ(real const x, real const y, real const z);

/*! \brief Sets the x, y and z components.
 *
 * \param obj The BkPoint3 object to modify.
 * \param x The cartesian coordinate along the x axis.
 * \param y The cartesian coordinate along the y axis.
 * \param z The cartesian coordinate along the z axis.
 */
extern BK_API void		BkPoint3_Set(struct BkPoint3* obj, real const x, real const y, real const z);

/*! \brief Copies a BkPoint3 object.
 *
 * \param src The BkPoint3 object to copy.
 * return The new BkPoint3 object.
 */
extern BK_API struct BkPoint3	BkPoint3_Copy(struct BkPoint3 const* src);

/*! \brief Copies a BkPoint3 object into one another.
 *
 * \param obj The BkPoint3 object into which the data will be copied.
 * \param src The BkPoint3 object to copy.
 */
extern BK_API void		BkPoint3_Assign(struct BkPoint3* obj, struct BkPoint3 const* src);

/*! \brief Addition a BkPoint3 and a BkVector3.
 *
 * Translate the point.
 *
 * \param a The BkPoint3.
 * \param b The BkVector3.
 * \return The new BkPoint3.
 */
extern BK_API struct BkPoint3	BkPoint3_Add_BkVector3(struct BkPoint3 const* a, struct BkVector3 const* b);

/*! \brief Substracts a BkPoint3 and a BkVector3.
 *
 * Translate the point.
 *
 * \param a The BkPoint3.
 * \param b The BkVector3.
 * \return The new BkPoint3.
 */
extern BK_API struct BkPoint3	BkPoint3_Sub_BkVector3(struct BkPoint3 const* a, struct BkVector3 const* b);

/*! \brief Substracts a BkPoint3 and a BkVector3.
 *
 * Return the delta of the distance between the first point and the second one.
 *
 * \param a The first BkPoint3.
 * \param b The second BkPoint3.
 * \return the delta of the distance between the first point and the second one.
 */
extern BK_API struct BkVector3	BkPoint3_Sub_BkPoint3(struct BkPoint3 const* a, struct BkPoint3 const* b);

/*! \brief Returns the distance between two points.
 *
 * \param a The first point.
 * \param b The second point.
 * \return The distance.
 */
extern BK_API real		BkPoint3_Distance(struct BkPoint3 const* a, struct BkPoint3 const* b);

/*! \brief Returns linear interpolation of two points based on t.
 *
 * \param from The first point.
 * \param to The second point.
 * \param t The interpolent.
 * \return The interpolated position.
 */
extern BK_API struct BkPoint3	BkPoint3_Lerp(struct BkPoint3 const* from, struct BkPoint3 const* to, real const t);

#endif
