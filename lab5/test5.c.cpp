#include <minix/syslib.h>
#include <minix/drivers.h>

#include "test5.h"

#define singleBit(byte) (0x01 & byte)

#define DELAY_US 		900000
#define DURATION 		30		/*30 segundos*/
#define KBC_CMD			0x64
#define MOUSE_CMD		0x60

#define KBD_IRQ1			1


int test_packet()
{
	unsigned char packet[3] ; 	/* guarda bytes do rato*/
	unsigned short count = 0 ;		/* identifica o byte recebido*/
	int time_counter = 0 ;				/* conta o tempo de execucao*/

	unsigned long scancode ;
	int hook_id = 0x00;
	int ipc_status;
	message msg;

	/*subscrever insterrupções*/
	sys_irqsetpolicy(KBD_IRQ1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
	sys_irqenable(&hook_id);

	sys_inb(0x64, 0xD4) ;

	while(time_counter<DURATION)
	{
		if(count==3)
			count=0;

		if( driver_receive(ANY, &msg, &ipc_status) != 0)
		{
			if(is_ipc_policy(ipc_status) && ENDPOINT_P(msg.m_source) == HARDWARE )
				{
					sys_outb(0x60 , &scancode) ;
					packet[count]=scancode ;
					printf("scancode: %c" , scancode);
				}
		}
		count++ ;
		time_counter++ ; /*errado! usar funcao do timer para contar os segundos*/
	}

	sys_irqdisable(&hook_id);
	sys_irqrmpolicy(&hook_id);
	return 0;
}


