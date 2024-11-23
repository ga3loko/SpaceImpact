#ifndef __INIMIGO__
#define __INIMIGO__

#include "pistola.h"

#define INIMIGO1_VEL 5
#define INIMIGO1_TAM_X 40
#define INIMIGO1_TAM_Y 40
#define INIMIGO2_VEL 3
#define INIMIGO2_TAM_X 80
#define INIMIGO2_TAM_Y 40

typedef struct {
    unsigned char tipo;
    unsigned char hp;
    unsigned char tam_x;
    unsigned char tam_y;
    unsigned short x;
    unsigned short y;
    unsigned short spawn;
    unsigned char direcao;
    unsigned char vel;
    pistola *arma;
} inimigo;

inimigo* inimigo_cria(unsigned char tipo, unsigned short x, unsigned short y, unsigned short spawn);

void inimigo_destroi(inimigo *inimigo);

void inimigo_move(inimigo *inimigo, unsigned char passo, short min_x, unsigned short max_y, unsigned char *valid);

void inimigo_atira(inimigo *inimigo);

#endif
