#include <stdlib.h>
#include "video_gr.h"
#include "pixmap.h"
#include "KBC.h"
#include "timer.h"
#define WAIT_TIME_S 5
#define UPPER_LIMIT 2
#define LOWER_LIMIT 668
#define N_MAX_MISSEIS 50
#define N_MAX_INIMIGOS 50



int spaceship_position;
int last_missile_index;
int pontuacao = 0;
static int hook= 0;
unsigned char scancode;

typedef struct {
	int verticalPos;
	int horizontalPos;
} missile;

typedef struct {
	int verticalPos;
	int horizontalPos;
} enemy;



missile vetor_misseis[N_MAX_MISSEIS];
enemy vetor_inimigos[N_MAX_INIMIGOS];


void drawMainShip(int verticalPos, int erase)
{
	// ERASE : 1 APAGA
	int width, height, x, y;
	char *spaceship_map;
	spaceship_map = (char*)read_xpm(spaceship, &width, &height);

		for(x = verticalPos; x < height+verticalPos ; x++)
		{
			for(y = 0; y <width  ; y++, spaceship_map++)
			{
				if(erase == 0) vg_set_pixel(y,x,*spaceship_map);
				else vg_set_pixel(y,x,0x00);
			}
		}

}

void drawMissile(missile input, int erase)
{
	// ERASE : 1 APAGA
	int width, height, x, y;
	char *missile_map;
	printf("entrou");
	missile_map =  (char*)read_xpm(missil2, &width, &height);
	//printf("saiu");

	//printf("vertical: %d, horizontal: %d \n \n", input.verticalPos, input.horizontalPos);



	for(x = input.verticalPos; x < height + input.verticalPos ; x++)
	{
		for(y = input.horizontalPos; y <width+input.horizontalPos; y++, missile_map++)
		{
			if(erase == 0) vg_set_pixel(y,x,*missile_map);
			else vg_set_pixel(y,x,0x00);
			//printf("entrou\n");

		}
	}

	//printf("X: %d | Y:%d \n",x,y);
}

void drawEnemy(enemy input, int erase)
{
	// ERASE : 1 APAGA
	int width, height, x, y;
	char *enemy;
	enemy = (char*)read_xpm(placeholder, &width, &height);

	for(x = input.verticalPos; x < height + input.verticalPos ; x++)
		{
			for(y = input.horizontalPos; y <width+input.horizontalPos; y++, enemy++)
			{
				if(erase == 0) vg_set_pixel(y,x,*enemy);
				else vg_set_pixel(y,x,0x00);
				//printf("entrou\n");

			}
		}
}

void checkColisao(missile vetor_misseis[]){
	int i, j;
	// vertical + 7
	// horizonal + 50
	for(i = 1; i < last_missile_index;i++)
	{
		if (vg_get_pixel(vetor_misseis[i].horizontalPos + 50,vetor_misseis[i].verticalPos + 7) != 0)
		{
			enemy teste1;
			teste1.horizontalPos = 850;
			teste1.verticalPos = 150;
			drawEnemy(teste1,0);

		}

	}
}

int actualizaMisseis(missile vetor_misseis[]){
	int i,j, removed;
	removed = 0;


	for(i = 1; i < last_missile_index;i++)
	{
		//if (vetor_misseis[i].horizontalPos < 800) vetor_misseis[i].horizontalPos+=10;
		drawMissile(vetor_misseis[i],1);
		vetor_misseis[i].horizontalPos+=10;
	}


	for(i = 1; i < last_missile_index;i++)
	{
		if (vetor_misseis[i].horizontalPos > 800)
		{
			for(j = i-1; j < last_missile_index-1 ; j++)
			{
				vetor_misseis[j] = vetor_misseis[j+1];
			}
			//removed++;
			last_missile_index--;
		}
	}
	//last_missile_index -= removed;

}


int main(){
	spaceship_position = 0;


	int ipc_status, irq_set, esc_found;

	int time_count,refresh_count,enemy_count;
	int missil_i;
	last_missile_index = 1;
	message msg;
	esc_found = 0;
	refresh_count = 0;
	enemy_count = 0;

	//sef_startup();

	missile a1;

	//printf("entrou\n &d     %d", a1.horizontalPos, a1.verticalPos);


	//drawMissile(a1);

	timer_subscribe_int();
	vg_init(0x105);



	//drawMainShip(spaceship_position);
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
									drawMainShip(spaceship_position,1);
									spaceship_position-= 10;
									drawMainShip(spaceship_position,0);
								}
								else
								{
									drawMainShip(spaceship_position,1);
									spaceship_position = 0;
									drawMainShip(spaceship_position,0);
								}


							}
							if (scancode == 0x50) // FOUND SETA BAIXO
							{
								if (spaceship_position + 20 < LOWER_LIMIT)
								{
									drawMainShip(spaceship_position,1);
									spaceship_position+=10;
									drawMainShip(spaceship_position,0);

								}
								else
								{
									drawMainShip(spaceship_position,1);
									spaceship_position = LOWER_LIMIT;
									drawMainShip(spaceship_position,0);

								}

							}

							if (scancode == 0x39) // FOUND B.ESPACOS
							{
								a1.horizontalPos = 150;
								a1.verticalPos = spaceship_position + 50;
								vetor_misseis[last_missile_index] = a1;
								last_missile_index++;
								drawMissile(a1,0);
							}
						}
						if (msg.NOTIFY_ARG & 0x4)
						{

							refresh_count++;
							enemy_count++;
							if (refresh_count == 2)
							{
								//last_missile_index = actualizaMisseis(vetor_misseis,last_missile_index);
								//a1.horizontalPos = 250;
								//a1.verticalPos = 250;

								actualizaMisseis(vetor_misseis);
								checkColisao(vetor_misseis);
								if (last_missile_index > 1)
								for(missil_i = 1; missil_i < last_missile_index; missil_i++)
								{
									drawMissile(vetor_misseis[missil_i],0);
								}
								refresh_count = 0;
							}
							if(enemy_count == 5)
							{
								enemy teste;
								teste.horizontalPos = 600;
								teste.verticalPos = 550;
								drawEnemy(teste,0);

							}
						}

				}
		}

	}
	//printf("Saiu do Ciclo\n");
	timer_unsubscribe_int();
	//printf("Fez unsubscribe ao timer\n");
	kbc_unsubscribe_int();
	//printf("Fez unsubscribe ao KBC\n");
	//sleep(2);
	vg_exit();





	//vg_init(0x105);
	//drawMainShip(spaceship_position);
	//sleep(15);
	//vg_exit(); /* Return to text mode */
	//printf("Saiu\n");
	return 0;
}
