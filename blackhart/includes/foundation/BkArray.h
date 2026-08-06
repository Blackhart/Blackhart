#ifndef __BK_ARRAY_H__
#define __BK_ARRAY_H__

/**
 * @file BkArray.h
 * @brief Opaque dynamic array container.
 *
 * BkArray stores a contiguous buffer of fixed-size elements. The handle is
 * opaque: create with BkArray_Create, free with BkArray_Release. Use getters
 * for size/capacity/data; typed macros (At, PushBack, …) take a BkArray*.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Macros Definitions ~~~~~

/**
 * @def BkArray_Empty(arr)
 * @brief Checks if the array has no elements.
 */
#define BkArray_Empty(arr) (BkArray_Size(arr) == 0)

/**
 * @def BkArray_At(arr, t, i)
 * @brief Element at index i, cast to type t.
 */
#define BkArray_At(arr, t, i) (((t*)BkArray_Data(arr))[i])

/**
 * @def BkArray_Front(arr, t)
 * @brief First element, cast to type t.
 */
#define BkArray_Front(arr, t) (((t*)BkArray_Data(arr))[0])

/**
 * @def BkArray_Back(arr, t)
 * @brief Last element, cast to type t.
 */
#define BkArray_Back(arr, t) (((t*)BkArray_Data(arr))[BkArray_Size(arr) - 1])

/**
 * @def BkArray_PushBack(arr, d)
 * @brief Appends a copy of d (lvalue) to the array.
 */
#define BkArray_PushBack(arr, d) BkArray_PushBack_t((arr), (char const*)&(d))

/**
 * @def BkArray_Insert(arr, i, d)
 * @brief Inserts a copy of d at index i.
 */
#define BkArray_Insert(arr, i, d) \
  BkArray_Insert_t((arr), (i), (char const*)&(d))

/**
 * @def BkArray_Resize(arr, s, d)
 * @brief Resizes to s elements; new slots filled with d.
 */
#define BkArray_Resize(arr, s, d) \
  BkArray_Resize_t((arr), (s), (char const*)&(d))

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkArray
 * @brief Opaque dynamic array handle.
 */
typedef struct BkArray BkArray;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates an empty array for elements of @p data_size bytes.
 *
 * @return New array, or NULL on allocation failure.
 */
extern BK_API BkArray* BkArray_Create(uint8 const data_size);

/**
 * @brief Releases the array and its buffer. Sets @p obj to NULL.
 */
extern BK_API void BkArray_Release(BkArray** obj);

/**
 * @brief Number of elements currently stored.
 */
extern BK_API size_t BkArray_Size(BkArray const* obj);

/**
 * @brief Allocated capacity in elements.
 */
extern BK_API size_t BkArray_Capacity(BkArray const* obj);

/**
 * @brief Size in bytes of one element.
 */
extern BK_API uint8 BkArray_DataSize(BkArray const* obj);

/**
 * @brief Contiguous element buffer (may be NULL if empty and never reserved).
 */
extern BK_API void* BkArray_Data(BkArray const* obj);

/**
 * @brief Ensures capacity is at least @p capacity elements.
 */
extern BK_API void BkArray_Reserve(BkArray* obj, size_t const capacity);

/**
 * @brief Sets size to 0 without freeing capacity.
 */
extern BK_API void BkArray_Clear(BkArray* obj);

/**
 * @brief Removes the element at @p index (swap-with-last style).
 */
extern BK_API void BkArray_Erase(BkArray* obj, size_t const index);

/**
 * @brief Appends @p data_size bytes from @p data.
 */
extern BK_API void BkArray_PushBack_t(BkArray* obj, char const* data);

/**
 * @brief Removes the last element.
 */
extern BK_API void BkArray_PopBack(BkArray* obj);

/**
 * @brief Inserts @p data_size bytes from @p data at @p index.
 */
extern BK_API void BkArray_Insert_t(BkArray* obj, size_t const index,
                                    char const* data);

/**
 * @brief Resizes to @p size; new elements filled from @p data.
 */
extern BK_API void BkArray_Resize_t(BkArray* obj, size_t const size,
                                    char const* data);

#endif
