#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>

#include "test7.h"


#define COM1 0x3F8
#define COM2 0x2F8
#define RBR 0
#define IER 1
#define IIR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6
#define SR  7
#define DLL 1
#define DLM 0
#define BIT7 (1 << 7) 
#define BIT6 (1 << 6) 
#define BIT5 (1 << 5) 
#define BIT4 (1 << 4) 
#define BIT3 (1 << 3) 
#define BIT2 (1 << 2) 
#define BIT1 (1 << 1) 
#define BIT0 (1 << 0) 

int test_conf(unsigned short base_addr) 
{
	unsigned long lcr,dlab,dlm,dll,bitrate,enableRegister;

    	sys_inb(base_addr+LCR, &lcr);
	printf("LCR: 0x0%x \n",lcr);
	
	printf("Bits p/ char\n");

	if(lcr & BIT1)
	{ 
		if(lcr & BIT0)
		{
			printf("Number of bits p/ char: 8 \n");
		}
		else printf("Number of bits p/ char: 7 \n");
		
	}
	else
	{ 
		if(lcr & BIT0)
		{
			printf("Number of bits p/ char: 6 \n");
		}
		else printf("Number of bits p/ char: 5 \n");
	}
	
	printf("Stop bits\n");

	if(lcr & BIT2)
	{
		printf("Number of stop bits: 2\n");
	}
	else
	{
		printf("Number of stop bits: 1\n");
	}
	
	printf("Parity control \n");

	if(lcr & BIT3)
	{ 
		if(lcr & BIT5)
		{
			if(lcr & BIT4)
			{
				printf("Parity bit is 0 (always)\n");
			}
			else
			{
				printf("Parity bit is 1 (always)\n");
			}
		}
		else
		{
			if(lcr & BIT4)
			{
				printf("Even parity\n");
			}
			else
			{
				printf("Odd parity\n");
			}
		}
	}
	else printf("No parity\n");

	sys_inb(base_addr+LCR, &dlab);
	dlab= dlab | 0x80;
	sys_outb(base_addr+LCR, dlab);

	sys_inb(base_addr+DLM, &dlm);
	printf("DLM: 0x%x \n", dlm);

	sys_inb(base_addr+DLL, &dll);
	printf("DLL: 0x%x \n", dll);	

	bitrate= 115200 / ( (dll * 256) + dlm);
	printf("Bit-rate: %d",bitrate);

	sys_inb(base_addr+LCR, &dlab);
	dlab = dlab&0x7F;
	sys_outb(base_addr+LCR, dlab);

	sys_inb(base_addr+IER, &enableRegister);
	printf("Interrupt enable register (ier): 0x%x \n", enableRegister);


	if(enableRegister & BIT0)
	{

		printf("Received Data Available Interrupt - enabled \n");

	}
	else
	{
		printf("Received Data Available Interrupt - disabled\n");

	}

	if(enableRegister & BIT1)
	{

		printf("Transmitter Holding Register Empty Interrupt - enabled\n");

	}
	else
	{
		printf("Transmitter Holding Register Empty Interrupt - disabled\n");
	}

	if(enableRegister & BIT2)
	{
		printf("Receiver Line Status Interrupt - enabled\n");
	}
	else
	{
		printf("Receiver Line Status Interrupt - disabled\n");
	}





    return 0;
}

