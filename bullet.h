#ifndef __BULLET__
#define __BULLET__

#define BULLET_VEL 10
#define BULLET_TAM_X 40
#define BULLET_TAM_Y 20

typedef struct {
    unsigned short x;
    unsigned short y;
    unsigned char trajetoria;
    struct bullet *prox;
} bullet;

bullet* bullet_cria(unsigned short x, unsigned short y, unsigned char trajetoria, bullet *prox);

void bullet_move(bullet *bullet);

void bullet_destroi(bullet *bullet);

#endif
