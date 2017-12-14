// Standard headers.
#include <stdlib.h>

// Blackhart.foundation headers.
#include "foundation\BkArray.h"
#include "foundation\BkError.h"


void	BkArray_Initialize(struct BkArray* array, uint8 const data_size)
{
	BK_ASSERT(BK_ISNULL(array));

	array->data = NULL;
	array->size = 0;
	array->capacity = 0;
	array->data_size = data_size;
}

void	BkArray_Reserve(struct BkArray* array, size_t const capacity)
{
	BK_ASSERT(BK_ISNULL(array));

	if (capacity <= array->capacity)
		return;

	size_t n = capacity * array->data_size;
	
	char* data = malloc(n);
	BK_ERROR(BK_ISNULL(data), "Memory system failed to allocate memory block!");

	if (array->size != 0)
	{
		n = array->size * array->data_size;
		memcpy(data, array->data, n);
	}

	array->capacity = capacity;

	free(array->data);
	array->data = data;
}

void	BkArray_Clear(struct BkArray* array)
{
	BK_ASSERT(BK_ISNULL(array));

	array->size = 0;
}

void	BkArray_Destroy(struct BkArray* array)
{
	BK_ASSERT(BK_ISNULL(array));

	free(array->data);
	array->data = NULL;
	array->capacity = 0;
	array->size = 0;
}

void	BkArray_Erase(struct BkArray* array, size_t const index)
{
	BK_ASSERT(BK_ISNULL(array));
	BK_ASSERT(index >= array->size);

	if (array->size == 1)
	{
		array->size = 0;
		return;
	}

	array->size -= 1;

	size_t offset = index * array->data_size;
	size_t start = array->size * array->data_size;

	memcpy(array->data + offset, array->data + start, array->data_size);
}

void	BkArray_PushBack_t(struct BkArray* array, char const* data)
{
	BK_ASSERT(BK_ISNULL(array));
	BK_ASSERT(BK_ISNULL(data));

	if ((array->size + 1) > array->capacity)
	{
		BkArray_Reserve(array, array->capacity + 4);
	}
	
	memcpy(array->data + (array->size * array->data_size), data, array->data_size);
	
	array->size += 1;
}

void	BkArray_PopBack(struct BkArray* array)
{
	BK_ASSERT(BK_ISNULL(array));

	array->size -= 1;
}

void	BkArray_Insert_t(struct BkArray* array, size_t const index, char const* data)
{
	BK_ASSERT(BK_ISNULL(array));
	BK_ASSERT(BK_ISNULL(data));
	BK_ASSERT(index > array->size);

	if (index == array->size)
	{
		BkArray_PushBack_t(array, data);
		return;
	}

	if ((array->size + 1) > array->capacity)
	{
		BkArray_Reserve(array, array->capacity + 4);
	}

	size_t offset = index * array->data_size;
	size_t start = array->size * array->data_size;

	memcpy(array->data + start, array->data + offset, array->data_size);
	memcpy(array->data + offset, data, array->data_size);

	array->size += 1;
}

void	BkArray_Resize_t(struct BkArray* array, size_t const size, char const* data)
{
	BK_ASSERT(BK_ISNULL(array));
	BK_ASSERT(BK_ISNULL(data));

	if (size < array->size)
		array->size = size;
	else if (size > array->size)
	{
		if (size > array->capacity)
			BkArray_Reserve(array, array->capacity + size + 4);

		size_t offset = array->size * array->data_size;

		for (size_t i = array->size; i < size; i++)
		{
			memcpy(array->data + offset, data, array->data_size);

			offset += array->data_size;
		}

		array->size = size;
	}
}