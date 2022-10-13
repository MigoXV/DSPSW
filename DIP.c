#include "myapp.h"

// 定义指示灯控制寄存器地址和寄存器类型
//#define LBDS (*((unsigned int *)0x400001))
unsigned int * const LBDS=(unsigned int *)0x400001;
// 定义拨码开关控制寄存器地址和寄存器类型
//#define DIPS (*(unsigned int *)0x400002)
unsigned int * const DIPS=(unsigned int *)0x400002;

main()
{
	PLL_Init(12);		// 初始化DSP运行时钟	
	SDRAM_init();	// 初始化EMIF接口
	while ( 1 )
	{
		*LBDS=*DIPS;	// 读取拨码开关状态直接送指示灯显示
	}
}




