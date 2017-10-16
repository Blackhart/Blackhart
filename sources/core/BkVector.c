#include <stdlib.h>

#include "core\BkVector.h"
#include "core\BkError.h"

void	BkVector_Initialize(struct BkVector* vector, uint32 const data_size)
{
	vector->data = NULL;
	vector->size = 0;
	vector->capacity = 0;
	vector->data_size = data_size;
}

void	BkVector_Reserve(struct BkVector* vector, uint32 const capacity)
{
	if (capacity <= vector->capacity)
		return;

	uint32 n = capacity * vector->data_size;
	
	char* data = malloc(n);
	if (BK_ISNULL(data))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block!");

	if (vector->size != 0)
	{
		n = vector->size * vector->data_size;
		memcpy(data, vector->data, n);
	}

	vector->capacity = capacity;

	free(vector->data);
	vector->data = data;
}

void	BkVector_Clear(struct BkVector* vector)
{
	vector->size = 0;
}

void	BkVector_Destroy(struct BkVector* vector)
{
	free(vector->data);
	vector->data = NULL;
	vector->capacity = 0;
	vector->size = 0;
}

void	BkVector_Erase(struct BkVector* vector, uint32 const index)
{
	if (index >= vector->size)
	{
		BkWarning(BK_ERROR_LOCATION "Index must be greater than the vector's size!");
		return;
	}

	if (vector->size == 1)
	{
		vector->size = 0;
		return;
	}

	vector->size -= 1;

	uint32 offset = index * vector->data_size;
	uint32 start = vector->size * vector->data_size;

	memcpy(vector->data + offset, vector->data + start, vector->data_size);
}

void	BkVector_PushBack_t(struct BkVector* vector, char const* data)
{
	if ((vector->size + 1) > vector->capacity)
	{
		BkVector_Reserve(vector, vector->capacity + 4);
	}
	
	memcpy(vector->data + (vector->size * vector->data_size), data, vector->data_size);
	
	vector->size += 1;
}

void	BkVector_PopBack(struct BkVector* vector)
{
	vector->size -= 1;
}

void	BkVector_Insert_t(struct BkVector* vector, uint32 const index, char const* data)
{
	if (index > vector->size)
	{
		BkWarning(BK_ERROR_LOCATION "Index must be lesser than or equal to the vector's size!");
		return;
	}

	if (index == vector->size)
	{
		BkVector_PushBack_t(vector, data);
		return;
	}

	if ((vector->size + 1) > vector->capacity)
	{
		BkVector_Reserve(vector, vector->capacity + 4);
	}

	uint32 offset = index * vector->data_size;
	uint32 start = vector->size * vector->data_size;

	memcpy(vector->data + start, vector->data + offset, vector->data_size);
	memcpy(vector->data + offset, data, vector->data_size);

	vector->size += 1;
}

void	BkVector_Resize_t(struct BkVector* vector, uint32 const size, char const* data)
{
	if (size < vector->size)
		vector->size = size;
	else if (size > vector->size)
	{
		if (size > vector->capacity)
			BkVector_Reserve(vector, vector->capacity + size + 4);

		uint32 offset = vector->size * vector->data_size;

		for (uint32 i = vector->size; i < size; i++)
		{
			memcpy(vector->data + offset, data, vector->data_size);

			offset += vector->data_size;
		}

		vector->size = size;
	}
}