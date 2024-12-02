#include <stdio.h>
#include <stdlib.h>

#include "botao.h"

botao *botao_cria(unsigned short x, unsigned short y, char* comando)
{

    botao *new_botao = (botao*) malloc(sizeof(botao));
    new_botao->x = x;
    new_botao->y = y;
    new_botao->tam_x = BOTAO_TAM_X;
    new_botao->tam_y = BOTAO_TAM_Y;
    new_botao->comando = comando;

    return new_botao;

}

unsigned char botao_click(botao *botao, unsigned short x, unsigned short y)
{

    if ((x >= botao->x - botao->tam_x/2 && x <= botao->x + botao->tam_x/2) &&
        (y >= botao->y - botao->tam_y/2 && y <= botao->y + botao->tam_y/2))
	return 1;
    return 0;

}

void botao_destroi(botao *botao)
{

    free(botao);

}
