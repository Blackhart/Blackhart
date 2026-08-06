// Standard headers.
#include <stdlib.h>
#include <string.h>

// blackhart headers.
#include "foundation/BkArray.h"
#include "foundation/BkError.h"

// ~~~~~ Type Definitions ~~~~~

struct BkArray {
  char* data;
  size_t size;
  size_t capacity;
  uint8 data_size;
  uint8 __padding__[7];
};

// ~~~~~ Def(PUBLIC) ~~~~~

BkArray* BkArray_Create(uint8 const data_size) {
  BkArray* obj = malloc(sizeof(BkArray));
  BK_ERROR(BK_ISNULL(obj),
           ((struct BkErrorInfo){
               .what = "Cannot create array",
               .why = "Out of memory while allocating BkArray",
               .how = "Free memory and retry",
               .result = "BkArray_Create returned NULL",
           }),
           NULL);

  obj->data = NULL;
  obj->size = 0;
  obj->capacity = 0;
  obj->data_size = data_size;
  return obj;
}

void BkArray_Release(BkArray** obj) {
  BK_ASSERT(BK_ISNULL(obj));
  if (BK_ISNULL(*obj)) {
    return;
  }

  free((*obj)->data);
  free(*obj);
  *obj = NULL;
}

size_t BkArray_Size(BkArray const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return obj->size;
}

size_t BkArray_Capacity(BkArray const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return obj->capacity;
}

uint8 BkArray_DataSize(BkArray const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return obj->data_size;
}

void* BkArray_Data(BkArray const* obj) {
  BK_ASSERT(BK_ISNULL(obj));
  return obj->data;
}

void BkArray_Reserve(BkArray* obj, size_t const capacity) {
  BK_ASSERT(BK_ISNULL(obj));

  if (capacity <= obj->capacity) return;

  size_t n = capacity * obj->data_size;

  void* data = malloc(n);
  BK_FATAL(BK_ISNULL(data),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system failed to allocate memory block!",
               .result = "Process aborted",
           }));

  if (obj->size != 0) {
    n = obj->size * obj->data_size;
    memcpy(data, obj->data, n);
  }

  obj->capacity = capacity;

  free(obj->data);
  obj->data = data;
}

void BkArray_Clear(BkArray* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  obj->size = 0;
}

void BkArray_Erase(BkArray* obj, size_t const index) {
  BK_ASSERT(BK_ISNULL(obj));
  BK_ASSERT(index >= obj->size);

  if (obj->size == 1) {
    obj->size = 0;
    return;
  }

  obj->size -= 1;

  size_t offset = index * obj->data_size;
  size_t start = obj->size * obj->data_size;

  memcpy(obj->data + offset, obj->data + start, obj->data_size);
}

void BkArray_PushBack_t(BkArray* obj, char const* data) {
  BK_ASSERT(BK_ISNULL(obj));
  BK_ASSERT(BK_ISNULL(data));

  if ((obj->size + 1) > obj->capacity) {
    BkArray_Reserve(obj, obj->capacity + 4);
  }

  memcpy(obj->data + (obj->size * obj->data_size), data, obj->data_size);

  obj->size += 1;
}

void BkArray_PopBack(BkArray* obj) {
  BK_ASSERT(BK_ISNULL(obj));

  obj->size -= 1;
}

void BkArray_Insert_t(BkArray* obj, size_t const index, char const* data) {
  BK_ASSERT(BK_ISNULL(obj));
  BK_ASSERT(BK_ISNULL(data));
  BK_ASSERT(index > obj->size);

  if (index == obj->size) {
    BkArray_PushBack_t(obj, data);
    return;
  }

  if ((obj->size + 1) > obj->capacity) {
    BkArray_Reserve(obj, obj->capacity + 4);
  }

  size_t offset = index * obj->data_size;
  size_t start = obj->size * obj->data_size;

  memcpy(obj->data + start, obj->data + offset, obj->data_size);
  memcpy(obj->data + offset, data, obj->data_size);

  obj->size += 1;
}

void BkArray_Resize_t(BkArray* obj, size_t const size, char const* data) {
  BK_ASSERT(BK_ISNULL(obj));
  BK_ASSERT(BK_ISNULL(data));

  if (size < obj->size)
    obj->size = size;
  else if (size > obj->size) {
    if (size > obj->capacity) BkArray_Reserve(obj, obj->capacity + size + 4);

    size_t offset = obj->size * obj->data_size;

    for (size_t i = obj->size; i < size; i++) {
      memcpy(obj->data + offset, data, obj->data_size);

      offset += obj->data_size;
    }

    obj->size = size;
  }
}
