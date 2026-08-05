#ifndef __BK_ARRAY_H__
#define __BK_ARRAY_H__

/**
 * @file BkArray.h
 * @brief Defines the BkArray structure and functions for dynamic array
 * operations.
 *
 * This file provides the definition of the BkArray struct, a generic dynamic
 * array container that can store elements of any type. It includes macros and
 * functions for initialization, element access, insertion, deletion, and memory
 * management.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Macros Definitions ~~~~~

/**
 * @def BkArray_Empty(v)
 * @brief Checks if the BkArray has no elements.
 * @param v The container (BkArray structure).
 * @return TRUE if the BkArray is empty, FALSE otherwise.
 */
#define BkArray_Empty(v) (BkArray_Size(v) == 0)

/**
 * @def BkArray_Size(v)
 * @brief Gets the number of elements currently stored in the BkArray.
 * @param v The container (BkArray structure).
 * @return The current size of the container.
 */
#define BkArray_Size(v) (v.size)

/**
 * @def BkArray_Capacity(v)
 * @brief Gets the capacity (allocated size) of the BkArray.
 * @param v The container (BkArray structure).
 * @return The capacity of the container (number of elements that can be stored
 * without reallocation).
 */
#define BkArray_Capacity(v) (v.capacity)

/**
 * @def BkArray_At(v, t, i)
 * @brief Gets the data at a given position in the BkArray.
 * @param v The container (BkArray structure).
 * @param t The type of the data element.
 * @param i The index of the element to access (0-based).
 * @return A reference to the element at the specified position (cast to type
 * t).
 */
#define BkArray_At(v, t, i) (((t*)v.data)[i])

/**
 * @def BkArray_Front(v, t)
 * @brief Gets the first element in the BkArray.
 * @param v The container (BkArray structure).
 * @param t The type of the data element.
 * @return A reference to the first element in the container (cast to type t).
 */
#define BkArray_Front(v, t) (((t*)v.data)[0])

/**
 * @def BkArray_Back(v, t)
 * @brief Gets the last element in the BkArray.
 * @param v The container (BkArray structure).
 * @param t The type of the data element.
 * @return A reference to the last element in the container (cast to type t).
 */
#define BkArray_Back(v, t) (((t*)v.data)[(v.size - 1)])

/**
 * @def BkArray_PushBack(v, d)
 * @brief Appends a new element to the end of the container.
 * @param v The container (BkArray structure).
 * @param d The data to insert (will be copied into the array).
 */
#define BkArray_PushBack(v, d) BkArray_PushBack_t(&v, (char const*)&d)

/**
 * @def BkArray_Insert(v, i, d)
 * @brief Inserts a new element at a given position in the BkArray.
 * @param v The container (BkArray structure).
 * @param i The index where to insert the data (0-based).
 * @param d The data to insert (will be copied into the array).
 */
#define BkArray_Insert(v, i, d) BkArray_Insert_t(&v, i, (char const*)&d)

/**
 * @def BkArray_Resize(v, s, d)
 * @brief Resizes the BkArray to contain exactly s elements.
 *
 * If the new size is larger than the current size, new elements are initialized
 * with the value d. If smaller, excess elements are removed.
 *
 * @param v The container (BkArray structure).
 * @param s The new size of the container.
 * @param d The data value to use for initializing new elements if size
 * increases.
 */
#define BkArray_Resize(v, s, d) BkArray_Resize_t(&v, s, (char const*)&d)

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkArray
 * @brief Structure representing a dynamic array container.
 *
 * The BkArray is a generic container that can store elements of any type.
 * It automatically manages memory allocation and reallocation as elements are
 * added.
 */
struct BkArray {
  char* data; /**< Pointer to the data buffer containing the array elements. */
  size_t size; /**< The current number of elements stored in the array. */
  size_t capacity; /**< The allocated capacity (maximum elements without
                           reallocation). */
  uint8 data_size; /**< The size in bytes of each element type. */
  uint8 __padding__[7]; /**< Padding for memory alignment. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Initializes a BkArray with the specified element size.
 *
 * Prepares the array for use. Must be called before using any other BkArray
 * functions. The array starts empty with no allocated capacity.
 *
 * @param obj Pointer to the BkArray container to initialize.
 * @param data_size The size in bytes of each element type that will be stored.
 */
extern BK_API void BkArray_Initialize(struct BkArray* obj,
                                      uint8 const data_size);

/**
 * @brief Requests that the BkArray capacity be at least enough to contain n
 * elements.
 *
 * If the requested capacity is greater than the current capacity, the array is
 * reallocated to the new capacity. Otherwise, no action is taken.
 *
 * @param obj Pointer to the BkArray container.
 * @param capacity The minimum capacity to reserve.
 */
extern BK_API void BkArray_Reserve(struct BkArray* obj, size_t const capacity);

/**
 * @brief Removes all elements from the BkArray, leaving the container with a
 * size of 0.
 *
 * The capacity remains unchanged. The data is not freed, allowing for efficient
 * reuse.
 *
 * @param obj Pointer to the BkArray container.
 */
extern BK_API void BkArray_Clear(struct BkArray* obj);

/**
 * @brief Destroys a BkArray and frees all allocated memory.
 *
 * This function should be called when the array is no longer needed to free
 * resources. After calling this function, the array should not be used unless
 * reinitialized.
 *
 * @param obj Pointer to the BkArray container to destroy.
 */
extern BK_API void BkArray_Destroy(struct BkArray* obj);

/**
 * @brief Removes the element at the given index from the BkArray.
 *
 * The element at the specified index is removed, and all subsequent elements
 * are shifted to fill the gap. The size of the array is decreased by one.
 *
 * @param obj Pointer to the BkArray container.
 * @param index The index of the element to remove (0-based).
 */
extern BK_API void BkArray_Erase(struct BkArray* obj, size_t const index);

/**
 * @brief Appends a new element to the end of the container.
 *
 * Adds a copy of the data to the end of the array. The array size is increased
 * by one. If the capacity is insufficient, the array is automatically
 * reallocated.
 *
 * @param obj Pointer to the BkArray container.
 * @param data Pointer to the data to insert (will be copied, data_size bytes
 * will be copied).
 */
extern BK_API void BkArray_PushBack_t(struct BkArray* obj, char const* data);

/**
 * @brief Removes the last element from the BkArray.
 *
 * The last element is removed and the size is decreased by one.
 * The capacity remains unchanged. If the array is empty, this function has no
 * effect.
 *
 * @param obj Pointer to the BkArray container.
 */
extern BK_API void BkArray_PopBack(struct BkArray* obj);

/**
 * @brief Inserts a new element at a given position in the BkArray.
 *
 * Inserts a copy of the data at the specified index. All elements at and after
 * the index are shifted to make room. The array size is increased by one.
 *
 * @param obj Pointer to the BkArray container.
 * @param index The position where to insert the data (0-based).
 * @param data Pointer to the data to insert (will be copied, data_size bytes
 * will be copied).
 */
extern BK_API void BkArray_Insert_t(struct BkArray* obj, size_t const index,
                                    char const* data);

/**
 * @brief Resizes the BkArray to contain exactly the specified number of
 * elements.
 *
 * If the new size is larger than the current size, new elements are initialized
 * with the value from data. If smaller, excess elements are removed. The
 * capacity may be adjusted if necessary.
 *
 * @param obj Pointer to the BkArray container.
 * @param size The new size of the container.
 * @param data Pointer to the data value to use for initializing new elements
 * (if size increases).
 */
extern BK_API void BkArray_Resize_t(struct BkArray* obj, size_t const size,
                                    char const* data);

#endif