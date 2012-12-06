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

typedef struct {
	int verticalPos;
	int horizontalPos;
} missile;





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

void drawMissile(missile input)
{
	int width, height, x, y;
	char *missile_map;
	//printf("entrou");
	missile_map =  read_xpm(missil2, &width, &height);
	//printf("saiu");

	//printf("vertical: %d, horizontal: %d \n \n", input.verticalPos, input.horizontalPos);



	for(x = input.verticalPos; x < height + input.verticalPos ; x++)
	{
		for(y = input.horizontalPos; y <width+input.horizontalPos; y++, missile_map++)
		{
			vg_set_pixel(y,x,*missile_map);
			//printf("entrou\n");

		}
	}

	//printf("X: %d | Y:%d \n",x,y);
}


int main(){
	spaceship_position = 0;


	int ipc_status, irq_set, esc_found;
	message msg;
	esc_found = 0;

	//sef_startup();

	//missile *a1 = malloc(sizeof(struct missile));
	missile a1;
	a1.horizontalPos = 20;
	a1.verticalPos = 20;
	//printf("entrou\n &d     %d", a1.horizontalPos, a1.verticalPos);


	//drawMissile(a1);


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
								if (spaceship_position - 20 > UPPER_LIMIT)
								{
									vg_eraseShip(0x00);

									spaceship_position-= 10;
									drawMainShip(spaceship_position);
								}
								else
								{
									vg_eraseShip(0x00);
									spaceship_position = 0;
									drawMainShip(spaceship_position);
								}


							}
							if (scancode == 0x50) // FOUND SETA BAIXO
							{
								if (spaceship_position + 20 < LOWER_LIMIT)
								{
									vg_eraseShip(0x00);
									spaceship_position+=10;
									drawMainShip(spaceship_position);

								}
								else
								{
									vg_eraseShip(0x00);
									spaceship_position = LOWER_LIMIT;
									drawMainShip(spaceship_position);

								}

							}

							if (scancode == 0x39) // FOUND B.ESPACOS
							{
								a1.horizontalPos = 150;
								a1.verticalPos = spaceship_position + 50;
								drawMissile(a1);
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
