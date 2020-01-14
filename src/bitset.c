
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
        return;
    }

    memset(set->bits, 0, BIT_SET_STORAGE_LEN(set->size)* sizeof(bitset_storage_t));
}
void bitset_set(bitset_t* set, int bit_pos)
{
	assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

    int element	= bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
    int offset		= bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

    set->bits[element] |= (START_BIT >> offset);

}
void bitset_toggle(bitset_t* set, int bit_pos)
{
	assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

    int element	= bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
    int offset		= bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

    set->bits[element] ^= (START_BIT >> offset);
}
void bitset_reset(bitset_t* set, int bit_pos)
{
    assert(CHECK_BIT_POS(bit_pos) && "invalid bit position input");

    int element    = bit_pos / BIT_SET_STORAGE_ELEMENT_BIT;
    int offset     = bit_pos % BIT_SET_STORAGE_ELEMENT_BIT;

    set->bits[element] &= ~(START_BIT >> offset);
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
/** reverse a uint8_t */
static uint8_t reverse_u8(uint8_t x)
{
   const char table[] = {0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1, 0x9, 0x5, 0xD, 0x3,0xB, 0x7,0xF};
   return table[(x & 0xF0) >> 4] | (table[x & 0x0F] << 4);
}
/** reverse a uint16_t */
static uint16_t reverse_u16(uint16_t x)
{
   return reverse_u8(x >> 8) | (reverse_u8(x & 0xFF) << 8);
}
/** reverse a uint32_t */
uint32_t reverse_u32(uint32_t x)
{
   return reverse_u16(x >> 16) | (reverse_u16(x & 0xFFFF) << 16);
}
int bitset_last_set_bit(bitset_t* set)
{
    for(int i = BIT_SET_STORAGE_LEN(set->size) - 1, bit_index = set->size - 1; i >= 0; --i)
    {
        bitset_storage_t element = set->bits[i];
		if(0 != element)
		{
			return bit_index - __builtin_clz(reverse_u32(element));
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
			return bit_index - __builtin_clz(reverse_u32(~element));
		}
		bit_index -= BIT_SET_STORAGE_ELEMENT_BIT;
    }
    return -1;
}
