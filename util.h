/*
 *  Copyright (C) 2001, Spectrum Digital, Inc.  All Rights Reserved.
 */
 
#define DSP_CLKIN        12
#define NULLLOOP_CLK     12

typedef struct {
    int freq;        // DSP operating clock
    int clkin;       // DSP input clock
    int pllmult;     // PLL multiplier
    int plldiv;      // PLL divisor
    int clksperusec; // DSP clocks per usec
    int nullloopclk; // DSP clocks per null loop
} DSPCLK;

extern DSPCLK dspclk;

//  Read and write from an address
#define Read(addr) addr
#define Write(addr,data) addr = data

//  Set or clear all bits in the mask
#define ClearMask(addr,mask) addr = (addr & ~(mask))
#define SetMask(addr,mask) addr = (addr | (mask))  

//  Read and write data at addr, only bits in mask are affected
#define ReadMask(addr,mask) (addr & (mask))
#define WriteMask(addr,data,mask) addr = (addr & ~(mask)) | (data)

//  Read and write data at addr, shift data so that bit 0 of data is aligned
//  with lowest set bit in mask.  Only bits in mask are modified.  Example
//  with address 0x1000 initial contents = 0x4007:
//  WriteField(0x1000, 0x56, 0x0ff0) will set address 0x1000 to 0x4567.
#define ReadField(addr,mask) ((addr & (mask)) >> firstbit(mask)) 
#define WriteField(addr,data,mask) addr = (addr & ~(mask)) | (data << firstbit(mask))

extern int firstbit(unsigned short mask);
