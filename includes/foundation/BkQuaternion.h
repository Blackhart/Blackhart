#ifndef __BK_QUATERNION_H__
#define __BK_QUATERNION_H__

// Blackhart.foundation headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkError.h"

// Forward declarations.
struct BkVector3;
struct BkMatrix4x4;
struct BkEulerAngles;
struct BkAngleAxis;

// Type definitions
struct BkQuaternion
{
	real w;
	real x;
	real y;
	real z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Returns an identity quaternion.
*
* \return The identity quaternion.
*/
extern BK_API struct BkQuaternion	BkQuaternion_Identity(void);

/*! \brief Multiplies two quaternions.
 *
 * Performs the following operation:
 *	ret = q1 * q2.
 *
 * Quaternion multiplication isn't commutative; 
 *	q1 * q2 =/= q2 * q1.
 *
 * Quaternion multiplication is associative;
 *	(q1 * q2) * q3 == q1 * (q2 * q3).
 *
 * \param q1 The first quaternion to multiply.
 * \param q2 The second quaternion to multiply.
 * \return The multiplied quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Mul_BkQuaternion(struct BkQuaternion const* q1, struct BkQuaternion const* q2);

/*! \brief Constructs a quaternion from an angle axis representation.
 *
 * \param angle_axis The angle axis.
 * \return The newly created quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_FromAngleAxis(struct BkAngleAxis const* angle_axis);

/*! \brief Constructs a quaternion from a 4x4 column order matrix representation.
 *
 * \param m The 4x4 column order matrix.
 * \return The newly created 4x4 column order matrix.
 */
extern BK_API struct BkQuaternion	BkQuaternion_FromBkMatrix4x4(struct BkMatrix4x4 const* m);

/*! \brief Constructs a quaternion from an euler angles representation.
 *
 * \param euler The euler angles.
 * \return The newly created quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_FromEulerAngles(struct BkEulerAngles const* euler);

/*! \brief Copies a quaternion.
 *
 * \param q The quaternion to copy.
 * \return The newly created quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Copy(struct BkQuaternion const* q);

/*! \brief Sets x, y, z and w components of a quaternion and returns it.
 *
 * \param this The quaternion to modify.
 * \param w W component.
 * \param x X component.
 * \param y Y component.
 * \param z Z component.
 */
extern BK_API void	BkQuaternion_Set(struct BkQuaternion* this, real const w, real const x, real const y, real const z);

/*! \brief Normalizes a quaternion.
 *
 * \param this The quaternion to normalize.
 */
extern BK_API void	BkQuaternion_Normalized(struct BkQuaternion* this);

/*! \brief Normalizes a quaternion.
 *
 * \param q The quaternion to normalize.
 * \return The normalized quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Normalize(struct BkQuaternion const* q);

/*! \brief Negates a quaternion.
*
* \param this The quaternion to negate.
*/
extern BK_API void	BkQuaternion_Negated(struct BkQuaternion* this);

/*! \brief Negates a quaternion.
 *
 * \param q The quaternion to negate.
 * \return The negated quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Negate(struct BkQuaternion const* q);

/*! \brief Returns the magnitude of a quaternion.
 *
 * \param q The quaternion.
 * \return The magnitude of the quaternion.
 */
extern BK_API real	BkQuaternion_Magnitude(struct BkQuaternion const* q);

/*! \brief Returns the conjugate quaternion of the quaternion passed as input.
*
* Conjugate method flip the direction that we consider to be positive rotation.
*
* As an example:
*	Instead of rotating an object from left to right, it rotates it from right to left.
*
* \param this The quaternion to conjugate.
*/
extern BK_API void	BkQuaternion_Conjugated(struct BkQuaternion* this);

/*! \brief Returns the conjugate quaternion of the quaternion passed as input.
 *
 * Conjugate method flip the direction that we consider to be positive rotation.
 * 
 * As an example:
 *	Instead of rotating an object from left to right, it rotates it from right to left.
 *
 * \param q The quaternion to conjugate.
 * \return The conjugated quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Conjugate(struct BkQuaternion const* q);

/*! \brief Returns the inverse quaternion of the quaternion passed as input.
*
* \param this The quaternion to inverse.
*/
extern BK_API void	BkQuaternion_Inversed(struct BkQuaternion* this);

/*! \brief Returns the inverse quaternion of the quaternion passed as input.
 *
 * \param q The quaternion to inverse.
 * \return The inversed quaternion.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Inverse(struct BkQuaternion const* q);

/*! \brief Returns the difference between two quaternions.
 *
 * Computes the angular displacement that rotates from q1 to q2.
 *
 * Quaternion difference isn't commutative:
 *	diff(q1, q2) =/= diff(q2, q1)
 *
 * \param q1 The first quaternion.
 * \param q2 The second quaternion.
 * \return The difference between the two quaternions.
 */
extern BK_API struct BkQuaternion	BkQuaternion_Difference(struct BkQuaternion const* q1, struct BkQuaternion const* q2);

/*! \brief Returns the dot product of two quaternions.
 *
 * \param q1 The first quaternion.
 * \param q2 The second quaternion.
 * \return The dot product of the two quaternions.
 */
extern BK_API real	BkQuaternion_Dot(struct BkQuaternion const* q1, struct BkQuaternion const* q2);

#endif
