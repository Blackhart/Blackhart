// Standard headers.
#include <stdlib.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkList.h"

// ~~~~~ Type Definitions ~~~~~

struct BkListNode {
  void* data;
  struct BkListNode* next;
  struct BkListNode* previous;
};

struct BkList {
  struct BkListNode* head;
  struct BkListNode* tail;
  uint32 size;
};

// ~~~~~ Def(INTERNAL) ~~~~~

static struct BkListNode* __BkList_AllocNode(void* data) {
  struct BkListNode* node = malloc(sizeof(struct BkListNode));
  BK_FATAL(BK_ISNULL(node),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system failed to allocate memory block",
               .result = "Process aborted",
           }));

  node->data = data;
  node->next = NULL;
  node->previous = NULL;
  return node;
}

static void __BkList_Unlink(BkList* obj, struct BkListNode* node) {
  if (node->previous != NULL) {
    node->previous->next = node->next;
  } else {
    obj->head = node->next;
  }

  if (node->next != NULL) {
    node->next->previous = node->previous;
  } else {
    obj->tail = node->previous;
  }

  free(node);
  obj->size--;
}

// ~~~~~ Def(PUBLIC) ~~~~~

BkList* BkList_Create(void) {
  BkList* obj = malloc(sizeof(BkList));
  BK_ERROR(BK_ISNULL(obj),
           ((struct BkErrorInfo){
               .what = "Cannot create list",
               .why = "Out of memory while allocating BkList",
               .how = "Free memory and retry",
               .result = "BkList_Create returned NULL",
           }),
           NULL);

  obj->head = NULL;
  obj->tail = NULL;
  obj->size = 0;
  return obj;
}

void BkList_Release(BkList** obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (BK_ISNULL(*obj)) {
    return;
  }

  BkList_Clear(*obj);
  free(*obj);
  *obj = NULL;
}

uint32 BkList_Size(BkList const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return obj->size;
}

void* BkList_Front(BkList const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (obj->head == NULL) {
    return NULL;
  }
  return obj->head->data;
}

void* BkList_Back(BkList const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (obj->tail == NULL) {
    return NULL;
  }
  return obj->tail->data;
}

void* BkList_Get(BkList const* obj, uint32 const index) {
  BkListNode* node = BkList_GetNode((BkList*)obj, index);
  if (node == NULL) {
    return NULL;
  }
  return node->data;
}

void BkList_Clear(BkList* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  struct BkListNode* node = obj->head;
  while (node != NULL) {
    struct BkListNode* next = node->next;
    free(node);
    node = next;
  }

  obj->head = NULL;
  obj->tail = NULL;
  obj->size = 0;
}

void BkList_Insert(BkList* obj, void* data, uint32 const index) {
  BK_ASSERT(BK_ISNULL(obj));

  if (index >= obj->size) {
    BkList_PushBack(obj, data);
    return;
  }

  if (index == 0) {
    BkList_PushFront(obj, data);
    return;
  }

  struct BkListNode* at = BkList_GetNode(obj, index);
  struct BkListNode* node = __BkList_AllocNode(data);

  node->next = at;
  node->previous = at->previous;
  at->previous->next = node;
  at->previous = node;
  obj->size++;
}

void BkList_Erase(BkList* obj, void* data) {
  BK_ASSERT(BK_ISNULL(obj));

  struct BkListNode* node = obj->head;
  while (node != NULL) {
    if (node->data == data) {
      __BkList_Unlink(obj, node);
      return;
    }
    node = node->next;
  }
}

BkListNode* BkList_EraseNode(BkList* obj, BkListNode* node) {
  BK_ASSERT(BK_ISNULL(obj));
  BK_ASSERT(BK_ISNULL(node));

  struct BkListNode* next = node->next;
  __BkList_Unlink(obj, node);
  return next;
}

void BkList_PushFront(BkList* obj, void* data) {
  BK_ASSERT(BK_ISNULL(obj));

  struct BkListNode* node = __BkList_AllocNode(data);
  node->next = obj->head;

  if (obj->head != NULL) {
    obj->head->previous = node;
  } else {
    obj->tail = node;
  }

  obj->head = node;
  obj->size++;
}

void BkList_PushBack(BkList* obj, void* data) {
  BK_ASSERT(BK_ISNULL(obj));

  struct BkListNode* node = __BkList_AllocNode(data);
  node->previous = obj->tail;

  if (obj->tail != NULL) {
    obj->tail->next = node;
  } else {
    obj->head = node;
  }

  obj->tail = node;
  obj->size++;
}

void BkList_PopFront(BkList* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (obj->head == NULL) {
    return;
  }
  __BkList_Unlink(obj, obj->head);
}

void BkList_PopBack(BkList* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (obj->tail == NULL) {
    return;
  }
  __BkList_Unlink(obj, obj->tail);
}

BkListNode* BkList_Begin(BkList* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return obj->head;
}

BkListNode* BkList_Next(BkListNode* node) {
  if (node == NULL) {
    return NULL;
  }
  return node->next;
}

BkListNode* BkList_Previous(BkListNode* node) {
  if (node == NULL) {
    return NULL;
  }
  return node->previous;
}

void* BkList_NodeData(BkListNode const* node) {
  BK_ASSERT(BK_ISNULL(node));
  return node->data;
}

BkListNode* BkList_GetNode(BkList* obj, uint32 const index) {
  BK_ASSERT(BK_ISNULL(obj));

  if (index >= obj->size) {
    return NULL;
  }

  struct BkListNode* node = obj->head;
  uint32 i = 0;
  while (i < index) {
    node = node->next;
    i++;
  }
  return node;
}
