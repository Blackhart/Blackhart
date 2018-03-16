#ifndef __BK_EULER_ANGLES_H__
#define __BK_EULER_ANGLES_H__

// Blackhart.foundation headers.
#include "BkExport.h"
#include "BkAtomicDataType.h"

// Forward declarations.
struct BkQuaternion;
struct BkMatrix4x4;

// Type definitions.
struct BkEulerAngles
{
	real x;
	real y;
	real z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Constructs a BkEulerAngle object with the x, y and z components filled.
 *
 * \param x The angle of rotation along the x axis. [Must be in degrees]
 * \param y The angle of rotation along the y axis. [Must be in degrees]
 * \param z The angle of rotation along the z axis. [Must be in degrees]
 * \return The new BkEulerAngle object.
 */
extern BK_API struct BkEulerAngles	BkEulerAngles_FromXYZ(real const x, real const y, real const z);

/*! \brief Constructs a BkEulerAngle object from a BkQuaternion.
 *
 * \param q The BkQuaternion.
 * \return The new BkEulerAngle object.
 */
extern BK_API struct BkEulerAngles	BkEulerAngles_FromBkQuaternion(struct BkQuaternion const* q);

/*! \brief Constructs a BkEulerAngle object from a BkMatrix4x4.
 *
 * \param m The BkMatrix4x4.
 * \return The new BkEulerAngle object.
 */
extern BK_API struct BkEulerAngles	BkEulerAngles_FromBkMatrix4x4(struct BkMatrix4x4 const* m);

/*! \brief Sets the x, y and z components.
 *
 * \param obj The BkEulerAngle to modify.
 * \param x The angle of rotation along the x axis. [Must be in degrees]
 * \param y The angle of rotation along the y axis. [Must be in degrees]
 * \param z The angle of rotation along the z axis. [Must be in degrees]
 */
extern BK_API void	BkEulerAngles_Set(struct BkEulerAngles* obj, real const x, real const y, real const z);

#endif
