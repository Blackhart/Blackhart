#include <stdlib.h>

#include "core\BkArray.h"
#include "core\BkError.h"

void	BkArray_Initialize(struct BkArray* array, uint32 const data_size)
{
	array->data = NULL;
	array->size = 0;
	array->capacity = 0;
	array->data_size = data_size;
}

void	BkArray_Reserve(struct BkArray* array, uint32 const capacity)
{
	if (capacity <= array->capacity)
		return;

	uint32 n = capacity * array->data_size;
	
	char* data = malloc(n);
	if (BK_ISNULL(data))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block!");

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
	array->size = 0;
}

void	BkArray_Destroy(struct BkArray* array)
{
	free(array->data);
	array->data = NULL;
	array->capacity = 0;
	array->size = 0;
}

void	BkArray_Erase(struct BkArray* array, uint32 const index)
{
	if (index >= array->size)
	{
		BkWarning(BK_ERROR_LOCATION "Index must be greater than the array's size!");
		return;
	}

	if (array->size == 1)
	{
		array->size = 0;
		return;
	}

	array->size -= 1;

	uint32 offset = index * array->data_size;
	uint32 start = array->size * array->data_size;

	memcpy(array->data + offset, array->data + start, array->data_size);
}

void	BkArray_PushBack_t(struct BkArray* array, char const* data)
{
	if ((array->size + 1) > array->capacity)
	{
		BkArray_Reserve(array, array->capacity + 4);
	}
	
	memcpy(array->data + (array->size * array->data_size), data, array->data_size);
	
	array->size += 1;
}

void	BkArray_PopBack(struct BkArray* array)
{
	array->size -= 1;
}

void	BkArray_Insert_t(struct BkArray* array, uint32 const index, char const* data)
{
	if (index > array->size)
	{
		BkWarning(BK_ERROR_LOCATION "Index must be lesser than or equal to the array's size!");
		return;
	}

	if (index == array->size)
	{
		BkArray_PushBack_t(array, data);
		return;
	}

	if ((array->size + 1) > array->capacity)
	{
		BkArray_Reserve(array, array->capacity + 4);
	}

	uint32 offset = index * array->data_size;
	uint32 start = array->size * array->data_size;

	memcpy(array->data + start, array->data + offset, array->data_size);
	memcpy(array->data + offset, data, array->data_size);

	array->size += 1;
}

void	BkArray_Resize_t(struct BkArray* array, uint32 const size, char const* data)
{
	if (size < array->size)
		array->size = size;
	else if (size > array->size)
	{
		if (size > array->capacity)
			BkArray_Reserve(array, array->capacity + size + 4);

		uint32 offset = array->size * array->data_size;

		for (uint32 i = array->size; i < size; i++)
		{
			memcpy(array->data + offset, data, array->data_size);

			offset += array->data_size;
		}

		array->size = size;
	}
}