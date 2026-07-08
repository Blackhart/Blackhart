#ifndef __BK_LIST_H__
#define __BK_LIST_H__

/**
 * @file BkList.h
 * @brief Defines the BkList structure and functions for doubly-linked list operations.
 *
 * This file provides the definition of the BkList struct, a doubly-linked list container
 * that can store elements of any type. It includes macros and functions for element access,
 * insertion, deletion, and list traversal.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkAtomicDataType.h"

// ~~~~~ Macros Definitions ~~~~~

/**
 * @def BkList_Empty(list)
 * @brief Checks if the BkList has no elements.
 * @param list Any BkList element (can be NULL).
 * @return TRUE if the BkList is empty (NULL), FALSE otherwise.
 */
#define BkList_Empty(list)	(BK_ISNULL(list))

/**
 * @def BkList_Data(list)
 * @brief Gets the data stored in a BkList element.
 * @param list Pointer to a BkList element.
 * @return The element's data pointer, or NULL if list is NULL.
 */
#define BkList_Data(list)	(list->data)

/**
 * @def BkList_Previous(list)
 * @brief Gets the previous element in the BkList.
 * @param list Pointer to a BkList element.
 * @return Pointer to the previous element, or NULL if there are no previous elements.
 */
#define BkList_Previous(list)	(list->previous)

/**
 * @def BkList_Next(list)
 * @brief Gets the next element in the BkList.
 * @param list Pointer to a BkList element.
 * @return Pointer to the next element, or NULL if there are no next elements.
 */
#define BkList_Next(list)	(list->next)

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkList
 * @brief Structure representing a node in a doubly-linked list.
 *
 * Each node contains a pointer to data and pointers to the next and previous nodes
 * in the list. The list can be traversed in both directions.
 */
struct BkList
{
	void*	data;              /**< Pointer to the data stored in this list node. */
	struct BkList*	next;       /**< Pointer to the next element in the list. */
	struct BkList*	previous;   /**< Pointer to the previous element in the list. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Gets the first element in a BkList.
 *
 * Traverses backward from the given element to find the head of the list.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @return Pointer to the first element in the BkList, or NULL if the list is empty.
 */
extern BK_API struct BkList*	BkList_Front(struct BkList* obj);

/**
 * @brief Gets the last element in a BkList.
 *
 * Traverses forward from the given element to find the tail of the list.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @return Pointer to the last element in the BkList, or NULL if the list is empty.
 */
extern BK_API struct BkList*	BkList_Back(struct BkList* obj);

/**
 * @brief Gets the number of elements in a BkList.
 *
 * Counts all elements by traversing the entire list from the given element.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @return The number of elements in the BkList.
 */
extern BK_API uint32	BkList_Size(struct BkList* obj);

/**
 * @brief Frees all memory used by a BkList.
 *
 * Deallocates all list nodes but does not free the data pointed to by each node.
 * If list elements contain dynamically-allocated memory, you should either use
 * BkList_ClearFull() (if available) or free them manually first.
 *
 * @param obj Any BkList element in the list (can be NULL). After this call, all
 *            list nodes are deallocated and the pointer should not be used.
 */
extern BK_API void	BkList_Clear(struct BkList* obj);

/**
 * @brief Gets the element at a given position (index) in a BkList.
 *
 * Traverses the list to find the element at the specified index position.
 * The first element is at index 0.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @param index The zero-based position of the element to retrieve.
 * @return Pointer to the element at the specified index, or NULL if the index is
 *         beyond the end of the list.
 */
extern BK_API struct BkList*	BkList_Get(struct BkList* obj, uint32 const index);

/**
 * @brief Inserts a new element into the list at the given position.
 *
 * Creates a new list node with the specified data and inserts it at the specified index.
 * If the index is larger than the number of elements in the list, the new element
 * is appended to the end of the list.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @param data Pointer to the data for the new element.
 * @param index The zero-based position where to insert the element.
 * @return Pointer to the head of the BkList (first element).
 */
extern BK_API struct BkList*	BkList_Insert(struct BkList* obj, void* data, uint32 const index);

/**
 * @brief Removes an element from a BkList by matching data pointer.
 *
 * Searches the list for an element containing the specified data pointer and removes it.
 * If multiple elements contain the same data pointer, only the first matching element
 * is removed. If no element contains the data pointer, the list is unchanged.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @param data The data pointer to search for and remove.
 * @return Pointer to the head of the BkList (first element).
 */
extern BK_API struct BkList*	BkList_Erase(struct BkList* obj, void* data);

/**
 * @brief Removes a specific link (node) from a BkList.
 *
 * Removes the specified list node from the list. The node is deallocated and the
 * list is reconnected. This is more efficient than BkList_Erase when you already
 * have a pointer to the node to remove.
 *
 * @param link Pointer to the list node (link) to remove from the BkList.
 * @return Pointer to the head of the BkList (first element).
 */
extern BK_API struct BkList*	BkList_EraseLink(struct BkList* link);

/**
 * @brief Prepends a new element to the start of the list.
 *
 * Creates a new list node with the specified data and adds it to the front of the list.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @param data Pointer to the data for the new element.
 * @return Pointer to the head of the BkList (the newly inserted first element).
 */
extern BK_API struct BkList*	BkList_PushFront(struct BkList* obj, void* data);

/**
 * @brief Appends a new element to the end of the list.
 *
 * Creates a new list node with the specified data and adds it to the back of the list.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @param data Pointer to the data for the new element.
 * @return Pointer to the head of the BkList (first element).
 */
extern BK_API struct BkList*	BkList_PushBack(struct BkList* obj, void* data);

/**
 * @brief Removes the first element from a BkList.
 *
 * Removes and deallocates the head node of the list. The list is reconnected
 * so the second element becomes the new head.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @return Pointer to the new head of the BkList (second element, or NULL if the list
 *         had only one element).
 */
extern BK_API struct BkList*	BkList_PopFront(struct BkList* obj);

/**
 * @brief Removes the last element from a BkList.
 *
 * Removes and deallocates the tail node of the list.
 *
 * @param obj Any BkList element in the list (can be NULL).
 * @return Pointer to the head of the BkList (first element, unchanged).
 */
extern BK_API struct BkList*	BkList_PopBack(struct BkList* obj);

/**
 * @brief Allocates memory for one BkList element.
 *
 * Creates a new, uninitialized list node. The node's data, next, and previous
 * pointers are not initialized and should be set before use.
 *
 * @return Pointer to the newly-allocated BkList element, or NULL if allocation fails.
 */
extern BK_API struct BkList*	BkList_Alloc(void);

#endif