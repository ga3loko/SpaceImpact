#include <stdio.h>
#include <stdlib.h>

#include "inimigo.h"
#include "defines.h"

inimigo* inimigo_cria(enum tipoInimigo tipo, unsigned short x, unsigned short y, unsigned short spawn)
{
    
    inimigo *new_inimigo = (inimigo*) malloc(sizeof(inimigo));
    new_inimigo->x = x;
    new_inimigo->y = y;
    new_inimigo->spawn = spawn;

    switch (tipo) {
        case INIMIGO1:
	    new_inimigo->tipo = INIMIGO1;
	    new_inimigo->hp = INIMIGO1_HP;
	    new_inimigo->tam_x = INIMIGO1_TAM_X;
	    new_inimigo->tam_y = INIMIGO1_TAM_Y;
	    new_inimigo->arma = NULL;
	    new_inimigo->direcao = ESQ;
	    new_inimigo->vel = INIMIGO1_VEL;
	    break;
	case INIMIGO2:
	    new_inimigo->tipo = INIMIGO2;
	    new_inimigo->hp = INIMIGO2_HP;
	    new_inimigo->tam_x = INIMIGO2_TAM_X;
	    new_inimigo->tam_y = INIMIGO2_TAM_Y;
	    new_inimigo->arma = pistola_cria();
	    new_inimigo->direcao = CIMA;
	    new_inimigo->vel = INIMIGO2_VEL;
	    break;
	case INIMIGO3:
	    new_inimigo->tipo = INIMIGO3;
	    new_inimigo->hp = INIMIGO3_HP;
	    new_inimigo->tam_x = INIMIGO3_TAM_X;
	    new_inimigo->tam_y = INIMIGO3_TAM_Y;
	    new_inimigo->arma = NULL;
	    new_inimigo->direcao = ESQ;
	    new_inimigo->vel = INIMIGO3_VEL;
	    break;
	case INIMIGO4:
	    new_inimigo->tipo = INIMIGO4;
	    new_inimigo->hp = INIMIGO4_HP;
	    new_inimigo->tam_x = INIMIGO4_TAM_X;
	    new_inimigo->tam_y = INIMIGO4_TAM_Y;
	    new_inimigo->arma = pistola_cria();
	    new_inimigo->direcao = ESQ;
	    new_inimigo->vel = INIMIGO4_VEL;
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

void inimigo_move(inimigo *inimigo, short min_x, unsigned short max_y, unsigned char *valid)
{

    switch (inimigo->tipo) {
	case INIMIGO2:
            switch (inimigo->direcao) {
                case CIMA:
		    if ((inimigo->y - inimigo->vel) - 
				    inimigo->tam_y/2 >= 0)
		        inimigo->y -= inimigo->vel;
		    else
		        inimigo->direcao = BAIXO;
		    break;
                case BAIXO:
		    if ((inimigo->y + inimigo->vel) +
				    inimigo->tam_y/2 <= max_y)
		        inimigo->y += inimigo->vel;
		    else
		        inimigo->direcao = CIMA;
		    break;
		default:
		    break;
	    }
	    break;
        case INIMIGO3:
	        switch (inimigo->direcao) {
                case CIMA:
                    if ((inimigo->y - inimigo->vel) -
                                    inimigo->tam_y/2 >= 0)
                        inimigo->y -= inimigo->vel;
                    break;
                case BAIXO:
                    if ((inimigo->y + inimigo->vel) +
                                    inimigo->tam_y/2 <= max_y)
                        inimigo->y += inimigo->vel;
                    break;
		default:
		    break;
            }
	    break;
	default:
	    break;
    }

    if ((inimigo->x - inimigo->vel) - inimigo->tam_x/2 >= min_x)
	inimigo->x -= inimigo->vel;
    else {
        inimigo_destroi(inimigo);
	*valid = 0;
    }
	

}

void inimigo_atira(inimigo *inimigo, unsigned short x)
{
   
    if (!inimigo->arma)
	return;

    bullet *shot;
    
    if (inimigo->tipo == INIMIGO4)
        shot = pistola_atira(x, -BULLET_TAM_X, BALA_BAIXO, inimigo->arma);
    else
        shot = pistola_atira(inimigo->x - inimigo->tam_x/2, inimigo->y, 
	                     BALA_ESQ, inimigo->arma);
    if (shot)
	inimigo->arma->shots = shot;

}
