uint32_t STRH_immed5(uint16_t i) {
  return 0xe1c000b0 | ((i & 0x0038) << 13) | ((i & 0x0007) << 12) | ((i & 0x0600) >> 1) | ((i & 0x01c0) >> 5);
}

uint32_t LDRH_immed5(uint16_t i) {
  return 0xe1d000b0 | ((i & 0x0038) << 13) | ((i & 0x0007) << 12) | ((i & 0x0600) >> 1) | ((i & 0x01c0) >> 5);
}

uint32_t ADD_sp_immed7(uint16_t i) {
  return 0xe28ddf00 | (i & 0x7f);
}

uint32_t SUB_sp_immed7(uint16_t i) {
  return 0xe24ddf00 | (i & 0x7f);
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
