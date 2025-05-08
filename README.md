# ARM Thumb Tablegen
This program outputs a file called `table.c`, which contains a table of values where indexing into the table with a Thumb opcode should return its 32-bit ARM equivalent.
The generated table is dedicated towards emulator developers who wish to decode Thumb instructions to ARM, and has been tested to work without issue in a modified build of ares.

Possible sources of error when decoding from Thumb to ARM:
- Thumb instructions that explicitly treat R15 as word-aligned require their corresponding ARM opcode to do the same.
- Branch instructions have their 24-bit displacement field multiplied by 4 when the Thumb bit of CPSR is clear, and 2 when the Thumb bit is set.
- Where R15 offsets are required, the offset size should be determined from the Thumb bit of CPSR.

Limitations:
- The BL instruction (opcodes `0xf000 - 0xffff`) does not have an obvious ARM equivalent, and is currently not supported. Attempting to index into the table with said instructions will currently return an undefined ARM opcode.
- Currently, the instruction table is specific to ARM7TDMI. However, adding support for any other ARM architecture versions where Thumb instructions can be decoded to 32-bit ARM instructions should be relatively straightforward.
- The source code uses GNU case range extensions, which may not be supported on other compilers.
