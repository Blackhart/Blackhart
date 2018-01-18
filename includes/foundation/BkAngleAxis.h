#ifndef __BK_ANGLE_AXIS_H__
#define __BK_ANGLE_AXIS_H__

// Blackhart.foundation headers.
#include "BkExport.h"
#include "BkAtomicDataType.h"
#include "BkVector3.h"

// Type definitions.
struct BkAngleAxis
{
	real angle;
	struct BkVector3 axis;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Constructs a BkAngleAxis object with the angle and axis components filled.
 *
 * \param angle The angle of rotation. [Must be in degrees]
 * \param axis The axis of rotation. [Must be normalized]
 * \return The new BkAngleAxis object.
 */
extern BK_API struct BkAngleAxis	BkAngleAxis_FromAngleAxis(real const angle, struct BkVector3 const* axis);

/*! \brief Sets the angle of rotation.
 *
 * \param this The BkAngleAxis struct to modify.
 * \param angle The angle of rotation. [Must be in degrees]
 */
extern BK_API void	BkAngleAxis_SetAngle(struct BkAngleAxis* this, real const angle);

/*! \brief Sets the axis of rotation.
 *
 * \param this The BkAngleAxis to modify.
 * \param axis The axis of rotation. [Must be normalized]
 */
extern BK_API void	BkAngleAxis_SetAxis(struct BkAngleAxis* this, struct BkVector3 const* axis);

#endif
