#include <stdlib.h>
#include "video_gr.h"
#define WAIT_TIME_S 2

int main(){
	sef_startup();
	vg_init(0x105); /* Change to video mode */
	vg_fill(25);
	sleep(WAIT_TIME_S); /* for WAIT_TIME_S (5) seconds */
	vg_exit(); /* Return to text mode */
	return 0;
}
