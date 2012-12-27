
#include "proj.h"
#define WAIT_TIME_S 5
#define UPPER_LIMIT 2
#define LOWER_LIMIT 568
#define N_MAX_MISSEIS 50
#define N_MAX_INIMIGOS 50
#define enemy_height 100



int spaceship_position;
int last_missile_index, last_enemy_index, total_enemies ;
int createdEnemies = 0;
int enemy_positions[N_MAX_INIMIGOS]={0,0,100,200,300,400,500,100,400,500,450};
//int enemy_height = 100;
int pontuacao = 0;
static int hook= 0;
unsigned char scancode;




missile vetor_misseis[N_MAX_MISSEIS];
enemy vetor_inimigos[N_MAX_INIMIGOS];
player_score highscores[50];
int last_highscore = 0;
int lowestHighscore = 0;

void ordenaHighScores()
{
	int i, j;
	player_score temp;
	for( i = 0 ;  i < last_highscore - 1  ; i++)
	{
		for (j = i + 1; j < last_highscore; j++)
		{
			if (highscores[j].pontuacao > highscores[i].pontuacao)
			{
				temp = highscores[i];
				highscores[i] = highscores[j];
				highscores[j] = temp;
			}
		}
	}
}


void writeHighScores(player_score arrayResultados[])
{
	int i, fim;
	player_score temp;
	fim = 15;
	FILE *fp;
	printf("ENTROU ESCRITA\n");
	if(fp = fopen("/usr/src/drivers/proj/highscores", "w"))
	{
		if (last_highscore < 15) fim  = last_highscore;
		for (i = 0; i < fim; i++)
		{
			temp = arrayResultados[i];
			fwrite(&temp,1,sizeof(temp),fp);
		}
		fclose(fp);
	}
	else printf("ERRO DE ESCRITA: FICHEIRO NAO EXISTE!");
}


void readHighScores(player_score arrayResultados[])
{
	player_score temp, vazio;
	strcpy(vazio.nome, "EMPTY");
	vazio.pontuacao = 0;

	vazio.dia = '0';
	vazio.mes = '0';
	vazio.ano = '0';
	vazio.hora = '0';
	vazio.minuto = '0';

	int i,numero_entradas = 0 ;

	FILE *fp;
	//printf("ENTROU LEITURA\n");
	if(fp = fopen("/usr/src/drivers/proj/highscores", "r"))
	{
		last_highscore  = 0;

		fread (&temp,sizeof(temp),1,fp);
		do
		{
			arrayResultados[last_highscore] = temp;
			numero_entradas++;
			last_highscore++;
			if (temp.pontuacao < lowestHighscore) lowestHighscore = temp.pontuacao;
			//printf("Nome: %s \n",temp.nome);
			//printf("Pontuacao: %d \n",temp.pontuacao);
			//printf("%x - %x - %x ! %x : %x\n",temp.dia,temp.mes,temp.ano,temp.hora,temp.minuto);
			fread (&temp,sizeof(temp),1,fp);

		}while(!(feof(fp)));
		fclose(fp);
	}
	else printf("ERRO DE LEITURA: FICHEIRO NAO EXISTE!");
	for(i = numero_entradas; i < 15; i++)
	{
		arrayResultados[i] = vazio;
	}
}

void insertNome(player_score jogador, int _irq_set, int _ipc_status, message _msg)
{
	int enter_found = 0;
	char tempNome[15];
	int nextChar = 0;
	unsigned char scancode2;
	vg_fill(0x00);
	drawInterface(0, 10, 259,0);
	int letra_x, letra_y;
	letra_x = 256;
	letra_y = 341;

	printf("Pontuacao na Funcao : %d\n",jogador.pontuacao);


	while(!enter_found) {
		if(driver_receive(ANY, &_msg, &_ipc_status) != 0) {
			printf("driver_receive failed\n");
			continue;
		}
		if (is_ipc_notify(_ipc_status)) {

			switch (_ENDPOINT_P(_msg.m_source)) {
				case HARDWARE :
					if (_msg.NOTIFY_ARG & _irq_set)
					{
						//printf("entrou ciclo\n");
						scancode2 = read_scancode();
						if (scancode2 == 0x1c) {
							enter_found = 1;
						}

						if (scancode2 == 0x1e)
						{

							drawLetter('A', letra_x, letra_y, 0);
							tempNome[nextChar] = 'A';
							nextChar++;
							letra_y += 25;

						}
						if (scancode2 == 0x30)
						{
							drawLetter('B', letra_x, letra_y, 0);
							tempNome[nextChar] = 'B';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x2e)
						{
							drawLetter('C', letra_x, letra_y, 0);
							tempNome[nextChar] = 'C';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x20)
						{
							drawLetter('D', letra_x, letra_y, 0);
							tempNome[nextChar] = 'D';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x12)
						{
							drawLetter('E', letra_x, letra_y, 0);
							tempNome[nextChar] = 'E';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x21)
						{
							drawLetter('F', letra_x, letra_y, 0);
							tempNome[nextChar] = 'F';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x22)
						{
							drawLetter('G', letra_x, letra_y, 0);
							tempNome[nextChar] = 'G';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x23)
						{
							drawLetter('H', letra_x, letra_y, 0);
							tempNome[nextChar] = 'H';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x17)
						{
							drawLetter('I', letra_x, letra_y, 0);
							tempNome[nextChar] = 'I';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x24)
						{
							drawLetter('J', letra_x, letra_y, 0);
							tempNome[nextChar] = 'J';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x25)
						{
							drawLetter('K', letra_x, letra_y, 0);
							tempNome[nextChar] = 'K';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x26)
						{
							drawLetter('L', letra_x, letra_y, 0);
							tempNome[nextChar] = 'L';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x32)
						{
							drawLetter('M', letra_x, letra_y, 0);
							tempNome[nextChar] = 'M';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x31)
						{
							drawLetter('N', letra_x, letra_y, 0);
							tempNome[nextChar] = 'N';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x18)
						{
							drawLetter('O', letra_x, letra_y, 0);
							tempNome[nextChar] = 'O';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x19)
						{
							drawLetter('P', letra_x, letra_y, 0);
							tempNome[nextChar] = 'P';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x10)
						{
							drawLetter('Q', letra_x, letra_y, 0);
							tempNome[nextChar] = 'Q';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x13)
						{
							drawLetter('R', letra_x, letra_y, 0);
							tempNome[nextChar] = 'R';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x1f)
						{
							drawLetter('S', letra_x, letra_y, 0);
							tempNome[nextChar] = 'S';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x14)
						{
							drawLetter('T', letra_x, letra_y, 0);
							tempNome[nextChar] = 'T';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x16)
						{
							drawLetter('U', letra_x, letra_y, 0);
							tempNome[nextChar] = 'U';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x2f)
						{
							drawLetter('V', letra_x, letra_y, 0);
							tempNome[nextChar] = 'V';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x11)
						{
							drawLetter('W', letra_x, letra_y, 0);
							tempNome[nextChar] = 'W';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x2d)
						{
							drawLetter('X', letra_x, letra_y, 0);
							tempNome[nextChar] = 'X';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x15)
						{
							drawLetter('Y', letra_x, letra_y, 0);
							tempNome[nextChar] = 'Y';
							nextChar++;
							letra_y += 25;
						}
						if (scancode2 == 0x2c)
						{
							drawLetter('Z', letra_x, letra_y, 0);
							tempNome[nextChar] = 'Z';
							nextChar++;
							letra_y += 25;
						}

						tempNome[nextChar] = '\0';
					}
			}
		}
	}
	strcpy(jogador.nome, tempNome);

	long int dia1, mes1, ano1, hora1, minuto1;
	long int *p_dia, *p_mes, *p_ano, *p_hora, *p_minuto;
	//printf("entrou apontadores\n");
	p_dia = &dia1;
	p_mes = &mes1;
	p_ano = &ano1;
	p_hora = &hora1;
	p_minuto = &minuto1;
	//printf("passou apontadores\n");
	get_data(p_dia,p_mes,p_ano,p_hora,p_minuto);
	//printf("saiu");
	printf(" DEPOIS DO GETDATA %x - %x - %x ! %x : %x",dia1,mes1,ano1,hora1,minuto1);

	jogador.ano = ano1;
	jogador.mes = mes1;
	jogador.dia = dia1;
	jogador.hora = hora1;
	jogador.minuto = minuto1;

	highscores[last_highscore] = jogador;
	last_highscore++;
	writeHighScores(highscores);
}





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
	//printf("entrou");
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
	int i, j,k;
	int found = 0;
	// vertical + 7
	// horizonal + 50
	//printf("Last Enemy Index Inicial : %d \n",last_enemy_index );
	for(i = 1; i < last_missile_index;i++)
	{
		found = 0;
		if ( (vg_get_pixel(vetor_misseis[i].horizontalPos + 50,vetor_misseis[i].verticalPos + 7) != 0) && (found == 0) )
		{
			//printf("Detectou colisao \n",j);
			//enemy teste1;
			//teste1.horizontalPos = 850;
			//teste1.verticalPos = 150;
			//drawEnemy(teste1,0);


			//VER QUAL É O INDICE DO VECTOR A QUE CORRESPONDE A COLISAO
			for(j = 1; j < last_enemy_index; j++ )
			{
				if (( ( vetor_misseis[i].verticalPos + 7 > vetor_inimigos[j].verticalPos ) && ( vetor_misseis[i].verticalPos + 7 < vetor_inimigos[j].verticalPos + enemy_height ) ) && (found == 0))
				{
					//printf("Detectou colisao parametrizada enemyindex : %d \n",j);
					found = 1;
					drawEnemy(vetor_inimigos[j],1);
					drawMissile(vetor_misseis[i],1);

					//Eliminar inimigo atingindo do vetor
					for(k = j; k < last_enemy_index-1 ; k++)
					{
						vetor_inimigos[k] = vetor_inimigos[k+1];
						//enemy_positions[k] = enemy_positions[k+1];
					}

					//Eliminar missil que acertou do vetor
					for(k = i-1; k < last_missile_index-1 ; k++)
					{
						vetor_misseis[k] = vetor_misseis[k+1];
					}

					last_missile_index--;
					last_enemy_index--;
					pontuacao+=100;
					drawPontuacao(pontuacao, 956,670,0);
					//drawNumber(1,600,600,0);
					//drawNumber(2,600,956,0);
				}
			}
			actualizaEnemy(0);


		}

	}
	//printf("Last Enemy Index Final : %d\n",last_enemy_index );
}

void drawNumber(int numero, int x_pos, int y_pos, int erase, int small)
{
	//ERASE 1: Apaga
	//SMALL 1: NUMERO PEQUENO
	int width, height, x, y;
	char *imagem;
	//printf("Numero : %d \n",numero);
	switch(numero)
	{
		case 0: {
					if(small == 1) imagem = (char*)read_xpm(zero_small, &width, &height);
					else imagem = (char*)read_xpm(zero, &width, &height);
				}
				break;

		case 1: {
					if(small == 1) imagem = (char*)read_xpm(one_small, &width, &height);
					else imagem = (char*)read_xpm(one, &width, &height);
				}
				break;

		case 2: {
					if(small == 1) imagem = (char*)read_xpm(two_small, &width, &height);
					else imagem = (char*)read_xpm(two, &width, &height);
				}
				break;

		case 3: {
					if(small == 1) imagem = (char*)read_xpm(three_small, &width, &height);
					else imagem = (char*)read_xpm(three, &width, &height);
				}
				break;

		case 4: {
					if(small == 1) imagem = (char*)read_xpm(four_small, &width, &height);
					else imagem = (char*)read_xpm(four, &width, &height);
				}
				break;

		case 5: {
					if(small == 1) imagem = (char*)read_xpm(five_small, &width, &height);
					else imagem = (char*)read_xpm(five, &width, &height);
				}
				break;

		case 6: {
				if(small == 1) imagem = (char*)read_xpm(six_small, &width, &height);
				else imagem = (char*)read_xpm(six, &width, &height);
				}
				break;

		case 7: {
					if(small == 1) imagem = (char*)read_xpm(seven_small, &width, &height);
					else imagem = (char*)read_xpm(seven, &width, &height);
				}
				break;

		case 8: {
					if(small == 1) imagem = (char*)read_xpm(eight_small, &width, &height);
					else imagem = (char*)read_xpm(eight, &width, &height);
				}
				break;

		case 9: {
					if(small == 1) imagem = (char*)read_xpm(nine_small, &width, &height);
					else imagem = (char*)read_xpm(nine, &width, &height);
				}
				break;

		default: imagem = (char*)read_xpm(zero, &width, &height);
				break;
	}
	//printf("Passou o Switch\n");
	for(x = x_pos; x < height + x_pos ; x++)
	{
		//printf("x: %d",x);
		for(y = y_pos; y <width + y_pos; y++, imagem++)
		{
			//printf("y: %d \n",y);
			if(erase == 0) vg_set_pixel(y,x,*imagem);
			else vg_set_pixel(y,x,0x00);
			//printf("entrou\n");
		}
	}

}

void drawLetter(char letra, int x_pos, int y_pos, int erase)
{
	//ERASE 1: Apaga
	int width, height, x, y;
	char *imagem;
	//printf("Numero : %d \n",numero);
	switch(letra)
	{
		case 'A': imagem = (char*)read_xpm(letra_A, &width, &height);
				break;
		case 'B': imagem = (char*)read_xpm(letra_B, &width, &height);
				break;
		case 'C': imagem = (char*)read_xpm(letra_C, &width, &height);
				break;
		case 'D': imagem = (char*)read_xpm(letra_D, &width, &height);
				break;
		case 'E': imagem = (char*)read_xpm(letra_E, &width, &height);
				break;
		case 'F': imagem = (char*)read_xpm(letra_F, &width, &height);
				break;
		case 'G': imagem = (char*)read_xpm(letra_G, &width, &height);
				break;
		case 'H': imagem = (char*)read_xpm(letra_H, &width, &height);
				break;
		case 'I': imagem = (char*)read_xpm(letra_I, &width, &height);
				break;
		case 'J': imagem = (char*)read_xpm(letra_J, &width, &height);
				break;
		case 'K': imagem = (char*)read_xpm(letra_K, &width, &height);
				break;
		case 'L': imagem = (char*)read_xpm(letra_L, &width, &height);
				break;
		case 'M': imagem = (char*)read_xpm(letra_M, &width, &height);
				break;
		case 'N': imagem = (char*)read_xpm(letra_N, &width, &height);
				break;
		case 'O': imagem = (char*)read_xpm(letra_O, &width, &height);
				break;
		case 'P': imagem = (char*)read_xpm(letra_P, &width, &height);
				break;
		case 'Q': imagem = (char*)read_xpm(letra_Q, &width, &height);
				break;
		case 'R': imagem = (char*)read_xpm(letra_R, &width, &height);
				break;
		case 'S': imagem = (char*)read_xpm(letra_S, &width, &height);
				break;
		case 'T': imagem = (char*)read_xpm(letra_T, &width, &height);
				break;
		case 'V': imagem = (char*)read_xpm(letra_V, &width, &height);
				break;
		case 'U': imagem = (char*)read_xpm(letra_U, &width, &height);
				break;
		case 'W': imagem = (char*)read_xpm(letra_W, &width, &height);
				break;
		case 'X': imagem = (char*)read_xpm(letra_X, &width, &height);
				break;
		case 'Y': imagem = (char*)read_xpm(letra_Y, &width, &height);
				break;
		case 'Z': imagem = (char*)read_xpm(letra_Z, &width, &height);
				break;
		default: imagem = (char*)read_xpm(letra_A, &width, &height);
				break;
	}
	//printf("Passou o Switch\n");
	for(x = x_pos; x < height + x_pos ; x++)
	{
		//printf("x: %d",x);
		for(y = y_pos; y <width + y_pos; y++, imagem++)
		{
			//printf("y: %d \n",y);
			if(erase == 0) vg_set_pixel(y,x,*imagem);
			else vg_set_pixel(y,x,0x00);
			//printf("entrou\n");
		}
	}

}

void drawInterface(int numero_id, int x_pos, int y_pos, int erase)
{
	//ERASE 1: Apaga
	int width, height, x, y;
	char *imagem;
	switch(numero_id)
	{
		case 0: imagem = (char*)read_xpm(insert_name, &width, &height);
				break;

	}
	for(x = x_pos; x < height + x_pos ; x++)
	{
		//printf("x: %d",x);
		for(y = y_pos; y <width + y_pos; y++, imagem++)
		{
			//printf("y: %d \n",y);
			if(erase == 0) vg_set_pixel(y,x,*imagem);
			else vg_set_pixel(y,x,0x00);
			//printf("entrou\n");
		}
	}
}

void drawPontuacao(int valor,int x_pos, int y_pos, int small)
{
	//6 Algarismos- y: 590
	// Primeiro algarismo x: 780
	//	824, 868, 912, 956, 1000
	int largura = 44;
	int aux, temp, n_algarismos;
	int last_x_pos = x_pos;
	int last_y_pos = y_pos;
	aux = valor;
	n_algarismos = 0;

	if(small = 1) largura = 20;

	while(aux >= 10)
	{
		temp = aux%10;
		aux = aux/10;
		//printf("Temp: %d | aux: %d | last_y_pos: %d | last_x_pos: %d | \n",temp,aux,last_y_pos,last_x_pos);
		drawNumber(temp, last_y_pos, last_x_pos, 0, small );
		last_x_pos = last_x_pos - largura - 2; // 2 de espacamento


		n_algarismos++;
	}
	drawNumber(aux, last_y_pos, last_x_pos, 0, small );
	last_x_pos = last_x_pos - largura - 2;
	n_algarismos++;

	while(n_algarismos < 6)
	{
		drawNumber(0, last_y_pos, last_x_pos, 0,small );
		last_x_pos = last_x_pos - largura  - 2; // 2 de espacamento
		n_algarismos++;
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

void actualizaEnemy(int move){
	// MOVE = 1 - MOVIMENTA O INIMIGO
	int i,j, removed;
	removed = 0;

	for(i = 1; i < last_enemy_index;i++)
	{
		//if (vetor_misseis[i].horizontalPos < 800) vetor_misseis[i].horizontalPos+=10;
		drawEnemy(vetor_inimigos[i],1);
		if(move == 1) vetor_inimigos[i].horizontalPos-=20;
		drawEnemy(vetor_inimigos[i],0);
	}


	for(i = 1; i < last_enemy_index;i++)
	{
		if (vetor_inimigos[i].horizontalPos < 10)
		{
			for(j = i-1; j < last_enemy_index-1 ; j++)
			{
				vetor_inimigos[j] = vetor_inimigos[j+1];
			}
			last_enemy_index--;
		}
	}
}

void createEnemy(){
	enemy temp;
	int i;
	//printf("Ciclo: \n");
	//for(i = 1; i < 5; i++) printf(" %d ",enemy_positions[i]);
	//printf("\n");
	temp.verticalPos = enemy_positions[createdEnemies+1];
	temp.horizontalPos = 700;
	//printf("entrou : %d", temp.verticalPos );

	vetor_inimigos[last_enemy_index] = temp;
	drawEnemy(temp,0);
	last_enemy_index++;
	createdEnemies++;


}

void drawGUI()
{
	vg_draw_line(0,668,1023,668,0x36);
}

int jogo(int _irq_set, int _ipc_status, message _msg){
	spaceship_position = 334;


	int ipc_status, irq_set, esc_found;
	int game_over = 0;
	int time_count,refresh_count,enemy_count,enemy_refresh;
	int missil_i;
	total_enemies = 9;
	last_missile_index = 1;
	last_enemy_index = 1;
	message msg;
	esc_found = 0;
	refresh_count = 0;
	enemy_count = 0;
	enemy_refresh = 0;
	pontuacao = 0;

	readHighScores(highscores);
	player_score jogador1;

	//sef_startup();

	missile a1;

	//printf("entrou\n &d     %d", a1.horizontalPos, a1.verticalPos);


	//drawMissile(a1);

	timer_subscribe_int();
	//vg_init(0x105);
	vg_fill(0x00);
	drawGUI();
	drawPontuacao(pontuacao, 956, 670, 0);
	drawMainShip(spaceship_position,0);

	//drawMainShip(spaceship_position);
	//irq_set = kbc_subscribe_int();

	while(!esc_found && !game_over) {
			if(driver_receive(ANY, &_msg, &_ipc_status) != 0) {
				printf("driver_receive failed\n");
				continue;
			}
			if (is_ipc_notify(_ipc_status)) {

				switch (_ENDPOINT_P(_msg.m_source)) {
					case HARDWARE :
						if (_msg.NOTIFY_ARG & _irq_set)
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
						if (_msg.NOTIFY_ARG & 0x4)
						{

							refresh_count++;
							enemy_count++;
							enemy_refresh++;
							if (refresh_count == 2)
							{
								//last_missile_index = actualizaMisseis(vetor_misseis,last_missile_index);
								//a1.horizontalPos = 250;
								//a1.verticalPos = 250;

								actualizaMisseis(vetor_misseis);
								checkColisao(vetor_misseis);
								//if ( last_enemy_index>0 ) actualizaEnemy();
								if (last_missile_index > 1)
								for(missil_i = 1; missil_i < last_missile_index; missil_i++)
								{
									drawMissile(vetor_misseis[missil_i],0);
								}
								refresh_count = 0;
							}
							if(enemy_count == 100)
							{

								if ( createdEnemies  < total_enemies )
								{
										createEnemy();
										enemy_count = 0;
								}
								//else game_over = 1;
							}
							if(enemy_refresh == 50)
							{
								actualizaEnemy(1);
								enemy_refresh = 0;
							}
						}

				}
		}

	}
	/*if (game_over == 1)
	{
		jogador1.pontuacao = pontuacao;
		insertNome(jogador1, _irq_set, _ipc_status, _msg);
	}*/

	jogador1.pontuacao = pontuacao;
	insertNome(jogador1, _irq_set, _ipc_status, _msg);

	//printf("Saiu do Ciclo\n");
	timer_unsubscribe_int();
	//printf("Fez unsubscribe ao timer\n");
	//kbc_unsubscribe_int();
	//printf("Fez unsubscribe ao KBC\n");
	//sleep(2);
	//vg_exit();





	//vg_init(0x105);
	//drawMainShip(spaceship_position);
	//sleep(15);
	//vg_exit(); /* Return to text mode */
	//printf("Saiu\n");
	return 0;
}
