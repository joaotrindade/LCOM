#include <stdlib.h>
#include "video_gr.h"
#define WAIT_TIME_S 5

int main(){
	vg_init(0x105); /* Change to video mode */
	//vg_fill(41);
	vg_set_pixel(2,2, 41);
	sleep(WAIT_TIME_S); /* for WAIT_TIME_S (5) seconds */
	vg_exit(); /* Return to text mode */
	return 0;
}
