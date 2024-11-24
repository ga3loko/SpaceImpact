#ifndef __BOSS__
#define __BOSS__

#include "pistola.h"

#define BOSS1_HP 20
#define BOSS1_TAM_X 200
#define BOSS1_TAM_Y 200
#define BOSS1_VEL 2
enum tipoBoss {
    BOSS1,
    BOSS2
};

typedef struct {
    enum tipoBoss tipo;
    unsigned char hp;
    unsigned char tam_x;
    unsigned char tam_y;
    unsigned short x;
    unsigned short y;
    unsigned short spawn;
    unsigned char direcao;
    unsigned char vel;
    pistola *arma;
} boss;

boss* boss_cria(enum tipoBoss tipo, unsigned short x, unsigned short y, unsigned short spawn);

void boss_destroi(boss *boss);

void boss_move(boss* boss, unsigned char passo, unsigned short max_x, unsigned short max_y, unsigned short min_y); 

void boss_atira(boss *boss);

#endif