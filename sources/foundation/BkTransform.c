// Blackhart.foundation headers.
#include "foundation\BkTransform.h"
#include "foundation\BkMatrix4x4.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkVector3	BkTransform_Forward(struct BkMatrix4x4 const* m)
{
	return (struct BkVector3) {
		.x = m->m13,
		.y = m->m23,
		.z = m->m33
	};
}

struct BkVector3	BkTransform_Right(struct BkMatrix4x4 const* m)
{
	return (struct BkVector3) {
		.x = m->m11,
		.y = m->m21,
		.z = m->m31
	};
}

struct BkVector3	BkTransform_Up(struct BkMatrix4x4 const* m)
{
	return (struct BkVector3) {
		.x = m->m12,
		.y = m->m22,
		.z = m->m32
	};
}

struct BkPoint3	BkTransform_Position(struct BkMatrix4x4 const* m)
{
	return (struct BkPoint3) {
		.x = m->m14,
		.y = m->m24,
		.z = m->m34
	};
}