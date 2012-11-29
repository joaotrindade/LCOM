#include <stdlib.h>
#include "video_gr.h"
#include "pixmap.h"
#define WAIT_TIME_S 5

int main(){
	//sef_startup();
	int width, height, x, y;
	char *spaceship_map;
	spaceship_map = read_xpm(spaceship, &width, &height);
	printf("loaded pixmap\n");
	printf ("width: %d  - height: %d\n",width,height);

	/*for(x = 0; x < height; x++)
	{
		for(y = 0; y < width ; y++, spaceship_map++)
		{
			printf("%d ",*spaceship_map);
		}
		printf("\n");
	}*/



	//sleep(10);

	vg_init(0x105); /* Change to video mode */

	for(x = 0; x < height ; x++)
	{
		for(y = 0; y <width  ; y++, spaceship_map++)
		{
			vg_set_pixel(y,x,*spaceship_map);

		}
	}

	sleep(15);

	//vg_fill(41);
	//vg_set_pixel(2,2, 41);
	//vg_draw_line(0,0,700,700,03);
	//sleep(WAIT_TIME_S);
	//vg_draw_line(0,0,700,900,36);
	//sleep(WAIT_TIME_S); /* for WAIT_TIME_S (5) seconds */
	vg_exit(); /* Return to text mode */
	return 0;
}
