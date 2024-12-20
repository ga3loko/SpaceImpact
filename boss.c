#include <stdio.h>
#include <stdlib.h>

#include "boss.h"
#include "defines.h"

boss* boss_cria(enum tipoBoss tipo, unsigned short x, unsigned short y, unsigned short spawn)
{

    boss *new_boss = (boss*) malloc(sizeof(boss));
    new_boss->x = x;
    new_boss->y = y;
    new_boss->spawn = spawn;
    new_boss->arma = pistola_cria();
    new_boss->trooper = NULL;
    new_boss->valid = 1;

    switch (tipo) {
        case BOSS1:
	    new_boss->tipo = BOSS1;
	    new_boss->hp = BOSS1_HP;
	    new_boss->tam_x = BOSS1_TAM_X;
	    new_boss->tam_y = BOSS1_TAM_Y;
	    new_boss->canhao = pistola_cria();
	    new_boss->direcao = ESQ;
	    new_boss->vel = BOSS1_VEL;
	    break;
	case BOSS2:
            new_boss->tipo = BOSS2;
            new_boss->hp = BOSS2_HP;
            new_boss->tam_x = BOSS2_TAM_X;
            new_boss->tam_y = BOSS2_TAM_Y;
	    new_boss->canhao = NULL;
            new_boss->direcao = ESQ;
            new_boss->vel = BOSS2_VEL;
            break;
	default:
	    break;
    }

    return new_boss;

}

void boss_destroi(boss *boss)
{
    pistola_destroi(boss->canhao);
    pistola_destroi(boss->arma);
    if (boss->trooper)
	inimigo_destroi(boss->trooper);
    free(boss);
}

void boss_move(boss *boss, unsigned short max_x, unsigned short max_y, unsigned short min_y)
{

    switch (boss->direcao) {
        case ESQ:
	    if ((boss->x - boss->vel) - boss->tam_x/2 >= max_x)
		boss->x -= boss->vel;
	    else
		boss->direcao = CIMA;
	    break;
	case CIMA:
	    if ((boss->y - boss->vel) - boss->tam_y/2 >= min_y)
		boss->y -= boss->vel;
	    else
		boss->direcao = BAIXO;
	    break;
	case BAIXO:
	    if ((boss->y + boss->vel) + boss->tam_y/2 <= max_y)
		boss->y += boss->vel;
	    else
		boss->direcao = CIMA;
	    break;
	default:
            break;
    }

}

void boss_atira(boss *boss)
{

    bullet *shot1;
    bullet *shot2;
    bullet *shot3;

    switch (boss->tipo) {
	case BOSS1:

            shot1 = pistola_atira(boss->x - boss->tam_x/2, 
			    boss->y + 20, BALA_ESQ, boss->arma);
            if (shot1)
	        boss->arma->shots = shot1;

            shot2 = pistola_atira(boss->x - boss->tam_x/2, 
			    boss->y - 20, BALA_ESQ, boss->arma);
            if (shot2)
	        boss->arma->shots = shot2;
	    break;
	case BOSS2:

            shot1 = pistola_atira(boss->x - boss->tam_x/2,
                            boss->y + boss->tam_y/2 - 30, BALA_ESQ, boss->arma);
            if (shot1)
                boss->arma->shots = shot1;

            shot2 = pistola_atira(boss->x - boss->tam_x/2,
                            boss->y - boss->tam_y/2 + 30, BALA_ESQ, boss->arma);
            if (shot2)
                boss->arma->shots = shot2;

	    shot3 = pistola_atira(boss->x - boss->tam_x/2, 
			    boss->y, BALA_ESQ, boss->arma);
	    if (shot3)
		boss->arma->shots = shot3;
            break;
	default:
	    break;
    }

}

void boss_especial(boss *boss, unsigned short y)
{
    bullet *shot;
            
    shot = pistola_atira(boss->x - boss->tam_x/2, y, BALA_ESQ, boss->canhao);

    if (shot)
	boss->canhao->shots = shot;
}
