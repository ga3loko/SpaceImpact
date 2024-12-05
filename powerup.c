#include <stdio.h>
#include <stdlib.h>

#include "powerup.h"

powerup* powerup_cria(unsigned char tipo, unsigned short x, unsigned short y)
{

    powerup *new_pu = (powerup*) malloc(sizeof(powerup));
    if (new_pu == NULL)
	return NULL;

    new_pu->tipo = tipo;
    new_pu->x = x;
    new_pu->y = y;

    return new_pu;

}

void powerup_move(powerup *powerup)
{
    powerup->x -= POWERUP_VEL;
}

void powerup_destroi(powerup *powerup)
{
    free(powerup);
}
