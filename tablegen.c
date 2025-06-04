#include <stdint.h>
#include <stdio.h>

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

uint32_t decodeALU_HI(uint16_t i) {
  switch((i & 0x0300) >> 8) {
  case 0x0: return ADD_hi(i);
  case 0x1: return CMP_hi(i);
  case 0x2: return MOV_hi(i);
  case 0x3: return     BX(i);
  }
  //unreachable
  return UNDEF(i);
}

uint32_t decodeLDRSTR_SHB(uint16_t i) {
  switch((i & 0x0e00) >> 9) {
  case 0x0: return STR_dnm(i);
  case 0x1: return STRH_dnm(i);
  case 0x2: return STRB_dnm(i);
  case 0x3: return LDRSB_dnm(i);
  case 0x4: return LDR_dnm(i);
  case 0x5: return LDRH_dnm(i);
  case 0x6: return LDRB_dnm(i);
  case 0x7: return LDRSH_dnm(i);
  }
  //unreachable
  return UNDEF(i);
}

uint32_t decodeMISC(uint16_t i) {
  switch((i & 0x0f00) >> 8) {
  case 0x0        : return (i & 0x0080) ? SUB_sp_immed7(i) : ADD_sp_immed7(i);
  case 0x4 ... 0x5: return PUSH(i);
  case 0xc ... 0xd: return POP(i);
  }
  return UNDEF(i);
}

uint32_t decodeBCC_SWI(uint16_t i) {
  switch((i & 0x0f00) >> 8) {
  case 0xe: return UNDEF(i);
  case 0xf: return SWI(i);
  }
  return B_cond(i);
}

uint32_t decode(uint16_t i) {
  switch(i >> 10) {
  case 0x00 ... 0x01: return LSL_immed5(i);
  case 0x02 ... 0x03: return LSR_immed5(i);
  case 0x04 ... 0x05: return ASR_immed5(i);
  case 0x06         : return (i & 0x0200) ? SUB_dnm(i)    : ADD_dnm(i);
  case 0x07         : return (i & 0x0200) ? SUB_immed3(i) : ADD_immed3(i);
  case 0x08 ... 0x09: return MOV_immed8(i);
  case 0x0a ... 0x0b: return CMP_immed8(i);
  case 0x0c ... 0x0d: return ADD_immed8(i);
  case 0x0e ... 0x0f: return SUB_immed8(i);
  case 0x10         : return decodeALU(i);
  case 0x11         : return decodeALU_HI(i);
  case 0x12 ... 0x13: return LDR_pc_immed8(i);
  case 0x14 ... 0x17: return decodeLDRSTR_SHB(i);
  case 0x18 ... 0x19: return STR_immed5(i);
  case 0x1a ... 0x1b: return LDR_immed5(i);
  case 0x1c ... 0x1d: return STRB_immed5(i);
  case 0x1e ... 0x1f: return LDRB_immed5(i);
  case 0x20 ... 0x21: return STRH_immed5(i);
  case 0x22 ... 0x23: return LDRH_immed5(i);
  case 0x24 ... 0x25: return STR_sp_immed8(i);
  case 0x26 ... 0x27: return LDR_sp_immed8(i);
  case 0x28 ... 0x29: return ADD_pc_immed8(i);
  case 0x2a ... 0x2b: return ADD_sp_immed8(i);
  case 0x2c ... 0x2f: return decodeMISC(i);
  case 0x30 ... 0x31: return STMIA(i);
  case 0x32 ... 0x33: return LDMIA(i);
  case 0x34 ... 0x37: return decodeBCC_SWI(i);
  case 0x38 ... 0x39: return B(i);
//case 0x3a ... 0x3b: return UNDEF(i);
//case 0x3c ... 0x3d: return BL_prefix(i);  //todo: this does not appear to have a direct ARM equivalent
//case 0x3e ... 0x3f: return BL_suffix(i);  //todo: this does not appear to have a direct ARM equivalent
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
