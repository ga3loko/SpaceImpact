#ifndef __PISTOLA__
#define __PISTOLA__

#include "bullet.h"

#define PISTOLA_COOLDOWN 15
#define PISTOLA_INI_COOLDOWN 60
#define PISTOLA_BOSS_COOLDOWN 45

typedef struct {
    unsigned char timer;
    bullet *shots;
} pistola;

pistola* pistola_cria();
bullet* pistola_atira(unsigned short x, short y, unsigned char trajetoria, pistola *arma);
void pistola_destroi(pistola *pistola);

#endif
