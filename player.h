#ifndef __PLAYER__
#define __PLAYER__

#include "joystick.h"
#include "pistola.h"
#include "powerup.h"

#define PLAYER_HP 3
#define PLAYER_VEL 7
#define PLAYER_TAM_X 80
#define PLAYER_TAM_Y 64
#define INVENCIBILIDADE 90

typedef struct {
    char hp;
    unsigned char colisao;
    unsigned char timer_colisao;
    unsigned char tam_x;
    unsigned char tam_y;
    unsigned short x;
    unsigned short y;
    unsigned short pontuacao;
    unsigned char frame_atual;
    unsigned short frame_time;
    enum tipoPower powerup;
    joystick *controle;
    pistola *arma;
    pistola *canhao;
} player;

player* player_cria(unsigned char tam_x, unsigned char tam_y, unsigned short x, unsigned short y);

void player_move(player *player, unsigned char direcao, unsigned short max_x, unsigned short max_y);

void player_atira(player *player);

void player_especial(player *player);

void player_destroi(player *player);

#endif
