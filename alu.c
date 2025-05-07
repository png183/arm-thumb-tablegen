#define rm ((i & 0x0038) >> 3)
#define rs ((i & 0x0038) >> 3)
#define rd ((i & 0x0007) >> 0)
#define rn ((i & 0x0007) >> 0)

uint32_t AND(uint16_t i) { return 0xe0100000 | (rd << 16) | (rd << 12) |              rm; }
uint32_t EOR(uint16_t i) { return 0xe0300000 | (rd << 16) | (rd << 12) |              rm; }
uint32_t LSL(uint16_t i) { return 0xe1b00010 |              (rd << 12) | (rs <<  8) | rd; }
uint32_t LSR(uint16_t i) { return 0xe1b00030 |              (rd << 12) | (rs <<  8) | rd; }
uint32_t ASR(uint16_t i) { return 0xe1b00050 |              (rd << 12) | (rs <<  8) | rd; }
uint32_t ADC(uint16_t i) { return 0xe0b00000 | (rd << 16) | (rd << 12) |              rm; }
uint32_t SBC(uint16_t i) { return 0xe0d00000 | (rd << 16) | (rd << 12) |              rm; }
uint32_t ROR(uint16_t i) { return 0xe1b00070 |              (rd << 12) | (rs <<  8) | rd; }
uint32_t TST(uint16_t i) { return 0xe1100000 | (rn << 16) |                           rm; }
uint32_t NEG(uint16_t i) { return 0xe2700000 | (rm << 16) | (rd << 12)                  ; }
uint32_t CMP(uint16_t i) { return 0xe1500000 | (rn << 16) |                           rm; }
uint32_t CMN(uint16_t i) { return 0xe1700000 | (rn << 16) |                           rm; }
uint32_t ORR(uint16_t i) { return 0xe1900000 | (rd << 16) | (rd << 12) |              rm; }
uint32_t MUL(uint16_t i) { return 0xe0100090 | (rd << 16) |              (rd <<  8) | rm; }
uint32_t BIC(uint16_t i) { return 0xe1d00000 | (rd << 16) | (rd << 12) |              rm; }
uint32_t MVN(uint16_t i) { return 0xe1f00000 |              (rd << 12) |              rm; }

#undef rm
#undef rs
#undef rd
#undef rn
