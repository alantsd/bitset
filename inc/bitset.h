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
	/*uint8_t				ecc[8]*/
	int						size;
	bitset_storage_t*		bits;
}
bitset_t;

#define START_BIT					0x80000000u

#define	BIT_SET_1_BIT				0x80000000u
#define	BIT_SET_2_BIT				0xc0000000u
#define	BIT_SET_3_BIT				0xe0000000u
#define	BIT_SET_4_BIT				0xf0000000u
#define	BIT_SET_5_BIT				0xf8000000u
#define	BIT_SET_6_BIT				0xfc000000u
#define	BIT_SET_7_BIT				0xfe000000u
#define	BIT_SET_8_BIT				0xff000000u

#define	BIT_RESET_1_BIT				(BIT_SET_1_BIT)
#define	BIT_RESET_2_BIT				(BIT_SET_2_BIT)
#define	BIT_RESET_3_BIT				(BIT_SET_3_BIT)
#define	BIT_RESET_4_BIT				(BIT_SET_4_BIT)
#define	BIT_RESET_5_BIT				(BIT_SET_5_BIT)
#define	BIT_RESET_6_BIT				(BIT_SET_6_BIT)
#define	BIT_RESET_7_BIT				(BIT_SET_7_BIT)
#define	BIT_RESET_8_BIT				(BIT_SET_8_BIT)


void		bitset_init				(bitset_t* set);

/** not support multi-bit set/reset across BIT_SET_STORAGE_ELEMENT_BIT boundary
*	@param count - use BIT_SET_X_BIT or BIT_RESET_X_BIT as count argument.
*/
void		bitset_set_n			(bitset_t* set, int bit_pos, uint32_t count);
void		bitset_reset_n			(bitset_t* set, int bit_pos, uint32_t count);

static inline
void		bitset_set				(bitset_t* set, int bit_pos) { bitset_set_n(set,  bit_pos, BIT_SET_1_BIT); }

static inline
void		bitset_reset			(bitset_t* set, int bit_pos) { bitset_reset_n(set,  bit_pos, BIT_RESET_1_BIT); }

void		bitset_reset			(bitset_t* set, int bit_pos);
void		bitset_toggle			(bitset_t* set, int bit_pos);

bool		bitset_is_set			(bitset_t const* set, int bit_pos);
bool		bitset_is_clr			(bitset_t const* set, int bit_pos);

/** find bit index */
int			bitset_first_set_bit	(bitset_t* set);
int			bitset_first_clr_bit	(bitset_t* set);

int			bitset_last_set_bit		(bitset_t* set);
int			bitset_last_clr_bit		(bitset_t* set);

/** No logical operation - I don't see common needs for this yet */
#endif
