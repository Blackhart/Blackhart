// Standard headers.
#include <stdlib.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkList.h"
#include "foundation/BkQueue.h"

// ~~~~~ Type Definitions ~~~~~

struct BkQueue {
  BkList* list;
};

// ~~~~~ Def(PUBLIC) ~~~~~

BkQueue* BkQueue_Create(void) {
  BkQueue* obj = malloc(sizeof(BkQueue));
  BK_ERROR(BK_ISNULL(obj),
           ((struct BkErrorInfo){
               .what = "Cannot create queue",
               .why = "Out of memory while allocating BkQueue",
               .how = "Free memory and retry",
               .result = "BkQueue_Create returned NULL",
           }),
           NULL);

  obj->list = BkList_Create();
  if (BK_ISNULL(obj->list)) {
    free(obj);
    return NULL;
  }

  return obj;
}

void BkQueue_Release(BkQueue** obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (BK_ISNULL(*obj)) {
    return;
  }

  BkList_Release(&(*obj)->list);
  free(*obj);
  *obj = NULL;
}

size_t BkQueue_Size(BkQueue const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return (size_t)BkList_Size(obj->list);
}

void* BkQueue_Front(BkQueue const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return BkList_Front(obj->list);
}

void* BkQueue_Back(BkQueue const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return BkList_Back(obj->list);
}

void BkQueue_Push(BkQueue* obj, void* data) {
  BK_ASSERT(BK_ISNULL(obj));
  BkList_PushBack(obj->list, data);
}

void BkQueue_Pop(BkQueue* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  BkList_PopFront(obj->list);
}

void BkQueue_Clear(BkQueue* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  BkList_Clear(obj->list);
}
