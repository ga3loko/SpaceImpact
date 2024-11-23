#include <stdio.h>
#include <stdlib.h>

#include "pistola.h"

pistola* pistola_cria()
{

    pistola *new_pistola = (pistola*) malloc(sizeof(pistola));
    if (new_pistola == NULL)
	return NULL;
    new_pistola->timer = 0;
    new_pistola->shots = NULL;

    return new_pistola;

}

bullet* pistola_atira(unsigned short x, unsigned short y, unsigned char trajetoria, pistola* arma)
{

    bullet *new_bullet = bullet_cria(x, y, trajetoria, arma->shots);
    if (new_bullet == NULL)
	return NULL;
    return new_bullet;

}

void pistola_destroi(pistola *pistola)
{
 
    if (pistola == NULL)
        return;
    
    bullet *sentinela;
    for (bullet *index = pistola->shots; index != NULL; index = sentinela) {
        sentinela = (bullet*) index->prox;
	bullet_destroi(index);
    }
    free(pistola);

}
