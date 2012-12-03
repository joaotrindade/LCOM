#include <stdlib.h>
#include "video_gr.h"
#include "pixmap.h"
#include "KBC.h"
#define WAIT_TIME_S 5
#define UPPER_LIMIT 2
#define LOWER_LIMIT 668

int spaceship_position;
static int hook= 0;
unsigned char scancode;


void drawMainShip(int verticalPos)
{
	int width, height, x, y;
	char *spaceship_map;
	spaceship_map = read_xpm(spaceship, &width, &height);

		for(x = verticalPos; x < height+verticalPos ; x++)
		{
			for(y = 0; y <width  ; y++, spaceship_map++)
			{
				vg_set_pixel(y,x,*spaceship_map);

			}
		}

}


int main(){
	spaceship_position = 0;


	int ipc_status, irq_set, esc_found;
	message msg;
	esc_found = 0;

	vg_init(0x105);
	drawMainShip(spaceship_position);
	irq_set = kbc_subscribe_int();

	while(!esc_found) {
			if(driver_receive(ANY, &msg, &ipc_status) != 0) {
				printf("driver_receive failed\n");
				continue;
			}
			if (is_ipc_notify(ipc_status)) {

				switch (_ENDPOINT_P(msg.m_source)) {
					case HARDWARE :
						if (msg.NOTIFY_ARG & irq_set)
						{
							//printf("entrou ciclo\n");
							scancode = read_scancode();
							if (scancode == 0x81) {
								esc_found = 1;
							}
							if (scancode == 0x48) // FOUND SETA CIMA
							{
								if (spaceship_position - 10 > UPPER_LIMIT)
								{
									vg_fill(0x00);
									spaceship_position-= 10;
									drawMainShip(spaceship_position);
								}
								else
								{
									vg_fill(0x00);
									spaceship_position = 0;
									drawMainShip(spaceship_position);
								}


							}
							if (scancode == 0x50) // FOUND SETA BAIXO
							{
								if (spaceship_position + 10 < LOWER_LIMIT)
								{
									vg_fill(0x00);
									spaceship_position+=10;
									drawMainShip(spaceship_position);

								}
								else
								{
									vg_fill(0x00);
									spaceship_position = LOWER_LIMIT;
									drawMainShip(spaceship_position);

								}

							}
						}
				}
		}

	}

	kbc_unsubscribe_int();

	sleep(2);
	vg_exit();





	//vg_init(0x105);
	//drawMainShip(spaceship_position);
	//sleep(15);
	//vg_exit(); /* Return to text mode */
	return 0;
}
