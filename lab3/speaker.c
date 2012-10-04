#include <minix/syslib.h>
#include <minix/drivers.h>
#include "timer.h"

int speaker_ctrl(unsigned char on) {
	
	if(on==1) //liga
		sys_outb(0x61, 0x3) ;
	else //desliga
		sys_outb(0x61, 0x0) ;

	return 0;
}

int speaker_test(unsigned long freq, unsigned long time) {
	
	speaker_ctrl(1);
	while( timer_test_int(time*60) != 1 )
	{
		timer_set_square(2, freq);
	} ;

	return 0;
}

