-w
-stack 500
-sysstack 500
-l rts55x.lib

MEMORY 
{
    DARAM:	o=0x100,	l=0x7f00
    VECT :  o=0x8000,	l=0x100
    DARAM2: o=0x8100,	l=0x7f00
    SARAM:  o=0x10000,	l=0x30000
    SDRAM:	o=0x40000,	l=0x3e0000
}

SECTIONS
{
    .text:    {} > DARAM 
    .vectors: {} > VECT 
    .trcinit: {} > DARAM 
    .gblinit: {} > DARAM 
     frt:     {} > DARAM 
    
    .cinit:   {} > DARAM 
    .pinit:   {} > DARAM 
    .sysinit: {} > DARAM 
    .bss:     {} > DARAM2 
    .far:     {} > DARAM2 
    .const:   {} > DARAM2 
    .switch:  {} > DARAM2 
    .sysmem:  {} > DARAM2 
    .cio:     {} > DARAM2 
    .MEM$obj: {} > DARAM2 
    .sysheap: {} > DARAM2 
    .sysstack {} > DARAM2 
    .stack:   {} > DARAM2 
    
}


