#include "highscores.h"

#define X_PLAYER 50
#define Y_NOME 25
#define Y_PONTUACAO 520

void print_data(int dia, int mes, int ano, int hora, int minuto, int x_pos, int y_pos)
{
	/*
	int last_y_pos = y_pos;
	if (hora<10){
		drawNumber(0, x_pos, last_y_pos, 0, small );
	}

	*/
}

void print_scores(int _irq_set, int _ipc_status, message _msg)
{
	int i,j;
	char temp_nome[15];
	player_score resultados[50], temp;
	readHighScores(resultados);
	
	vg_fill(0x00);

	//drawPontuacao(222,0, 0, 1);

	for(i= 0; i < 13; i++)
	{
		temp = resultados[i];
		strcpy(temp_nome, temp.nome);
		j = 0;

		while ( (temp_nome[j] != '\0') && (j < 15) )
		{
			drawLetter(temp_nome[j], (i+1)*X_PLAYER, (j+1)*Y_NOME, 0);
			j++;
		}

		drawPontuacao(temp.pontuacao,Y_PONTUACAO, (i+1)*X_PLAYER, 1);




	}

}
