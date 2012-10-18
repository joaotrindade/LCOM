#include <minix/syslib.h>
#include <minix/drivers.h>

#include "test5.h"

#define singleBit(byte) (0x01 & byte)

#define DELAY_US 		900000
#define DURATION 		30		/*30 segundos*/
#define KBC_CMD			0x64
#define MOUSE_CMD		0x60

#define WRITE_REG  0x64

#define KBD_IRQ1			1


int test_packet()
{

	unsigned char packet[3] ; 	/* guarda bytes do rato*/
	unsigned short count = 0 ;		/* identifica o byte recebido*/
	int byte_counter = 0 ;				/* conta o numero de bytes recebidos */

	unsigned long scancode ;
	int hook_id = 0x00;
	int ipc_status;
	message msg;

	/*subscrever insterrup��es*/
	sys_irqsetpolicy(KBD_IRQ1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
	sys_irqenable(&hook_id);

	sys_inb(WRITE_REG, 0xD4) ;

	while(byte_counter<DURATION)
	{
		if(count==3)
			count=0;

		if( driver_receive(ANY, &msg, &ipc_status) != 0 )
		{
			if(is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE )
				{
					sys_outb(0x60 , &scancode) ;
					packet[count]=scancode ;
					printf("scancode: %c" , scancode);
				}
		}
		count++ ;
		byte_counter++ ;
	}

	sys_irqdisable(&hook_id);
	sys_irqrmpolicy(&hook_id);
	return 0;
}


