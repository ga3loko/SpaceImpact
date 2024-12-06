#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"

bullet* bullet_cria(unsigned short x, short y, unsigned char trajetoria, bullet* prox)
{

    bullet *new_bullet = (bullet*) malloc(sizeof(bullet));
    if (new_bullet == NULL)
        return NULL;

    new_bullet->x = x;
    new_bullet->y = y;
    new_bullet->trajetoria = trajetoria;
    new_bullet->prox = (struct bullet*) prox;

    return new_bullet;

}

void bullet_move(bullet *bullet)
{
    switch (bullet->trajetoria) {
	case 0:
	    bullet->x -= BULLET_VEL;
	    break;
	case 1:
	    bullet->x += BULLET_VEL;
	    break;
	case 2:
	    bullet->y += BULLET_VEL;
	    break;
	default:
	    break;
    }

}

void bullet_destroi(bullet *bullet)
{
    free(bullet);
}
