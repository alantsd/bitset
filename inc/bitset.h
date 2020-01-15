#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
* Copyright (c) 2020 Alan Tong Sing Teik.
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/

/**
 * bitset is set for efficient storing bits for embedded systems (ARM M3/M4 microcontrollers)
 * Design aim no bloat, as lean as possible
 *
 */

#define BIT_SET_STORAGE_ELEMENT_BIT			(32)
#define BIT_SET_STORAGE_LEN(bit_count)		(bit_count / BIT_SET_STORAGE_ELEMENT_BIT)

typedef uint32_t	bitset_storage_t;

typedef struct bitset
{
	int						size;
	bitset_storage_t*		bits;
}
bitset_t;

void		bitset_init				(bitset_t* set);
void		bitset_set				(bitset_t* set, int bit_pos);
void		bitset_reset			(bitset_t* set, int bit_pos);
void		bitset_toggle			(bitset_t* set, int bit_pos);

bool        bitset_is_set			(bitset_t const* set, int bit_pos);
bool        bitset_is_clr			(bitset_t const* set, int bit_pos);

/** find bit index */
int		bitset_first_set_bit		(bitset_t* set);
int		bitset_first_clr_bit		(bitset_t* set);

int		bitset_last_set_bit	(bitset_t* set);
int		bitset_last_clr_bit	(bitset_t* set);

/** No logical operation - I don't see common needs for this yet */

uint32_t	reverse_u32(uint32_t x);
#endif
