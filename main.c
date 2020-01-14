#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bitset.h"

void print_bitset(bitset_t* bitset)
{
	for(int i = 0; i <  bitset->size; ++i)
	{
		printf("[%02d]:%d ", i, bitset_is_set(bitset, i));
		if(0 == (i + 1) % 16)
		{
			printf("\n");
		}
	}
	printf("\n");
}
void test_first_set()
{
	uint32_t storage[BIT_SET_STORAGE_LEN(64)];
	bitset_t bitset =
	{
		.bits = storage,
		.size = 64
	};

	bitset_init(&bitset);
	for(int i = 0; i <  bitset.size; ++i)
	{
		bitset_set(&bitset, i);
		assert(bitset_first_set_bit(&bitset) == 0);
	}
	bitset_init(&bitset);
	for(int i = bitset.size - 1; i >= 0; --i)
	{
		bitset_set(&bitset, i);
		assert(bitset_first_set_bit(&bitset) == i);
	}
	for(int i = 0; i <  bitset.size; ++i)
	{
		assert(bitset_first_set_bit(&bitset) == i);
		bitset_reset(&bitset, i);
	}
}
void test_first_clr()
{
	uint32_t storage[BIT_SET_STORAGE_LEN(64)];
	bitset_t bitset =
	{
		.bits = storage,
		.size = 64
	};

	bitset_init(&bitset);
	for(int i = 1; i <  bitset.size; ++i)
	{
		bitset_set(&bitset, i);
		assert(bitset_first_clr_bit(&bitset) == 0);
	}
	for(int i = bitset.size - 1; i > 0; --i)
	{
		bitset_reset(&bitset, i);
		assert(bitset_first_clr_bit(&bitset) == 0);
	}
	bitset_init(&bitset);
	for(int i = 0; i <  bitset.size - 1; ++i)
	{
		assert(bitset_first_clr_bit(&bitset) == i);
		bitset_set(&bitset, i);
	}
	for(int i = 63; i >= 0; --i)
	{
		bitset_reset(&bitset, i);
		assert(bitset_first_clr_bit(&bitset) == i);
	}
}
void test_last_set()
{
	uint32_t storage[BIT_SET_STORAGE_LEN(64)];
	bitset_t bitset =
	{
		.bits = storage,
		.size = 64
	};

	bitset_init(&bitset);
	bitset_set(&bitset, 63);
	for(int i = 0; i <  bitset.size; ++i)
	{
		bitset_set(&bitset, i);
		assert(bitset_last_set_bit(&bitset) == 63);
	}
	for(int i = 0; i <  bitset.size - 1; ++i)
	{
		bitset_reset(&bitset, i);
		assert(bitset_last_set_bit(&bitset) == 63);
	}
	bitset_init(&bitset);
	for(int i = 0; i <  bitset.size; ++i)
	{
		bitset_set(&bitset, i);
		assert(bitset_last_set_bit(&bitset) == i);
	}
	for(int i = 63; i >= 0; --i)
	{
		assert(bitset_last_set_bit(&bitset) == i);
		bitset_reset(&bitset, i);
	}
}
void test_last_clr()
{
	uint32_t storage[BIT_SET_STORAGE_LEN(64)];
	bitset_t bitset =
	{
		.bits = storage,
		.size = 64
	};

	bitset_init(&bitset);
	for(int i = 0; i <  bitset.size - 1; ++i)
	{
		bitset_set(&bitset, i);
		assert(bitset_last_clr_bit(&bitset) == 63);
	}
	for(int i = 0; i <  bitset.size - 1; ++i)
	{
		bitset_reset(&bitset, i);
		assert(bitset_last_clr_bit(&bitset) == 63);
	}

	bitset_init(&bitset);
	for(int i = 63; i >= 0; --i)
	{
		assert(bitset_last_clr_bit(&bitset) == i);
		bitset_set(&bitset, i);
	}
	for(int i = 0; i <  bitset.size - 1; ++i)
	{
		bitset_reset(&bitset, i);
		assert(bitset_last_clr_bit(&bitset) == i);
	}
}

int main()
{
	printf("Hello bitset!\n");
	test_first_set();
	test_first_clr();

	test_last_set();
	test_last_clr();

	uint32_t storage[BIT_SET_STORAGE_LEN(64)];

	bitset_t bitset =
	{
		.bits = storage,
		.size = 64
	};

	bitset_init(&bitset);

	bitset_set(&bitset, 0);
	bitset_set(&bitset, 1);
	bitset_set(&bitset, 2);
	bitset_set(&bitset, 3);

	bitset_set(&bitset, 4);
	bitset_set(&bitset, 5);
	bitset_set(&bitset, 6);
	bitset_set(&bitset, 7);

	bitset_set(&bitset, 31);
	bitset_set(&bitset, 52);
	bitset_set(&bitset, 53);
	bitset_toggle(&bitset, 61);
	bitset_set(&bitset, 60);
	bitset_set(&bitset, 63);
	bitset_reset(&bitset, 63);

	for(int i = 0; i <  bitset.size; ++i)
	{
		printf("[%02d]:%d ", i, bitset_is_set(&bitset, i));
		if(0 == (i + 1) % 16)
		{
			printf("\n");
		}
	}
	printf("\n");
	printf("first_set_bit  :\t%02d\n", bitset_first_set_bit(&bitset));
	printf("first_clear_bit:\t%02d\n", bitset_first_clr_bit(&bitset));

	printf("last_set_bit   :\t%02d\n", bitset_last_set_bit(&bitset));
	printf("last_clr_bit   :\t%02d\n", bitset_last_clr_bit(&bitset));

	return 0;
}
