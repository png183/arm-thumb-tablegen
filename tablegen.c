#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "alu.c"
#include "instrs.c"

uint32_t decodeALU(uint16_t i) {
  switch((i & 0x03c0) >> 6) {
  case 0x0: return AND(i);
  case 0x1: return EOR(i);
  case 0x2: return LSL(i);
  case 0x3: return LSR(i);
  case 0x4: return ASR(i);
  case 0x5: return ADC(i);
  case 0x6: return SBC(i);
  case 0x7: return ROR(i);
  case 0x8: return TST(i);
  case 0x9: return NEG(i);
  case 0xa: return CMP(i);
  case 0xb: return CMN(i);
  case 0xc: return ORR(i);
  case 0xd: return MUL(i);
  case 0xe: return BIC(i);
  case 0xf: return MVN(i);
  }
  //unreachable
  return UNDEF(i);
}

uint32_t decode(uint16_t i) {
  switch(i >> 8) {
  case 0x00 ... 0x07: return LSL_immed5(i);
  case 0x08 ... 0x0f: return LSR_immed5(i);
  case 0x10 ... 0x17: return ASR_immed5(i);
  case 0x18 ... 0x19: return ADD_dnm(i);
  case 0x1a ... 0x1b: return SUB_dnm(i);
  case 0x1c ... 0x1d: return ADD_immed3(i);
  case 0x1e ... 0x1f: return SUB_immed3(i);
  case 0x20 ... 0x27: return MOV_immed8(i);
  case 0x28 ... 0x2f: return CMP_immed8(i);
  case 0x30 ... 0x37: return ADD_immed8(i);
  case 0x38 ... 0x3f: return SUB_immed8(i);
  case 0x40 ... 0x43: return decodeALU(i);
  case 0x44         : return ADD_hi(i);
  case 0x45         : return CMP_hi(i);
  case 0x46         : return MOV_hi(i);
  case 0x47         : return BX(i);
  case 0x48 ... 0x4f: return LDR_pc_immed8(i);
  case 0x50 ... 0x51: return STR_dnm(i);
  case 0x52 ... 0x53: return STRH_dnm(i);
  case 0x54 ... 0x55: return STRB_dnm(i);
  case 0x56 ... 0x57: return LDRSB_dnm(i);
  case 0x58 ... 0x59: return LDR_dnm(i);
  case 0x5a ... 0x5b: return LDRH_dnm(i);
  case 0x5c ... 0x5d: return LDRB_dnm(i);
  case 0x5e ... 0x5f: return LDRSH_dnm(i);
  case 0x60 ... 0x67: return STR_immed5(i);
  case 0x68 ... 0x6f: return LDR_immed5(i);
  case 0x70 ... 0x77: return STRB_immed5(i);
  case 0x78 ... 0x7f: return LDRB_immed5(i);
  case 0x80 ... 0x87: return STRH_immed5(i);
  case 0x88 ... 0x8f: return LDRH_immed5(i);
  case 0x90 ... 0x97: return STR_sp_immed8(i);
  case 0x98 ... 0x9f: return LDR_sp_immed8(i);
  case 0xa0 ... 0xa7: return ADD_pc_immed8(i);
  case 0xa8 ... 0xaf: return ADD_sp_immed8(i);
  case 0xb0         : return (i & 0x0080) ? SUB_sp_immed7(i) : ADD_sp_immed7(i);
//case 0xb1 ... 0xb3: return UNDEF(i);
  case 0xb4 ... 0xb5: return PUSH(i);
//case 0xb6 ... 0xbb: return UNDEF(i);
  case 0xbc ... 0xbd: return POP(i);
//case 0xbe ... 0xbf: return UNDEF(i);
  case 0xc0 ... 0xc7: return STMIA(i);
  case 0xc8 ... 0xcf: return LDMIA(i);
  case 0xd0 ... 0xdd: return B_cond(i);
//case 0xde         : return UNDEF(i);  //todo: verify that this does not behave as an unconditional branch
  case 0xdf         : return SWI(i);
  case 0xe0 ... 0xe7: return B(i);
//case 0xe8 ... 0xef: return UNDEF(i);
//case 0xf0 ... 0xf7: return BL_prefix(i);  //todo: this does not appear to have a direct ARM equivalent
//case 0xf8 ... 0xff: return BL_suffix(i);  //todo: this does not appear to have a direct ARM equivalent
  }
  return UNDEF(i);
}

int main() {
  FILE* c = fopen("table.c", "w");
  fprintf(c, "const uint32_t table[0x10000] = {\n");
  for(uint32_t i = 0; i < 0x10000; i++) {
    if(i % 0x100 == 0) fprintf(c, "  ");
    fprintf(c, "0x%08x, ", decode(i));
    if(i % 0x100 == 0xff) fprintf(c, "\n");
  }
  fprintf(c, "};\n");
  fclose(c);

  return 0;
}
