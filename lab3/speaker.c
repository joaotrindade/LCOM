#include <minix/syslib.h>
#include <minix/drivers.h>
#include "timer.h"
#include "i8254.h"

int speaker_ctrl(unsigned char on) {
	long unsigned int val;
	sys_inb(SPEAKER_CTRL, &val);
	if(on==1) //liga
		sys_outb(SPEAKER_CTRL, val | SPEAKER_ENABLE | TIMER2_ENABLE) ;
	else //desliga
		sys_outb(SPEAKER_CTRL, val | ~SPEAKER_ENABLE | ~TIMER2_ENABLE) ;

	return 0;
}

int speaker_test(unsigned long freq, unsigned long time) {
	
	speaker_ctrl(1);

	timer_set_square(2,1193182/261);

	sleep(2);

	speaker_ctrl(0);


	return 0;
}

