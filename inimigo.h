#ifndef __INIMIGO__
#define __INIMIGO__

#include "pistola.h"

#define INIMIGO1_HP 2
#define INIMIGO1_VEL 7
#define INIMIGO1_TAM_X 64
#define INIMIGO1_TAM_Y 64
#define INIMIGO2_HP 3
#define INIMIGO2_VEL 3
#define INIMIGO2_TAM_X 80
#define INIMIGO2_TAM_Y 64
#define INIMIGO3_HP 2
#define INIMIGO3_VEL 5
#define INIMIGO3_TAM_X 64
#define INIMIGO3_TAM_Y 64
#define INIMIGO4_HP 3
#define INIMIGO4_VEL 3
#define INIMIGO4_TAM_X 40
#define INIMIGO4_TAM_Y 100
enum tipoInimigo {
    INIMIGO1,
    INIMIGO2,
    INIMIGO3,
    INIMIGO4
};


typedef struct {
    enum tipoInimigo tipo;
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

inimigo* inimigo_cria(enum tipoInimigo tipo, unsigned short x, unsigned short y, unsigned short spawn);

void inimigo_destroi(inimigo *inimigo);

void inimigo_move(inimigo *inimigo, short min_x, unsigned short max_y, unsigned char *valid);

void inimigo_atira(inimigo *inimigo, unsigned short x);

#endif
