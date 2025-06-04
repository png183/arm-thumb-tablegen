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

#define immed5    ((i & 0x07c0) >> 6)
#define immed5_hi ((i & 0x0600) >> 9)
#define immed5_lo ((i & 0x01c0) >> 6)
#define immed3    ((i & 0x01c0) >> 6)
#define rm        ((i & 0x01c0) >> 6)
#define rn        ((i & 0x0038) >> 3)
#define rd        ((i & 0x0007) >> 0)
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
uint32_t STRH_immed5(uint16_t i) { return 0xe1c000b0 | (rn << 16) | (rd << 12) | (immed5_hi << 8) | (immed5_lo << 1); }
uint32_t LDRH_immed5(uint16_t i) { return 0xe1d000b0 | (rn << 16) | (rd << 12) | (immed5_hi << 8) | (immed5_lo << 1); }
#undef immed5
#undef immed5_hi
#undef immed5_lo
#undef immed3
#undef rm
#undef rn
#undef rd

#define immed5 ((i & 0x07c0) >> 6)
#define rm     ((i & 0x0038) >> 3)
#define rd      (i & 0x0007)
//top-level decode
uint32_t LSL_immed5(uint16_t i) { return 0xe1b00000 | (rd << 12) | (immed5 << 7) | rm; }
uint32_t LSR_immed5(uint16_t i) { return 0xe1b00020 | (rd << 12) | (immed5 << 7) | rm; }
uint32_t ASR_immed5(uint16_t i) { return 0xe1b00040 | (rd << 12) | (immed5 << 7) | rm; }
#undef immed5
#undef rm
#undef rd

#define immed8  (i & 0x00ff)
#define rd     ((i & 0x0700) >> 8)
//top-level decode
uint32_t    MOV_immed8(uint16_t i) { return 0xe3b00000 |              (rd << 12) | immed8; }
uint32_t    CMP_immed8(uint16_t i) { return 0xe3500000 | (rd << 16) |              immed8; }
uint32_t    ADD_immed8(uint16_t i) { return 0xe2900000 | (rd << 16) | (rd << 12) | immed8; }
uint32_t    SUB_immed8(uint16_t i) { return 0xe2500000 | (rd << 16) | (rd << 12) | immed8; }
uint32_t LDR_pc_immed8(uint16_t i) { return 0xe59f0000 |              (rd << 12) | (immed8 << 2); }
uint32_t STR_sp_immed8(uint16_t i) { return 0xe58d0000 |              (rd << 12) | (immed8 << 2); }
uint32_t LDR_sp_immed8(uint16_t i) { return 0xe59d0000 |              (rd << 12) | (immed8 << 2); }
uint32_t ADD_pc_immed8(uint16_t i) { return 0xe28f0f00 |              (rd << 12) | immed8; }
uint32_t ADD_sp_immed8(uint16_t i) { return 0xe28d0f00 |              (rd << 12) | immed8; }
//BCC_SWI
uint32_t           SWI(uint16_t i) { return 0xef000000 |                           immed8; }
#undef immed8
#undef rd

#define immed7 (i & 0x7f)
//MISC
uint32_t ADD_sp_immed7(uint16_t i) { return 0xe28ddf00 | immed7; }
uint32_t SUB_sp_immed7(uint16_t i) { return 0xe24ddf00 | immed7; }
#undef immed7

#define rlist  (i & 0x00ff)
#define lr    ((i & 0x0100) >> 8)
#define pc    ((i & 0x0100) >> 8)
#define rn    ((i & 0x0700) >> 8)
#define writeback (((~i) >> rn) & 1)
//MISC
uint32_t  PUSH(uint16_t i) { return 0xe92d0000 |                                              (lr << 14) | rlist; }
uint32_t   POP(uint16_t i) { return 0xe8bd0000 |                                  (pc << 15) |             rlist; }
//top-level decode
uint32_t STMIA(uint16_t i) { return 0xe8a00000 |                     (rn << 16) |                          rlist; }
uint32_t LDMIA(uint16_t i) { return 0xe8900000 | (writeback << 21) | (rn << 16) |                          rlist; }
#undef rlist
#undef lr
#undef pc
#undef rn
#undef writeback

#define immed8_s ((((int32_t)i << 24) >> 24) & 0x00ffffff)
#define cond ((i & 0x0f00) >> 8)
//BCC_SWI
uint32_t B_cond(uint16_t i) { return (cond << 28) | 0x0a000000 | immed8_s; }
#undef immed8_s
#undef cond

#define immed11_s ((((int32_t)i << 21) >> 21) & 0x00ffffff)
//top-level decode
uint32_t B(uint16_t i) { return 0xea000000 | immed11_s;}
#undef immed11_s

//any A32 opcode of the form 0xe7f---f- is labeled as "permanently undefined" in ARM documentation
uint32_t UNDEF(uint16_t i) { return 0xe7ffffff; }
