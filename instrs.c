uint32_t LSL_immed5(uint16_t i) {
  return 0xe1b00000 | ((i & 0x0007) << 12) | ((i & 0x07c0) << 1) | ((i & 0x0038) >> 3);
}

uint32_t LSR_immed5(uint16_t i) {
  return 0xe1b00020 | ((i & 0x0007) << 12) | ((i & 0x07c0) << 1) | ((i & 0x0038) >> 3);
}

uint32_t ASR_immed5(uint16_t i) {
  return 0xe1b00040 | ((i & 0x0007) << 12) | ((i & 0x07c0) << 1) | ((i & 0x0038) >> 3);
}

uint32_t MOV_immed8(uint16_t i) {
  return 0xe3b00000 | ((i & 0x0700) << 4) | (i & 0x00ff);
}

uint32_t CMP_immed8(uint16_t i) {
  return 0xe3500000 | ((i & 0x0700) << 8) | (i & 0x00ff);
}

uint32_t ADD_immed8(uint16_t i) {
  return 0xe2900000 | ((i & 0x0700) << 8) | ((i & 0x0700) << 4) | (i & 0x00ff);
}

uint32_t SUB_immed8(uint16_t i) {
  return 0xe2500000 | ((i & 0x0700) << 8) | ((i & 0x0700) << 4) | (i & 0x00ff);
}

uint32_t LDR_pc_immed8(uint16_t i) {
  return 0xe59f0000 | ((i & 0x0700) << 4) | ((i & 0x00ff) << 2);
}

uint32_t STRH_immed5(uint16_t i) {
  return 0xe1c000b0 | ((i & 0x0038) << 13) | ((i & 0x0007) << 12) | ((i & 0x0600) >> 1) | ((i & 0x01c0) >> 5);
}

uint32_t LDRH_immed5(uint16_t i) {
  return 0xe1d000b0 | ((i & 0x0038) << 13) | ((i & 0x0007) << 12) | ((i & 0x0600) >> 1) | ((i & 0x01c0) >> 5);
}

uint32_t STR_sp_immed8(uint16_t i) {
  return 0xe58d0000 | ((i & 0x0700) << 4) | ((i & 0x00ff) << 2);
}

uint32_t LDR_sp_immed8(uint16_t i) {
  return 0xe59d0000 | ((i & 0x0700) << 4) | ((i & 0x00ff) << 2);
}

uint32_t ADD_pc_immed8(uint16_t i) {
  return 0xe28f0f00 | ((i & 0x0700) << 4) | (i & 0x00ff);
}

uint32_t ADD_sp_immed8(uint16_t i) {
  return 0xe28d0f00 | ((i & 0x0700) << 4) | (i & 0x00ff);
}

uint32_t ADD_sp_immed7(uint16_t i) {
  return 0xe28ddf00 | (i & 0x7f);
}

uint32_t SUB_sp_immed7(uint16_t i) {
  return 0xe24ddf00 | (i & 0x7f);
}

uint32_t PUSH(uint16_t i) {
  return 0xe92d0000 | ((i & 0x0100) << 6) | (i & 0x00ff);
}

uint32_t POP(uint16_t i) {
  return 0xe8bd0000 | ((i & 0x0100) << 7) | (i & 0x00ff);
}

uint32_t STMIA(uint16_t i) {
  return 0xe8a00000 | ((i & 0x0700) << 8) | (i & 0x00ff);
}

uint32_t LDMIA(uint16_t i) {
  uint32_t rn = (i & 0x0700) >> 8;
  uint32_t writeback = 0x00200000 * (((~i) >> rn) & 1);
  return 0xe8900000 | writeback | (rn << 16) | (i & 0x00ff);
}

uint32_t B_cond(uint16_t i) {
  int32_t immed8 = i;
  immed8 <<= 24;
  immed8 >>= 24;
  return ((i & 0x0f00) << 20) | 0x0a000000 | (immed8 & 0x00ffffff);
}

uint32_t SWI(uint16_t i) {
  return 0xef000000 | (i & 0x00ff);
}

uint32_t B(uint16_t i) {
  int32_t immed11 = i;
  immed11 <<= 21;
  immed11 >>= 21;
  return 0xea000000 | (immed11 & 0x00ffffff);
}

uint32_t UNDEF(uint16_t i) {
  //use an easily-identifiable opcode that is undefined on a wide range of ARM architecture versions
  return 0xe7ffffff;
}
