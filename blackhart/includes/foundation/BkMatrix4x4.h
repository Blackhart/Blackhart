#ifndef __BK_MATRIX4X4_H__
#define __BK_MATRIX4X4_H__

/**
 * @file BkMatrix4x4.h
 * @brief Defines the BkMatrix4x4 structure and functions for 4x4 matrix
 * operations.
 *
 * This file provides the definition of the BkMatrix4x4 struct and comprehensive
 * matrix operations including multiplication, transformations, rotations,
 * scaling, translation, and matrix inversion.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"
#include "foundation/BkPoint3.h"
#include "foundation/BkVector3.h"

// ~~~~~ Forward declarations ~~~~~

struct BkQuaternion;
struct BkAngleAxis;
struct BkEulerAngles;

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkMatrix4x4
 * @brief Structure representing a 4x4 matrix in column-major order.
 *
 * The matrix is stored in column-major order, which is the standard format for
 * OpenGL. The matrix elements are accessed as m[row][column], where m11 is row
 * 1, column 1.
 */
struct BkMatrix4x4 {
  real m11;
  real m12;
  real m13;
  real m14; /**< First row of the matrix. */
  real m21;
  real m22;
  real m23;
  real m24; /**< Second row of the matrix. */
  real m31;
  real m32;
  real m33;
  real m34; /**< Third row of the matrix. */
  real m41;
  real m42;
  real m43;
  real m44; /**< Fourth row of the matrix. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Returns a 4x4 identity matrix.
 *
 * The identity matrix is a square matrix with ones on the main diagonal and
 * zeros elsewhere. Multiplying any matrix by the identity matrix returns the
 * original matrix.
 *
 * @return The 4x4 identity matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Identity(void);

/**
 * @brief Multiplies a 4x4 matrix with another 4x4 matrix.
 *
 * Performs matrix multiplication: result = m1 * m2.
 *
 * Matrix multiplication is not commutative: m1 * m2 ≠ m2 * m1.
 * Matrix multiplication is associative: (m1 * m2) * m3 == m1 * (m2 * m3).
 *
 * @param m1 Pointer to the first 4x4 matrix.
 * @param m2 Pointer to the second 4x4 matrix.
 * @return The result of multiplying m1 by m2.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Mul_BkMatrix4x4(
    struct BkMatrix4x4 const* m1, struct BkMatrix4x4 const* m2);

/**
 * @brief Multiplies a 4x4 matrix by a scalar real number.
 *
 * Performs scalar multiplication: result = m * r.
 * Each element of the matrix is multiplied by the scalar value.
 *
 * @param m Pointer to the 4x4 matrix.
 * @param r The scalar real number to multiply by.
 * @return The matrix multiplied by the scalar.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Mul_real(
    struct BkMatrix4x4 const* m, real const r);

/**
 * @brief Multiplies a 4x4 matrix with a column-order vector3.
 *
 * Performs matrix-vector multiplication: result = m * v.
 * The vector is treated as a column vector with an implicit w component of 0.
 *
 * @param m Pointer to the 4x4 matrix.
 * @param v Pointer to the column-order vector3.
 * @return The transformed vector3.
 */
extern BK_API struct BkVector3 BkMatrix4x4_Mul_BkVector3(
    struct BkMatrix4x4 const* m, struct BkVector3 const* v);

/**
 * @brief Multiplies a 4x4 matrix with a column-order point3.
 *
 * Performs matrix-point multiplication: result = m * p.
 * The point is treated as a column vector with an implicit homogeneous w
 * component of 1.0, meaning translations will be applied to the point.
 *
 * @param m Pointer to the 4x4 matrix.
 * @param p Pointer to the column-order point3.
 * @return The transformed point3.
 */
extern BK_API struct BkPoint3 BkMatrix4x4_Mul_BkPoint3(
    struct BkMatrix4x4 const* m, struct BkPoint3 const* p);

/**
 * @brief Multiplies a 4x4 matrix with a column-order point4 (homogeneous
 * coordinates).
 *
 * Performs matrix-point multiplication: result = m * p.
 * The point is treated as a homogeneous coordinate with an explicit w component
 * of 1.0. This allows full 4D transformations including perspective
 * projections.
 *
 * @param m Pointer to the 4x4 matrix.
 * @param p Pointer to the column-order point3 representing a point4 with w=1.0.
 * @return The transformed point3 after perspective divide.
 */
extern BK_API struct BkPoint3 BkMatrix4x4_Mul_BkPoint4(
    struct BkMatrix4x4 const* m, struct BkPoint3 const* p);

/**
 * @brief Constructs a 4x4 rotation matrix from a quaternion.
 *
 * Converts a quaternion rotation to a 4x4 rotation matrix in column-major
 * order.
 *
 * @param q Pointer to the quaternion representing the rotation.
 * @return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_FromBkQuaternion(
    struct BkQuaternion const* q);

/**
 * @brief Constructs a 4x4 rotation matrix from an angle-axis representation.
 *
 * Creates a rotation matrix that rotates around an arbitrary axis by a
 * specified angle.
 *
 * @param angle_axis Pointer to the angle-axis structure containing the rotation
 * angle (in degrees) and the normalized axis vector.
 * @return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_FromBkAngleAxis(
    struct BkAngleAxis const* angle_axis);

/**
 * @brief Constructs a 4x4 rotation matrix from Euler angles.
 *
 * Creates a rotation matrix from Euler angles in degrees. The rotation order is
 * typically ZYX (yaw-pitch-roll) or XYZ depending on the implementation.
 *
 * @param euler Pointer to the Euler angles structure containing x, y, z
 * rotation angles (in degrees).
 * @return The 4x4 rotation matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_FromBkEulerAngles(
    struct BkEulerAngles const* euler);

/**
 * @brief Creates a copy of a 4x4 matrix.
 *
 * @param src Pointer to the source 4x4 matrix to copy.
 * @return A new BkMatrix4x4 containing a copy of the source matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Copy(
    struct BkMatrix4x4 const* src);

/**
 * @brief Copies a 4x4 matrix into another existing matrix.
 *
 * Assigns the values from the source matrix to the destination matrix.
 * The destination matrix must already be allocated.
 *
 * @param obj Pointer to the destination matrix (must be allocated).
 * @param src Pointer to the source matrix to copy from.
 */
extern BK_API void BkMatrix4x4_Assign(struct BkMatrix4x4* __restrict obj,
                                      struct BkMatrix4x4 const* __restrict src);

/**
 * @brief Transposes a 4x4 matrix.
 *
 * Transposing a matrix swaps its rows and columns. A column-major matrix
 * becomes a row-major matrix and vice versa. For rotation matrices, the
 * transpose equals the inverse.
 *
 * @param m Pointer to the matrix to transpose.
 * @return The transposed 4x4 matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Transpose(
    struct BkMatrix4x4 const* m);

/**
 * @brief Creates a 4x4 uniform scaling matrix.
 *
 * Creates a scaling matrix that scales equally along all three axes.
 *
 * @param k The uniform scaling coefficient. Values > 1.0 scale up, values < 1.0
 * scale down.
 * @return The 4x4 uniform scaling matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Scaling_Uniform(real const k);

/**
 * @brief Creates a 4x4 non-uniform scaling matrix.
 *
 * Creates a scaling matrix that scales differently along each axis.
 *
 * @param x The scaling coefficient along the x-axis.
 * @param y The scaling coefficient along the y-axis.
 * @param z The scaling coefficient along the z-axis.
 * @return The 4x4 non-uniform scaling matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Scaling_Nonuniform(real const x,
                                                                real const y,
                                                                real const z);

/**
 * @brief Creates a 4x4 scaling matrix along an arbitrary axis.
 *
 * Creates a scaling matrix that scales along a specified axis vector.
 *
 * @param v Pointer to the normalized axis vector along which to scale.
 * @param k The scaling coefficient along the specified axis.
 * @return The 4x4 scaling matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Scaling_axis(
    struct BkVector3 const* v, real const k);

/**
 * @brief Creates a 4x4 translation matrix from x, y, z values.
 *
 * Creates a translation matrix that translates by the specified amounts along
 * each axis.
 *
 * @param x The translation amount along the x-axis.
 * @param y The translation amount along the y-axis.
 * @param z The translation amount along the z-axis.
 * @return The 4x4 translation matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Translation_XYZ(real const x,
                                                             real const y,
                                                             real const z);

/**
 * @brief Creates a 4x4 translation matrix from a BkVector3.
 *
 * Creates a translation matrix that translates by the amounts specified in the
 * vector.
 *
 * @param v Pointer to the translation vector.
 * @return The 4x4 translation matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Translation_BkVector3(
    struct BkVector3 const* v);

/**
 * @brief Creates a 4x4 translation matrix from a BkPoint3.
 *
 * Creates a translation matrix that translates to the position specified by the
 * point.
 *
 * @param v Pointer to the position point.
 * @return The 4x4 translation matrix.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Translation_BkPoint3(
    struct BkPoint3 const* v);

/**
 * @brief Computes the determinant of a 4x4 matrix.
 *
 * The determinant is a scalar value that can be used to determine if a matrix
 * is invertible. A matrix with a determinant of zero is singular and cannot be
 * inverted.
 *
 * @param m Pointer to the 4x4 matrix.
 * @return The determinant of the matrix.
 */
extern BK_API real BkMatrix4x4_Determinant(struct BkMatrix4x4 const* m);

/**
 * @brief Computes the inverse of a 4x4 matrix.
 *
 * The inverse matrix, when multiplied by the original matrix, yields the
 * identity matrix. The matrix must be invertible (determinant != 0) for this
 * operation to succeed.
 *
 * @param m Pointer to the 4x4 matrix to invert.
 * @return The inverted 4x4 matrix.
 *
 * @note If the matrix is singular (determinant = 0), the result is undefined.
 */
extern BK_API struct BkMatrix4x4 BkMatrix4x4_Inverse(
    struct BkMatrix4x4 const* m);

#endif