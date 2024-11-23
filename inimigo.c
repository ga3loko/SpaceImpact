#include <stdio.h>
#include <stdlib.h>

#include "inimigo.h"

inimigo* inimigo_cria(unsigned char tipo, unsigned short x, unsigned short y, unsigned short spawn)
{
    
    inimigo *new_inimigo = (inimigo*) malloc(sizeof(inimigo));
    new_inimigo->tipo = tipo;
    new_inimigo->x = x;
    new_inimigo->y = y;
    new_inimigo->spawn = spawn;

    switch (tipo) {
        case 0:
	    new_inimigo->hp = 2;
	    new_inimigo->tam_x = INIMIGO1_TAM_X;
	    new_inimigo->tam_y = INIMIGO1_TAM_Y;
	    new_inimigo->arma = NULL;
	    new_inimigo->direcao = 0;
	    new_inimigo->vel = INIMIGO1_VEL;
	    break;
	case 1:
	    new_inimigo->hp = 3;
	    new_inimigo->tam_x = INIMIGO2_TAM_X;
	    new_inimigo->tam_y = INIMIGO2_TAM_Y;
	    new_inimigo->arma = pistola_cria();
	    new_inimigo->direcao = 1;
	    new_inimigo->vel = INIMIGO2_VEL;
	    break;
	default:
	    break;
    }

    return new_inimigo;

}

void inimigo_destroi(inimigo *inimigo)
{
    pistola_destroi(inimigo->arma);
    free(inimigo);
}

void inimigo_move(inimigo *inimigo, unsigned char passo, short min_x, unsigned short max_y, unsigned char *valid)
{

    if (inimigo->direcao) {
        switch (inimigo->direcao) {
            case 1:
		if ((inimigo->y - passo * inimigo->vel) - inimigo->tam_y/2 >= 0)
		    inimigo->y -= passo * inimigo->vel;
		else
		    inimigo->direcao = 2;
		break;
            case 2:
		if ((inimigo->y + passo * inimigo->vel) 
				+ inimigo->tam_y/2 <= max_y)
		    inimigo->y += passo * inimigo->vel;
		else
		    inimigo->direcao = 1;
		break;
	}
    }	    

    if ((inimigo->x - passo * inimigo->vel) - inimigo->tam_x/2 >= min_x)
	inimigo->x -= passo * inimigo->vel;
    else {
        inimigo_destroi(inimigo);
	*valid = 0;
    }
	

}

void inimigo_atira(inimigo *inimigo)
{
   
    if (!inimigo->arma)
	return;

    bullet *shot;

    shot = pistola_atira(inimigo->x - inimigo->tam_x/2, inimigo->y, 0, 
		         inimigo->arma);
    if (shot)
	inimigo->arma->shots = shot;

}
