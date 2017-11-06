#ifndef __BK_ARRAY_H__
#define __BK_ARRAY_H__

#include <string.h>

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

/*! \brief Checks if the BkArray has no elements
*
* \param v The container
* \return TRUE if the BkArray is empty, FALSE otherwise
*/
#define BkArray_Empty(v)		(BkArray_Size(v) == 0)

/*! \brief Gets the size of a BkArray
*
* \param v The container
* \return The size of the container
*/
#define BkArray_Size(v)		(v.size)

/*! \brief Gets the capacity of a BkArray
*
* \param v The container
* \return The capacity of the container
*/
#define BkArray_Capacity(v)		(v.capacity)

/*! \brief Gets the data at a given position in a BkArray
*
* \param v The container
* \param t The type of the data
* \param i The position of the data in the vector
* \return The data at the specified position in the container
*/
#define BkArray_At(v, t, i)		(((t*)v.data)[i])

/*! \brief Gets the first element in a BkArray
*
* \param v The container
* \param t The type of the data
* \return The first element in the container
*/
#define BkArray_Front(v, t)		(((t*)v.data)[0])

/*! \brief Gets the last element in a BkArray
*
* \param v The container
* \param t The type of the data
* \return The last element in the container
*/
#define BkArray_Back(v, t)		(((t*)v.data)[(v.size - 1)])

/*! \brief Prepend a new element on to the end of the container
*
* \param v The container
* \param d The data to insert
*/
#define BkArray_PushBack(v, d)		BkArray_PushBack_t(&v, (char const*)&d)

/*! \brief Inserts a new element at a given position in a BkArray
*
* \param v The container
* \param i The position to insert the data
* \param d The data to insert
*/
#define BkArray_Insert(v, i, d)	BkArray_Insert_t(&v, i, (char const*)&d)

/*! \brief Resizes a BkArray so that it contains s elements
*
* \param v The container
* \param s The new container size
* \param d The data to insert
*/
#define BkArray_Resize(v, s, d)	BkArray_Resize_t(&v, s, (char const*)&d)

struct BkArray
{
	char*	data;
	uint32	size;
	uint32	capacity;
	uint8	data_size;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Initializes a BkArray
*
* \param vector The container
* \param data_size The size of the data
*/
extern BK_API void	BkArray_Initialize(struct BkArray* vector, uint32 const data_size);

/*! \brief Requests that a BkArray capacity be at least enough to contain n elements.
*
* \param vector The container
* \param capacity The new capacity of the container
*/
extern BK_API void	BkArray_Reserve(struct BkArray* vector, uint32 const capacity);

/*! \brief Removes all elements from a BkArray, leaving the container with a size of 0.
*
* \param vector The container
*/
extern BK_API void	BkArray_Clear(struct BkArray* vector);

/*! \brief Destroy a BkArray
*
* \param vector The container
*/
extern BK_API void	BkArray_Destroy(struct BkArray* vector);

/*! \brief Removes the element at the given index from a BkArray
*
* \param vector The container
* \param index The index of the element to remove
*/
extern BK_API void	BkArray_Erase(struct BkArray* vector, uint32 const index);

/*! \brief Prepend a new element on to the end of the container
*
* \param vector The container
* \param data The data to insert
*/
extern BK_API void	BkArray_PushBack_t(struct BkArray* vector, char const* data);

/*! \brief Remove the last element from a BkArray
*
* \param The container
*/
extern BK_API void	BkArray_PopBack(struct BkArray* vector);

/*! \brief Inserts a new element at a given position in a BkArray
*
* \param vector The container
* \param index The position to insert the data
* \param data The data to insert
*/
extern BK_API void	BkArray_Insert_t(struct BkArray* vector, uint32 const index, char const* data);

/*! \brief Resizes a BkArray so that it contains s elements
*
* \param vector The container
* \param size The new container size
* \param data The data to insert
*/
extern BK_API void	BkArray_Resize_t(struct BkArray* vector, uint32 const size, char const* data);

#endif