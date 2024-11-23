#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"

bullet* bullet_cria(unsigned short x, unsigned short y, unsigned char trajetoria, bullet* prox)
{

    if (trajetoria > 1) 
	return NULL;

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

     if (!bullet->trajetoria) 
	bullet->x -= BULLET_VEL;
     else 
	bullet->x += BULLET_VEL;

}

void bullet_destroi(bullet *bullet)
{
    free(bullet);
}
