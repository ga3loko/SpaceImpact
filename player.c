#include <stdio.h>
#include <stdlib.h>

#include "player.h"

player* player_cria(unsigned char tam_x, unsigned char tam_y, unsigned short x, unsigned short y)
{

    player *new_player = (player*) malloc(sizeof(player));
    new_player->hp = PLAYER_HP;
    new_player->colisao = 0;
    new_player->timer_colisao = INVENCIBILIDADE;
    new_player->tam_x = tam_x;
    new_player->tam_y = tam_y;
    new_player->x = x;
    new_player->y = y;
    new_player->pontuacao = 0;
    new_player->powerup = NO_PU;
    new_player->controle = joystick_cria();
    new_player->arma = pistola_cria();
    
    return new_player;

}

void player_move(player *player, unsigned char passo, unsigned char direcao, unsigned short max_x, unsigned short max_y)
{

    switch (direcao) {
        case 0:
	    if ((player->x - passo*PLAYER_VEL) - player->tam_x/2 >= 0)
	        player->x -= passo*PLAYER_VEL;
	    break;
	case 1:
	    if ((player->x + passo*PLAYER_VEL) + player->tam_x/2 <= max_x)
                player->x += passo*PLAYER_VEL;
            break;
	case 2:
            if ((player->y - passo*PLAYER_VEL) - player->tam_y/2 >= 0)
                player->y -= passo*PLAYER_VEL;
            break;
        case 3:
            if ((player->y + passo*PLAYER_VEL) + player->tam_y/2 <= max_y)
                player->y += passo*PLAYER_VEL;
            break;
	default:
	    break;
    }

}

void player_atira(player *player)
{
    bullet *shot;

    shot = pistola_atira(player->x + player->tam_x/2, player->y, 1, 
		         player->arma);
    if (shot)
	player->arma->shots = shot;
}

void player_destroi(player *player)
{
    pistola_destroi(player->arma);
    joystick_destroi(player->controle);
    free(player);
}

