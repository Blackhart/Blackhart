#ifndef __BK_VECTOR_H__
#define __BK_VECTOR_H__

#include <string.h>

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

/*! \brief Checks if the BkVector has no elements
*
* \param v The container
* \return TRUE if the BkVector is empty, FALSE otherwise
*/
#define BkVector_Empty(v)		(BkVector_Size(v) == 0)

/*! \brief Gets the size of a BkVector
*
* \param v The container
* \return The size of the container
*/
#define BkVector_Size(v)		(v.size)

/*! \brief Gets the capacity of a BkVector
*
* \param v The container
* \return The capacity of the container
*/
#define BkVector_Capacity(v)		(v.capacity)

/*! \brief Gets the data at a given position in a BkVector
*
* \param v The container
* \param t The type of the data
* \param i The position of the data in the vector
* \return The data at the specified position in the container
*/
#define BkVector_At(v, t, i)		(((t*)v.data)[i])

/*! \brief Gets the first element in a BkVector
*
* \param v The container
* \param t The type of the data
* \return The first element in the container
*/
#define BkVector_Front(v, t)		(((t*)v.data)[0])

/*! \brief Gets the last element in a BkVector
*
* \param v The container
* \param t The type of the data
* \return The last element in the container
*/
#define BkVector_Back(v, t)		(((t*)v.data)[(v.size - 1)])

/*! \brief Prepend a new element on to the end of the container
*
* \param v The container
* \param d The data to insert
*/
#define BkVector_PushBack(v, d)		BkVector_PushBack_t(&v, (char const*)&d)

/*! \brief Inserts a new element at a given position in a BkVector
*
* \param v The container
* \param i The position to insert the data
* \param d The data to insert
*/
#define BkVector_Insert(v, i, d)	BkVector_Insert_t(&v, i, (char const*)&d)

/*! \brief Resizes a BkVector so that it contains s elements
*
* \param v The container
* \param s The new container size
* \param d The data to insert
*/
#define BkVector_Resize(v, s, d)	BkVector_Resize_t(&v, s, (char const*)&d)

struct BkVector
{
	char*	data;
	uint32	size;
	uint32	capacity;
	uint8	data_size;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Initializes a BkVector
*
* \param vector The container
* \param data_size The size of the data
*/
extern BK_API void	BkVector_Initialize(struct BkVector* vector, uint32 const data_size);

/*! \brief Requests that a BkVector capacity be at least enough to contain n elements.
*
* \param vector The container
* \param capacity The new capacity of the container
*/
extern BK_API void	BkVector_Reserve(struct BkVector* vector, uint32 const capacity);

/*! \brief Removes all elements from a BkVector, leaving the container with a size of 0.
*
* \param vector The container
*/
extern BK_API void	BkVector_Clear(struct BkVector* vector);

/*! \brief Destroy a BkVector
*
* \param vector The container
*/
extern BK_API void	BkVector_Destroy(struct BkVector* vector);

/*! \brief Removes the element at the given index from a BkVector
*
* \param vector The container
* \param index The index of the element to remove
*/
extern BK_API void	BkVector_Erase(struct BkVector* vector, uint32 const index);

/*! \brief Prepend a new element on to the end of the container
*
* \param vector The container
* \param data The data to insert
*/
extern BK_API void	BkVector_PushBack_t(struct BkVector* vector, char const* data);

/*! \brief Remove the last element from a BkVector
*
* \param The container
*/
extern BK_API void	BkVector_PopBack(struct BkVector* vector);

/*! \brief Inserts a new element at a given position in a BkVector
*
* \param vector The container
* \param index The position to insert the data
* \param data The data to insert
*/
extern BK_API void	BkVector_Insert_t(struct BkVector* vector, uint32 const index, char const* data);

/*! \brief Resizes a BkVector so that it contains s elements
*
* \param vector The container
* \param size The new container size
* \param data The data to insert
*/
extern BK_API void	BkVector_Resize_t(struct BkVector* vector, uint32 const size, char const* data);

#endif