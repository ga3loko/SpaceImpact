#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "defines.h"

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
    new_player->canhao = pistola_cria();
    new_player->frame_atual = 0;
    new_player->frame_time = 0;

    return new_player;

}

void player_move(player *player, unsigned char direcao, unsigned short max_x, unsigned short max_y)
{

    switch (direcao) {
        case ESQ:
	    if ((player->x - PLAYER_VEL) - player->tam_x/2 >= 0)
	        player->x -= PLAYER_VEL;
	    break;
	case DIRE:
	    if ((player->x + PLAYER_VEL) + player->tam_x/2 <= max_x)
                player->x += PLAYER_VEL;
            break;
	case CIMA:
            if ((player->y - PLAYER_VEL) - player->tam_y/2 >= 0)
                player->y -= PLAYER_VEL;
            break;
        case BAIXO:
            if ((player->y + PLAYER_VEL) + player->tam_y/2 <= max_y)
                player->y += PLAYER_VEL;
            break;
	default:
	    break;
    }

}

void player_atira(player *player)
{
    bullet *shot;

    shot = pistola_atira(player->x + player->tam_x/2, player->y, BALA_DIR, 
		         player->arma);
    if (shot)
	player->arma->shots = shot;
}

void player_especial(player *player)
{

    bullet *shot;
    
    switch (player->powerup) {
	case PU1:
            shot = pistola_atira(player->x + player->tam_x/2, player->y, 3,
			    player->canhao);
	    break;
	case PU2:
	    shot = pistola_atira(player->x + player->tam_x/2, player->y, 1,
			    player->canhao);
	    break;
	default:
	    break;
    }

    if (shot)
	player->canhao->shots = shot;

}

void player_destroi(player *player)
{
    pistola_destroi(player->arma);
    pistola_destroi(player->canhao);
    joystick_destroi(player->controle);
    free(player);
}

