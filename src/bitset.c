
#include "bitset.h"
#include <string.h>

#ifdef HAS_ASSERT
#include <assert.h>
#else
#define assert(x)
#endif // HAS_ASSERT

#define START_BIT					0x80000000ul
#define ELEMENT_VALUE_MAX			0xFFFFffff
#define CHECK_BIT_POS(x)			(0 <= bit_pos && bit_pos < set->size)

void bitset_init(bitset_t* set)
{
	/** must be a multiple of BIT_SET_STORAGE_ELEMENT_BIT */
	if(0 != set->size % BIT_SET_STORAGE_ELEMENT_BIT)
	{
		assert(0);
		return;
	}

	memset(set->bits, 0, BIT_SET_STORAGE_LEN(set->size)* sizeof(bitset_storage_t));
}
void bitset_set_n(bitset_t* set, int bit_pos, uint32_t count)
{
	assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

	int element		= bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
	int offset		= bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

	set->bits[element] |= (count >> offset);
}
void bitset_reset_n(bitset_t* set, int bit_pos, uint32_t count)
{
	assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

	int element    = bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
	int offset     = bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

	set->bits[element] &= ~(count >> offset);
}
void bitset_toggle(bitset_t* set, int bit_pos)
{
	assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

	int element		= bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
	int offset		= bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

	set->bits[element] ^= (START_BIT >> offset);
}
bool bitset_is_set(bitset_t const* set, int bit_pos)
{
	assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

	int element    = bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
	int offset     = bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

	return (set->bits[element] & (START_BIT >> offset));
}
bool bitset_is_clr(bitset_t const* set, int bit_pos)
{
	return false == bitset_is_set(set, bit_pos);
}
int bitset_first_set_bit(bitset_t* set)
{
	for(int i = 0, bit_index = 0; i < BIT_SET_STORAGE_LEN(set->size); ++i)
	{
		bitset_storage_t element = set->bits[i];
		if(0 != element)
		{
			return bit_index + __builtin_clz(element);
		}
		bit_index += BIT_SET_STORAGE_ELEMENT_BIT;
	}
	return -1;
}
int bitset_first_clr_bit(bitset_t* set)
{
	for(int i = 0, bit_index = 0; i < BIT_SET_STORAGE_LEN(set->size); ++i)
	{
		bitset_storage_t element = set->bits[i];
		if(ELEMENT_VALUE_MAX != element)
		{
			return bit_index + (__builtin_clz(~element));
		}
		bit_index += BIT_SET_STORAGE_ELEMENT_BIT;
	}
	return -1;
}
int bitset_last_set_bit(bitset_t* set)
{
	for(int i = BIT_SET_STORAGE_LEN(set->size) - 1, bit_index = set->size - 1; i >= 0; --i)
	{
		bitset_storage_t element = set->bits[i];
		if(0 != element)
		{
			return bit_index - __builtin_ctz((element));
		}
		bit_index -= BIT_SET_STORAGE_ELEMENT_BIT;
	}
	return -1;
}
int bitset_last_clr_bit(bitset_t* set)
{
	for(int i = BIT_SET_STORAGE_LEN(set->size) - 1, bit_index = set->size - 1; i >= 0; --i)
	{
		bitset_storage_t element = set->bits[i];
		if(ELEMENT_VALUE_MAX != element)
		{
			return bit_index - __builtin_ctz((~element));
		}
		bit_index -= BIT_SET_STORAGE_ELEMENT_BIT;
	}
	return -1;
}
