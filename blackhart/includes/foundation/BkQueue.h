#ifndef __BK_QUEUE_H__
#define __BK_QUEUE_H__

/**
 * @file BkQueue.h
 * @brief Opaque FIFO queue of void* elements.
 *
 * Create with BkQueue_Create, free with BkQueue_Release. Payload pointers are
 * not freed by the queue.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Macros Definitions ~~~~~

/**
 * @def BkQueue_Empty(queue)
 * @brief Checks if the queue has no elements.
 */
#define BkQueue_Empty(queue) (BkQueue_Size(queue) == 0)

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkQueue
 * @brief Opaque FIFO queue handle.
 */
typedef struct BkQueue BkQueue;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates an empty queue.
 *
 * @return New queue, or NULL on allocation failure.
 */
extern BK_API BkQueue* BkQueue_Create(void);

/**
 * @brief Releases a queue and its nodes.
 *
 * Does not free payload pointers. Safe if @p *obj is NULL.
 *
 * @param obj Address of the queue pointer; set to NULL on success.
 */
extern BK_API void BkQueue_Release(BkQueue** obj);

/**
 * @brief Number of elements in the queue.
 */
extern BK_API size_t BkQueue_Size(BkQueue const* obj);

/**
 * @brief Oldest element, or NULL if empty.
 */
extern BK_API void* BkQueue_Front(BkQueue const* obj);

/**
 * @brief Newest element, or NULL if empty.
 */
extern BK_API void* BkQueue_Back(BkQueue const* obj);

/**
 * @brief Appends @p data (no-op effect on ownership of the payload).
 */
extern BK_API void BkQueue_Push(BkQueue* obj, void* data);

/**
 * @brief Removes the oldest element (no-op if empty).
 */
extern BK_API void BkQueue_Pop(BkQueue* obj);

/**
 * @brief Removes all elements; the queue handle stays valid.
 */
extern BK_API void BkQueue_Clear(BkQueue* obj);

#endif
