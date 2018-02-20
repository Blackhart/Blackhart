// Standard headers.
#include <stdlib.h>
#include <string.h>

// Blackhart.foundation headers.
#include "foundation\BkArray.h"
#include "foundation\BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkArray_Initialize(struct BkArray* this, uint8 const data_size)
{
	BK_ASSERT(BK_ISNULL(this));

	this->data = NULL;
	this->size = 0;
	this->capacity = 0;
	this->data_size = data_size;
}

void	BkArray_Reserve(struct BkArray* this, size_t const capacity)
{
	BK_ASSERT(BK_ISNULL(this));

	if (capacity <= this->capacity)
		return;

	size_t n = capacity * this->data_size;
	
	char* data = malloc(n);
	BK_ERROR(BK_ISNULL(data), "Memory system failed to allocate memory block!");

	if (this->size != 0)
	{
		n = this->size * this->data_size;
		memcpy(data, this->data, n);
	}

	this->capacity = capacity;

	free(this->data);
	this->data = data;
}

void	BkArray_Clear(struct BkArray* this)
{
	BK_ASSERT(BK_ISNULL(this));

	this->size = 0;
}

void	BkArray_Destroy(struct BkArray* this)
{
	BK_ASSERT(BK_ISNULL(this));

	free(this->data);
	this->data = NULL;
	this->capacity = 0;
	this->size = 0;
}

void	BkArray_Erase(struct BkArray* this, size_t const index)
{
	BK_ASSERT(BK_ISNULL(this));
	BK_ASSERT(index >= this->size);

	if (this->size == 1)
	{
		this->size = 0;
		return;
	}

	this->size -= 1;

	size_t offset = index * this->data_size;
	size_t start = this->size * this->data_size;

	memcpy(this->data + offset, this->data + start, this->data_size);
}

void	BkArray_PushBack_t(struct BkArray* this, char const* data)
{
	BK_ASSERT(BK_ISNULL(this));
	BK_ASSERT(BK_ISNULL(data));

	if ((this->size + 1) > this->capacity)
	{
		BkArray_Reserve(this, this->capacity + 4);
	}
	
	memcpy(this->data + (this->size * this->data_size), data, this->data_size);
	
	this->size += 1;
}

void	BkArray_PopBack(struct BkArray* this)
{
	BK_ASSERT(BK_ISNULL(this));

	this->size -= 1;
}

void	BkArray_Insert_t(struct BkArray* this, size_t const index, char const* data)
{
	BK_ASSERT(BK_ISNULL(this));
	BK_ASSERT(BK_ISNULL(this));
	BK_ASSERT(index > this->size);

	if (index == this->size)
	{
		BkArray_PushBack_t(this, data);
		return;
	}

	if ((this->size + 1) > this->capacity)
	{
		BkArray_Reserve(this, this->capacity + 4);
	}

	size_t offset = index * this->data_size;
	size_t start = this->size * this->data_size;

	memcpy(this->data + start, this->data + offset, this->data_size);
	memcpy(this->data + offset, data, this->data_size);

	this->size += 1;
}

void	BkArray_Resize_t(struct BkArray* this, size_t const size, char const* data)
{
	BK_ASSERT(BK_ISNULL(this));
	BK_ASSERT(BK_ISNULL(data));

	if (size < this->size)
		this->size = size;
	else if (size > this->size)
	{
		if (size > this->capacity)
			BkArray_Reserve(this, this->capacity + size + 4);

		size_t offset = this->size * this->data_size;

		for (size_t i = this->size; i < size; i++)
		{
			memcpy(this->data + offset, data, this->data_size);

			offset += this->data_size;
		}

		this->size = size;
	}
}