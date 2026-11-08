/* SPDX-License-Identifier: MIT */
/*
 * at89s52.h - Register Declarations for the Atmel AT89S52 Processor
 *
 * Copyright (c) 2026 YOUNGJIN JOO (neoelec@gmail.com)
 */

#ifndef AT89S52_H
#define AT89S52_H

#include <at89x52.h>

#ifdef AT89x52_H
#undef AT89x52_H
#endif

/* BYTE addressable registers */
SFR(DP0L, 0x82);
SFR(DP0H, 0x83);
SFR(DP1L, 0x84);
SFR(DP1H, 0x85);
SFR(AUXR, 0x8E);
SFR(AUXR1, 0xA2);
SFR(WDTRST, 0xA6);

/* BIT definitions for bits that are not directly accessible */
/* AUXR bits */
#define DISALE 0x01
#define DISRTO 0x08
#define WDIDLE 0x10

#define DISALE_ 0x01
#define DISRTO_ 0x08
#define WDIDLE_ 0x10

/* AUXR1 bits */
#define DPS 0x01

#define DPS_ 0x01

#endif /*AT89S52_H*/
