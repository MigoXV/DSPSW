#include "myapp.h"

// ����ָʾ�ƿ��ƼĴ�����ַ�ͼĴ�������
//#define LBDS (*((unsigned int *)0x400001))
unsigned int * const LBDS=(unsigned int *)0x400001;
// ���岦�뿪�ؿ��ƼĴ�����ַ�ͼĴ�������
//#define DIPS (*(unsigned int *)0x400002)
unsigned int * const DIPS=(unsigned int *)0x400002;

main()
{
	PLL_Init(12);		// ��ʼ��DSP����ʱ��	
	SDRAM_init();	// ��ʼ��EMIF�ӿ�
	while ( 1 )
	{
		*LBDS=*DIPS;	// ��ȡ���뿪��״ֱ̬����ָʾ����ʾ
	}
}




