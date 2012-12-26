#ifndef __PROJ_H
#define __PROJ_H

#include <stdlib.h>
#include "video_gr.h"
#include "pixmap.h"
#include "KBC.h"
#include "RTC.h"
#include "timer.h"
#include "algarismos.h"
#include "algarismos_small.h"
#include "alfabeto.h"
#include "interface_xpm.h"
#include <string.h>


typedef struct {
	int verticalPos;
	int horizontalPos;
} missile;

typedef struct {
	int verticalPos;
	int horizontalPos;
} enemy;

typedef struct {
	int verticalPos;
	int horizontalPos;
	int vida;
} boss;

typedef struct {
	char nome[15];
	long  pontuacao;
	long int dia;
	long int mes;
	long int ano;
	long int hora;
	long int minuto;
} player_score;


int jogo(int _irq_set, int _ipc_status, message _msg);
void readHighScores(player_score arrayResultados[]);
void actualizaEnemy(int move);
void drawPontuacao(int valor,int x_pos, int y_pos, int small);
void drawNumber(int numero, int x_pos, int y_pos, int erase, int small);
void drawLetter(char letra, int x_pos, int y_pos, int erase);
void drawInterface(int numero_id, int x_pos, int y_pos, int erase);

#endif /* __PROJ */
