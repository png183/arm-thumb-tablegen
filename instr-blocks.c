#define rm ((i & 0x0038) >> 3)
#define rs ((i & 0x0038) >> 3)
#define rd ((i & 0x0007) >> 0)
#define rn ((i & 0x0007) >> 0)

//ALU
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

#define rm  ((i & 0x0078) >> 3)
#define rd (((i & 0x0080) >> 4) | (i & 0x0007))

//ALU_HI
uint32_t ADD_hi(uint16_t i) { return 0xe0800000 | (rd << 16) | (rd << 12) | rm; }
uint32_t CMP_hi(uint16_t i) { return 0xe1500000 | (rd << 16) |              rm; }
uint32_t MOV_hi(uint16_t i) { return 0xe1a00000 |              (rd << 12) | rm; }
uint32_t     BX(uint16_t i) { return 0xe12fff10 |                           rm; }

#undef rm
#undef rd

#define immed5 ((i & 0x07c0) >> 6)
#define immed3 ((i & 0x01c0) >> 6)
#define rm     ((i & 0x01c0) >> 6)
#define rn     ((i & 0x0038) >> 3)
#define rd     ((i & 0x0007) >> 0)

//LDRSTR_SHB
uint32_t     STR_dnm(uint16_t i) { return 0xe7800000 | (rn << 16) | (rd << 12) | rm; }
uint32_t    STRH_dnm(uint16_t i) { return 0xe18000b0 | (rn << 16) | (rd << 12) | rm; }
uint32_t    STRB_dnm(uint16_t i) { return 0xe7c00000 | (rn << 16) | (rd << 12) | rm; }
uint32_t   LDRSB_dnm(uint16_t i) { return 0xe19000d0 | (rn << 16) | (rd << 12) | rm; }
uint32_t     LDR_dnm(uint16_t i) { return 0xe7900000 | (rn << 16) | (rd << 12) | rm; }
uint32_t    LDRH_dnm(uint16_t i) { return 0xe19000b0 | (rn << 16) | (rd << 12) | rm; }
uint32_t    LDRB_dnm(uint16_t i) { return 0xe7d00000 | (rn << 16) | (rd << 12) | rm; }
uint32_t   LDRSH_dnm(uint16_t i) { return 0xe19000f0 | (rn << 16) | (rd << 12) | rm; }

//top-level decode
uint32_t     ADD_dnm(uint16_t i) { return 0xe0900000 | (rn << 16) | (rd << 12) | rm; }
uint32_t     SUB_dnm(uint16_t i) { return 0xe0500000 | (rn << 16) | (rd << 12) | rm; }
uint32_t  ADD_immed3(uint16_t i) { return 0xe2900000 | (rn << 16) | (rd << 12) | immed3; }
uint32_t  SUB_immed3(uint16_t i) { return 0xe2500000 | (rn << 16) | (rd << 12) | immed3; }
uint32_t  STR_immed5(uint16_t i) { return 0xe5800000 | (rn << 16) | (rd << 12) | (immed5 << 2); }
uint32_t  LDR_immed5(uint16_t i) { return 0xe5900000 | (rn << 16) | (rd << 12) | (immed5 << 2); }
uint32_t STRB_immed5(uint16_t i) { return 0xe5c00000 | (rn << 16) | (rd << 12) | immed5; }
uint32_t LDRB_immed5(uint16_t i) { return 0xe5d00000 | (rn << 16) | (rd << 12) | immed5; }

#undef immed5
#undef immed3
#undef rm
#undef rn
#undef rd
