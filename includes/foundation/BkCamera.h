#ifndef __BK_CAMERA_H__
#define __BK_CAMERA_H__

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkMath.h"


// ~~~~~ REFERENCES ~~~~~

/*! Shutter speed 
 *
 * 1s
 * 1/2s
 * 1/4s
 * 1/8s
 * 1/15s
 * 1/30s
 * 1/60s
 * 1/125s
 * 1/250s
 * 1/500s
 * 1/1000s
 *
 */

/*! Aperture 
 *
 * f/1.4
 * f/2
 * f/2.8
 * f/4
 * f/5.6
 * f/8
 * f/11
 * f/16
 * f/22
 * f/32
 *
 */

/*! Sensor sizes 
 *
 * Full Frame: 36.0mm X 24.0mm
 * APS-H (Canon): 28.70mm X 19.00mm
 * APS-C: 23.60mm X 15.70mm
 * APS-C (Canon): 22.20mm X 14.80mm
 * Foveon (Sigma): 20.7mm X 13.8mm
 * Four Thirds System (Olympus, Panasonic): 17.3mm X 13mm
 * 1" (Nikon, Sony): 13.2mm X 8.8mm
 * 2/3" (Fuji, Nokia): 8.6mm X 6.6mm
 * 1/1.7": 7.6mm X 5.7mm
 * 1/2.5": 5.76mm X 4.29mm
 *
 */

enum BkCamera_Mode
{
	AUTOMATIC = 0,
	SPEED_PRIORITY,
	APERTURE_PRIORITY
};

struct BkCamera_Transform
{
	struct BkMatrix4x4	cam_to_world;
	struct BkMatrix4x4	world_to_cam;
};

struct BkCamera_Lens
{
	real	aperture;
	uint16	focal_length; 
};

struct BkCamera_Sensor
{
	real	sensor_width;
	real	sensor_height;
	uint16	resolution_width;
	uint16	resolution_height;
	uint16	iso;
};

struct BKCamera_Motor
{
	real	shutter_speed;
};

struct BkCamera
{
	struct BkCamera_Transform	transform;
	enum BkCamera_Mode		mode;
	struct BkCamera_Sensor		sensor;
	struct BKCamera_Motor		motor;
	struct BkCamera_Lens		lens;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkCamera_Initialize(struct BkCamera* camera);
extern BK_API void	BkCamera_LookAt(struct BkCamera* camera, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up);

#endif
