#ifndef __BK_LIST_H__
#define __BK_LIST_H__

/**
 * @file BkList.h
 * @brief Opaque doubly-linked list of void* elements.
 *
 * BkList is a container handle: create with BkList_Create, free with
 * BkList_Release. Nodes are opaque; use Begin/Next/NodeData for iteration and
 * EraseNode when removing during a walk. Payload pointers are not freed.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Macros Definitions ~~~~~

/**
 * @def BkList_Empty(list)
 * @brief Checks if the list has no elements.
 */
#define BkList_Empty(list) (BkList_Size(list) == 0)

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkList
 * @brief Opaque doubly-linked list handle.
 */
typedef struct BkList BkList;

/**
 * @typedef BkListNode
 * @brief Opaque list node (iterator) handle.
 */
typedef struct BkListNode BkListNode;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates an empty list.
 *
 * @return New list, or NULL on allocation failure.
 */
extern BK_API BkList* BkList_Create(void);

/**
 * @brief Releases a list and all of its nodes.
 *
 * Does not free payload pointers stored in the nodes. Safe if @p *obj is NULL.
 *
 * @param obj Address of the list pointer; set to NULL on success.
 */
extern BK_API void BkList_Release(BkList** obj);

/**
 * @brief Number of elements in the list.
 *
 * @param obj List handle (must not be NULL).
 */
extern BK_API uint32 BkList_Size(BkList const* obj);

/**
 * @brief Data pointer of the first element, or NULL if empty.
 */
extern BK_API void* BkList_Front(BkList const* obj);

/**
 * @brief Data pointer of the last element, or NULL if empty.
 */
extern BK_API void* BkList_Back(BkList const* obj);

/**
 * @brief Data pointer at zero-based @p index, or NULL if out of range.
 */
extern BK_API void* BkList_Get(BkList const* obj, uint32 const index);

/**
 * @brief Removes all nodes. Does not free payloads. List handle stays valid.
 */
extern BK_API void BkList_Clear(BkList* obj);

/**
 * @brief Inserts @p data at @p index (append if index >= size).
 */
extern BK_API void BkList_Insert(BkList* obj, void* data, uint32 const index);

/**
 * @brief Removes the first node whose data pointer equals @p data.
 */
extern BK_API void BkList_Erase(BkList* obj, void* data);

/**
 * @brief Removes @p node from @p obj and returns the following node (or NULL).
 *
 * @p node must belong to @p obj. Payload is not freed.
 */
extern BK_API BkListNode* BkList_EraseNode(BkList* obj, BkListNode* node);

/**
 * @brief Prepends @p data.
 */
extern BK_API void BkList_PushFront(BkList* obj, void* data);

/**
 * @brief Appends @p data.
 */
extern BK_API void BkList_PushBack(BkList* obj, void* data);

/**
 * @brief Removes the first element (no-op if empty).
 */
extern BK_API void BkList_PopFront(BkList* obj);

/**
 * @brief Removes the last element (no-op if empty).
 */
extern BK_API void BkList_PopBack(BkList* obj);

/**
 * @brief First node, or NULL if empty.
 */
extern BK_API BkListNode* BkList_Begin(BkList* obj);

/**
 * @brief Next node after @p node, or NULL.
 */
extern BK_API BkListNode* BkList_Next(BkListNode* node);

/**
 * @brief Previous node before @p node, or NULL.
 */
extern BK_API BkListNode* BkList_Previous(BkListNode* node);

/**
 * @brief Payload stored in @p node.
 */
extern BK_API void* BkList_NodeData(BkListNode const* node);

/**
 * @brief Node at zero-based @p index, or NULL if out of range.
 */
extern BK_API BkListNode* BkList_GetNode(BkList* obj, uint32 const index);

#endif
