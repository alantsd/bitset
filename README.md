# bitset
Ditset is set for efficient storing bits for embedded systems (ARM cortex M3/M4 microcontrollers).
Implementation use efficient search intruction for ARM cortex M3/M4.
Design aim minimal, no bloat, as lean as possible.

example test prject use Code::Blocks IDE
# function
```
int			bitset_first_set_bit(bitset_t* set);
int			bitset_first_clr_bit(bitset_t* set);

int			bitset_last_set_bit(bitset_t* set);
int			bitset_last_clr_bit(bitset_t* set);
```

# Flash size (-Os)
text	424 bytes


