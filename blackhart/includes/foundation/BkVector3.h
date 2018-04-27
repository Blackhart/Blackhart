#ifndef __BK_VECTOR3_H__
#define __BK_VECTOR3_H__

// blackhart headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"

// Forward declarations.
struct BkPoint3;

// Type definitions.
struct BkVector3
{
    real    x;
    real    y;
    real    z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Constructs a BkVector3 object with its x, y and z components set to 0.
 *
 * \return The new BkVector3 object.
 */
extern BK_API struct BkVector3	BkVector3_Zero(void);

/*! \brief Constructs a BkVector3 object with its x, y and z components filled.
 *
 * \param x The cartesian coordinate along the x axis.
 * \param y The cartesian coordinate along the y axis.
 * \param z The cartesian coordinate along the z axis.
 * \return The new BkVector3 object.
 */
extern BK_API struct BkVector3	BkVector3_FromXYZ(real const x, real const y, real const z);

/*! \brief Additions two BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The new BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Add_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Substracts two BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The new BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Sub_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Multiplies a BkVector3 with a real number.
 *
 * \param a The BkVector3.
 * \param b The real number.
 * \return The new BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Mul_Real(struct BkVector3 const* a, real b);

/*! \brief Divides a BkVector3 with a real number.
 *
 * \param a The BkVector3.
 * \param b The real number.
 * \return The new BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Div_Real(struct BkVector3 const* a, real b);

/*! \brief Computes the magnitude of a BkVector3.
 *
 * Magnitude is equal to the length of the vector.
 *
 * \param a The BkVector3.
 * \return The magnitude.
 */
extern BK_API real	BkVector3_Magnitude(struct BkVector3 const* a);

/*! \brief Sets the x, y and z components.
 *
 * \param obj The BkVector3 object to modify.
 * \param x The cartesian coordinate along the x axis.
 * \param y The cartesian coordinate along the y axis.
 * \param z The cartesian coordinate along the z axis.
 */
extern BK_API void	BkVector3_Set(struct BkVector3* obj, real const x, real const y, real const z);

/*! \brief Copies a BkVector3.
 *
 * \param src The BkVector3 to copy.
 * return The new BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Copy(struct BkVector3 const* src);

/*! \brief Copies a BkVector3 into one another.
*
* \param obj The BkVector3 into which the data will be copied.
* \param src The BkVector3 to copy.
*/
extern BK_API void	BkVector3_Assign(struct BkVector3* __restrict obj, struct BkVector3 const* __restrict src);

/*! \brief Returns the dot product of two BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The dot product.
 */
extern BK_API real	BkVector3_Dot(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Returns the absolute dot product of two BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The absolute dot product.
 */
extern BK_API real	BkVector3_AbsDot(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Returns the cross product of two BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The cross product.
 */
extern BK_API struct BkVector3	BkVector3_Cross(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Negates all the components of a BkVector3.
 *
 * \param obj The BkVector3 to negate.
 */
extern BK_API void	BkVector3_Negated(struct BkVector3* obj);

/*! \brief Negates all the components of a BkVector3.
 *
 * \param a The BkVector3 to negate.
 * \return The negated BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Negate(struct BkVector3 const* a);

/*! \brief Returns the angles in degrees between two BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The angle in degrees.
 */
extern BK_API real	BkVector3_Angle(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Normalizes a BkVector3.
 *
 * \param obj The BkVector3 to normalize.
 */
extern BK_API void	BkVector3_Normalized(struct BkVector3* obj);

/*! \brief Normalizes a BkVector3.
 *
 * \param a The BkVector3 to normalize.
 * \return The normalized BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Normalize(struct BkVector3 const* a);

/*! \brief Returns linear interpolation of two BkVector3 based on t.
 *
 * \param from The first BkVector3.
 * \param to The second BkVector3.
 * \param t The interpolent.
 * \return The interpolated BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Lerp(struct BkVector3 const* from, struct BkVector3 const* to, real const t);

/*! \brief Returns the longest BkVector3.
 *
 * Based on the magnitude of each BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The longest BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Max(struct BkVector3 const* a, struct BkVector3 const* b);

/*! \brief Returns the shortest BkVector3.
 *
 * Based on the magnitude of each BkVector3.
 *
 * \param a The first BkVector3.
 * \param b The second BkVector3.
 * \return The shortest BkVector3.
 */
extern BK_API struct BkVector3	BkVector3_Min(struct BkVector3 const* a, struct BkVector3 const* b);

#endif