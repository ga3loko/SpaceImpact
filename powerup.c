#include <stdio.h>
#include <stdlib.h>

#include "powerup.h"

powerup* powerup_cria(enum tipoPower tipo, unsigned short x, unsigned short y, unsigned short spawn)
{

    powerup *new_pu = (powerup*) malloc(sizeof(powerup));
    if (new_pu == NULL)
	return NULL;

    new_pu->tipo = tipo;
    new_pu->x = x;
    new_pu->y = y;
    new_pu->spawn = spawn;

    return new_pu;

}

void powerup_destroi(powerup *powerup)
{
    free(powerup);
}

void powerup_move(powerup *powerup, unsigned char *valid)
{
    if (powerup->x -= POWERUP_VEL > 0)
	powerup->x -= POWERUP_VEL;
    else {
	powerup_destroi(powerup);
	*valid = 0;
    }
}
