/*
 *  Copyright (C) 2001, Spectrum Digital, Inc.  All Rights Reserved.
 */

#include "5509.h"
#include "util.h"

DSPCLK dspclk;

/*void PLL_Init(int freq)
{
    PC55XX_CMOD pCMOD = (PC55XX_CMOD)C55XX_CLKMD_ADDR;

    // Calculate PLL multiplier values (only integral multiples now)
    dspclk.clkin = DSP_CLKIN;
    dspclk.pllmult = freq / dspclk.clkin;
    dspclk.freq = dspclk.pllmult * dspclk.clkin;
    dspclk.plldiv = 0;
    dspclk.nullloopclk = NULLLOOP_CLK;

    // Turn the PLL off
    ClearMask(pCMOD -> clkmd, CLKMD_PLLENABLE);
    while(ReadMask(pCMOD -> clkmd, CLKMD_LOCK));

    // Initialize PLL flags
    ClearMask(pCMOD -> clkmd, CLKMD_IAI);
    SetMask(pCMOD -> clkmd, CLKMD_IOB | CLKMD_BREAKLN);

    // Set the multiplier/divisor
    WriteMask(pCMOD -> clkmd,
        CLKMD_PLLDIV_1 | CLKMD_BYPASSDIV_1,
        CLKMD_PLLDIV_MASK | CLKMD_BYPASSDIV_MASK);
    WriteField(pCMOD -> clkmd, dspclk.pllmult, CLKMD_PLLMULT_MASK);

    // Enable the PLL and wait for lock
    SetMask(pCMOD -> clkmd, CLKMD_PLLENABLE);
    while(!ReadMask(pCMOD -> clkmd, CLKMD_LOCK));
}*/

void PLL_Init(int freq)
{
    int i;
    DSPCLK dspclk;
    ioport unsigned int *clkmd;
    ioport unsigned int *sysr;
    clkmd=(unsigned int *)0x1c00;
    
    sysr=(unsigned int *)0x07fd;
    
    // Calculate PLL multiplier values (only integral multiples now)
    dspclk.clkin = DSP_CLKIN;
    dspclk.pllmult = (freq *2)/ dspclk.clkin;
    
    if(dspclk.pllmult>= 32)dspclk.pllmult=31; 
   // dspclk.nullloopclk = NULLLOOP_CLK;

    // Turn the PLL off
    *clkmd &= ~0x10; //pll enable = 0;
    for(i=*clkmd&1; i!= 0 ;i=*clkmd&1);

    // Initialize PLL flags
    *clkmd &= ~0x4000; // iai=0;
    *clkmd |= 0x2000;  // iob=1;
      // Set the multiplier/divisor
  //  WriteMask(pCMOD -> clkmd,
  //      CLKMD_PLLDIV_1 | CLKMD_BYPASSDIV_1,
  //      CLKMD_PLLDIV_MASK | CLKMD_BYPASSDIV_MASK);
    *clkmd &= ~0xc;
    *clkmd |= 4;
    *clkmd &= ~0x60;
    *clkmd |= 0x20;
    //WriteField(pCMOD -> clkmd, dspclk.pllmult, CLKMD_PLLMULT_MASK);
    *clkmd &= ~0x0f80;
    *clkmd |= dspclk.pllmult<<7;
    // Enable the PLL and wait for lock
    *clkmd|=0x10;
    for(i=0;i<10;i++);
    for(i=*clkmd&1; i!= 1 ;i=*clkmd&1);
    
    *sysr=2;

    
}

void INT_Enable(unsigned short mask)
{
    *IER0 = *IER0 | mask;
}

void INT_Disable(unsigned short mask)
{
    *IER0 = *IER0 & ~mask;
}

void INT_EnableGlobal()
{
    asm(" BCLR INTM");
}

void INT_DisableGlobal()
{
    asm(" BSET INTM");
}

void INT_SetVec(unsigned long addr)
{
    *IVPD = (unsigned short)(addr >> 8);
    *IVPH = *IVPD;
}

void INT_InstallHandler(int vecno, void(*handler)())
{
    unsigned long handler_addr, vec_addr;
    unsigned short *pdata;

    // Calculate address of vector
    vec_addr = (unsigned long)*IVPD;
    vec_addr = vec_addr << 7;
    vec_addr += vecno * 4;

    // Insert branch to handler in vector location
    handler_addr = (unsigned long)handler;
    pdata = (unsigned short *)vec_addr;
    *pdata++ = ((handler_addr >> 16) & 0x00ff) | 0xea00;
    *pdata++ = handler_addr & 0xffff;
    *pdata++ = 0x5e80;
    *pdata++ = 0x5f80;
}

void SWDelayUsec(unsigned int usec)
{
    unsigned int i, j, loopsperusec;

    loopsperusec = dspclk.freq / dspclk.nullloopclk;
    for (i=0;i<usec;i++)
        for (j = 0; j < loopsperusec; j++);
}

void SWDelayMsec(unsigned int msec)
{
    unsigned int i;
    for (i=0;i<msec;i++)
        SWDelayUsec(1000);
}

int firstbit(unsigned short mask)
{
    int shiftamt;
    unsigned short bit;

    // Find offset of first bit in mask
    bit = 1;
    for (shiftamt = 0; shiftamt < 16; shiftamt++) {
        if (bit & mask)
            break;
        bit = bit << 1;
    }

    return shiftamt;
}
