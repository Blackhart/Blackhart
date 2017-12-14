#ifndef __BK_MATRIX4X4_H__
#define __BK_MATRIX4X4_H__

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"


struct BkPoint3;
struct BkVector3;

struct BkMatrix4x4
{
    real m11; real m12; real m13; real m14;
    real m21; real m22; real m23; real m24;
    real m31; real m32; real m33; real m34;
    real m41; real m42; real m43; real m44;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Returns a 4x4 identity matrix.
 *
 * \return The 4x4 identity matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Identity();

/*! \brief Multiplies a 4x4 matrix with another 4x4 matrix.
 *
 * \param m1 The first 4x4 matrix.
 * \param m2 The second 4x4 matrix.
 * \return The multplied 4x4 matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Mul_BkMatrix4x4(struct BkMatrix4x4 const* m1, struct BkMatrix4x4 const* m2);

/*! \brief Multiplies a 4x4 matrix with a real number.
 *
 * \param m The 4x4 matrix.
 * \param r The real number.
 * \return The multiplied 4x4 matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Mul_real(struct BkMatrix4x4 const* m, real const r);

/*! \brief Multiplies a 4x4 matrix with a column-order vector3.
 *
 * \param m The 4x4 matrix.
 * \param v The column-order vector3.
 * \return The multiplied column-order vector3.
 */
extern BK_API struct BkVector3		BkMatrix4x4_Mul_BkVector3(struct BkMatrix4x4 const* m, struct BkVector3 const* v);

/*! \brief Multiplies a 4x4 matrix with a column-order point3.
 *
 * \param m The 4x4 matrix.
 * \param p The column-order point3.
 * \return The multiplied column-order point3.
 */
extern BK_API struct BkPoint3		BkMatrix4x4_Mul_BkPoint(struct BkMatrix4x4 const* m, struct BkPoint3 const* p);

/*! \brief Returns a copy of a 4x4 matrix.
 *
 * \param src The 4x4 matrix to copy.
 * \return The copied 4x4 matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Copy(struct BkMatrix4x4 const* src);

/*! \brief Copies a 4x4 matrix into another.
 *
 * \param src The 4x4 matrix to copy.
 * \param dst The 4x4 matrix into which the copy will be made. (Must be allocated)
 */
extern BK_API void			BkMatrix4x4_Assign(struct BkMatrix4x4* dst, struct BkMatrix4x4 const* src);

/*! \brief Transposes a 4x4 matrix.
 *
 * \param m The matrix to transpose.
 * \return The transposed 4x4 matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Transpose(struct BkMatrix4x4 const* m);

/*! \brief Returns a 4x4 rotation matrix rotated along the x axis.
 *
 * \param deg The number of degrees to rotate.
 * \return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotation_x(real const deg);

/*! \brief Returns a 4x4 rotation matrix rotated along the y axis.
 *
 * \param deg The number of degrees to rotate.
 * \return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotation_y(real const deg);

/*! \brief Returns a 4x4 rotation matrix rotated along the z axis.
 *
 * \param deg The number of degrees to rotate.
 * \return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotation_z(real const deg);

/*! \brief Returns a 4x4 rotation matrix.
 *
 * \param x_deg The number of degrees to rotate along the x axis.
 * \param y_deg The number of degrees to rotate along the y axis.
 * \param z_deg The number of degrees to rotate along the z axis.
 * \return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotation_xyz(real const x_deg, real const y_deg, real const z_deg);

/*! \brief Returns a 4x4 rotation matrix rotated along an arbitrary axis.
 *
 * \param v The axis along which to rotate.
 * \param deg The number of degrees to rotate.
 * \return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotation_axis(struct BkVector3 const* v, real const deg);

/*! \brief Returns a 4x4 uniformly scale matrix.
 *
 * \param k The scaling coefficient.
 * \return The 4x4 scale matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Scaling_Uniform(real const k);

/*! \brief Returns a 4x4 non-uniformly scale matrix.
 *
 * \param x The x axis scaling coefficient.
 * \param y The y axis scaling coefficient.
 * \param z The z axis scaling coefficient.
 * \return The 4x4 scale matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Scaling_Nonuniform(real const x, real const y, real const z);

/*! \brief Returns a 4x4 scale matrix scaled along an arbitrary axis.
 *
 * \param v The axis along which to scale.
 * \param k The scaling coefficient.
 * \return The 4x4 scale matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Scaling_axis(struct BkVector3 const* v, real const k);

/*! \brief Returns a 4x4 translation matrix.
 *
 * \param x The number of units to translate along the x axis.
 * \param y The number of units to translate along the y axis.
 * \param z The number of units to translate along the z axis.
 * \return The 4x4 translation matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Translation(real const x, real const y, real const z);

/*! \brief Returns the determinant of a 4x4 matrix.
 *
 * \param m The 4x4 matrix.
 * \return The determinant of the 4x4 matrix.
 */
extern BK_API real			BkMatrix4x4_Determinant(struct BkMatrix4x4 const* m);

/*! \brief Returns the inverse of a 4x4 matrix.
 *
 * \param m The 4x4 matrix.
 * \return The inverted 4x4 matrix.
 */
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Inverse(struct BkMatrix4x4 const* m);

#endif