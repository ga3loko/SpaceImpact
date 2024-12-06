#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "player.h"
#include "inimigo.h"
#include "boss.h"
#include "botao.h"
#include "powerup.h"

#define X_TELA 1080
#define Y_TELA 720
#define FPS 30
#define SPAWN1_1 2
#define SPAWN2_1 4
#define SPAWN3_1 7
#define SPAWN4_1 8
#define SPAWN5_1 15
#define SPAWN6_1 15
#define SPAWN7_1 15
#define SPAWN8_1 20
#define SPAWN9_1 32
#define SPAWN10_1 32
#define SPAWN11_1 32
#define SPAWN12_1 32
#define SPAWN13_1 32
#define SPAWN14_1 32
#define SPAWN15_1 35
#define SPAWN1_2 3
#define SPAWN2_2 3
#define SPAWN3_2 8
#define SPAWN4_2 8
#define SPAWN5_2 10
#define SPAWN6_2 10
#define SPAWN7_2 12
#define SPAWN8_2 15
#define SPAWN9_2 15
#define SPAWN10_2 15
#define SPAWN11_2 21
#define SPAWN12_2 21
#define SPAWN13_2 23
#define SPAWN14_2 25
#define SPAWN15_2 30
#define SPAWN16_2 30
#define SPAWN17_2 30
#define SPAWN18_2 30
#define SPAWN19_2 40
#define SPAWN20_2 40
#define SPAWN21_2 40
#define SPAWN22_2 40
#define SPAWN23_2 40
#define SPAWN24_2 45
#define SPAWN25_2 47
#define SPAWNBOSS1 47
#define SPAWNBOSS2 57
#define SPAWNPU1_1 12
#define SPAWNPU2_1 27
#define SPAWNPU1_2 17
#define SPAWNPU2_2 35
#define PU_NUM 2
#define GANHOU 2
#define PERDEU 1
#define INIMIGOS_FASE1 15
#define INIMIGOS_FASE2 25

void movimenta_bullets_player(player *player){
    bullet *anterior = NULL;
    for (bullet *index = player->arma->shots; index != NULL;){
	bullet_move(index);
	if (index->x > X_TELA){
	    if (anterior){
		anterior->prox = index->prox;
		bullet_destroi(index);
		index = (bullet*) anterior->prox;
	    }
	    else {
	        player->arma->shots = (bullet*) index->prox;
	        bullet_destroi(index);
	        index = player->arma->shots;
	    }
	}
	else {
	    anterior = index;
	    index = (bullet*) index->prox;
	}
    }

    if (player->powerup == PU1) {
        bullet *index = player->canhao->shots;
	if (index) {
            index->y = player->y;
	    index->x = player->x + player->tam_x/2;
	}
    }
}

void movimenta_bullets_inimigo(inimigo *inimigo){
    bullet *anterior = NULL;
    for (bullet *index = inimigo->arma->shots; index != NULL;){
        bullet_move(index);
        if (index->x <= 0 || index->y >= Y_TELA){
            if (anterior){
                anterior->prox = index->prox;
                bullet_destroi(index);
                index = (bullet*) anterior->prox;
            }
            else {
                inimigo->arma->shots = (bullet*) index->prox;
                bullet_destroi(index);
                index = inimigo->arma->shots;
            }
        }
        else {
            anterior = index;
            index = (bullet*) index->prox;
        }
    }
}

void movimenta_bullets_boss(boss *boss){
    
    bullet *anterior = NULL;
    for (bullet *index = boss->arma->shots; index != NULL;){
        bullet_move(index);
        if (index->x <= 0){
            if (anterior){
                anterior->prox = index->prox;
                bullet_destroi(index);
                index = (bullet*) anterior->prox;
            }
            else {
                boss->arma->shots = (bullet*) index->prox;
                bullet_destroi(index);
                index = boss->arma->shots;
            }
        }
        else {
            anterior = index;
            index = (bullet*) index->prox;
        }
    }

}

void movimenta_canhao_boss(boss* boss) {

    bullet *anterior = NULL;
    if (boss->tipo == BOSS1) {
        for (bullet *index = boss->canhao->shots; index != NULL;) {
            bullet_move(index);
            if (index->x <= 0){
                if (anterior){
                    anterior->prox = index->prox;
                    bullet_destroi(index);
                    index = (bullet*) anterior->prox;
                }
                else {
                    boss->canhao->shots = (bullet*) index->prox;
                    bullet_destroi(index);
                    index = boss->canhao->shots;
                }
            }
            else {
                anterior = index;
                index = (bullet*) index->prox;
            }
        }
    }
}


unsigned char colidiu_ini(player* player, inimigo *inimigo)
{
    if ((((player->y - player->tam_y/2 >= inimigo->y - inimigo->tam_y/2) && 
	 (inimigo->y + inimigo->tam_y/2 >= player->y - player->tam_y/2)) ||
         ((inimigo->y - inimigo->tam_y/2 >= player->y - player->tam_y/2) && 
	(player->y + player->tam_y/2 >= inimigo->y - inimigo->tam_y/2))) &&
        (((player->x - player->tam_y/2 >= inimigo->x - inimigo->tam_x/2) && 
	 (inimigo->x + inimigo->tam_x/2 >= player->x - player->tam_x/2)) ||
         ((inimigo->x - inimigo->tam_x/2 >= player->x - player->tam_x/2) && 
	  (player->x + player->tam_x/2 >= inimigo->x - inimigo->tam_x/2)))) 
	return 1;
    return 0;
}

unsigned char colidiu_powerup(powerup* powerup, player *player)
{
    if ((((player->y - player->tam_y/2 >= powerup->y - POWERUP_R) &&
         (powerup->y + POWERUP_R >= player->y - player->tam_y/2)) ||
         ((powerup->y - POWERUP_R >= player->y - player->tam_y/2) &&
        (player->y + player->tam_y/2 >= powerup->y - POWERUP_R))) &&
        (((player->x - player->tam_y/2 >= powerup->x - POWERUP_R) &&
         (powerup->x + POWERUP_R >= player->x - player->tam_x/2)) ||
         ((powerup->x - POWERUP_R >= player->x - player->tam_x/2) &&
          (player->x + player->tam_x/2 >= powerup->x - POWERUP_R))))
        return 1;
    return 0;
}

unsigned char colidiu_boss(player* player, boss *boss)
{
    if ((((player->y - player->tam_y/2 >= boss->y - boss->tam_y/2) &&
         (boss->y + boss->tam_y/2 >= player->y - player->tam_y/2)) ||
         ((boss->y - boss->tam_y/2 >= player->y - player->tam_y/2) &&
        (player->y + player->tam_y/2 >= boss->y - boss->tam_y/2))) &&
        (((player->x - player->tam_y/2 >= boss->x - boss->tam_x/2) &&
         (boss->x + boss->tam_x/2 >= player->x - player->tam_x/2)) ||
         ((boss->x - boss->tam_x/2 >= player->x - player->tam_x/2) &&
          (player->x + player->tam_x/2 >= boss->x - boss->tam_x/2))))
        return 1;
    return 0;
}


void movimenta_player(player *player)
{

    if (player->controle->esq)
        player_move(player, 1, 0, X_TELA, Y_TELA);
    if (player->controle->dir)
	player_move(player, 1, 1, X_TELA, Y_TELA);
    if (player->controle->cima)
	player_move(player, 1, 2, X_TELA, Y_TELA);
    if (player->controle->baixo)
	player_move(player, 1, 3, X_TELA, Y_TELA);
    if (player->controle->atira) {
        if (!player->arma->timer) {
            player_atira(player);
	    player->arma->timer = PISTOLA_COOLDOWN;
	}
    }

    if (player->arma->timer > 0)
	player->arma->timer--;

    if (player->controle->especial) {
        switch (player->powerup) {
            case NO_PU:
		break;
	    case PU1:
                if (!player->canhao->shots) {
	            player_especial(player);
		    player->canhao->timer = CANHAO_COOLDOWN;
	        }
		break;
	    case PU2:
		break;
	    default:
		break;
	}

    }

    switch (player->powerup) {
        case NO_PU:
	    break;
	case PU1:
	    if (player->canhao->shots && !player->canhao->timer) {
                bullet_destroi(player->canhao->shots);
		player->canhao->shots = NULL;
		player->powerup = NO_PU;
	    }
	    break;
	case PU2:
	    break;
	default:
	    break;
    }

    if (player->canhao->timer > 0)
	player->canhao->timer--;

    movimenta_bullets_player(player);
}

unsigned char matou_boss(player *player, boss *boss)
{

    bullet *anterior = NULL;
    for (bullet *index = player->arma->shots; index != NULL;
                            index = (bullet*) index->prox) {
        if ((((index->y - BULLET_TAM_Y/2 >= boss->y - boss->tam_y/2) &&
             (boss->y + boss->tam_y/2 >= index->y - BULLET_TAM_Y/2)) ||
             ((boss->y - boss->tam_y/2 >= index->y - BULLET_TAM_Y/2) &&
            (index->y + BULLET_TAM_Y/2 >= boss->y - boss->tam_y/2))) &&
            (((index->x - BULLET_TAM_X/2 >= boss->x - boss->tam_x/2) &&
             (boss->x + boss->tam_x/2 >= index->x - BULLET_TAM_X/2)) ||
             ((boss->x - boss->tam_x/2 >= index->x - BULLET_TAM_X/2) &&
             (index->x + BULLET_TAM_X/2 >= boss->x - boss->tam_x/2)))) {

            boss->hp--;

            if (anterior) {
                anterior->prox = index->prox;
                bullet_destroi(index);
                index = (bullet*) anterior->prox;
            }
            else {
                player->arma->shots = (bullet*) index->prox;
                bullet_destroi(index);
                index = player->arma->shots;
            }
            if (!boss->hp)
                return 1;
            return 0;
        }
        anterior = index;
    }
    
    switch (player->powerup) {
        case PU1:
	    anterior = player->canhao->shots;
	    if (anterior) {
                if ((((anterior->y - CANHAO_PU1_TAM_Y/2 >= boss->y - boss->tam_y/2) &&
                     (boss->y + boss->tam_y/2 >= anterior->y - CANHAO_PU1_TAM_Y/2)) ||
                     ((boss->y - boss->tam_y/2 >= anterior->y - CANHAO_PU1_TAM_Y/2) &&
                    (anterior->y + CANHAO_PU1_TAM_Y/2 >= boss->y - boss->tam_y/2))) &&
                                         (((anterior->x >= boss->x - boss->tam_x/2) &&
                                          (boss->x + boss->tam_x/2 >= anterior->x)) ||
                                          ((boss->x - boss->tam_x/2 >= anterior->x) &&
                                              (X_TELA >= boss->x - boss->tam_x/2)))) {
                    
		    if (boss->hp >= 3)
		        boss->hp -= 3;
		    else
			boss->hp = 0;
		    if (player->canhao->timer >= 25)
			player->canhao->timer -= 25;
		    else
			player->canhao->timer = 0;

	        }
	    }
	    break;
        case PU2:
	    break;
	default:
	    break;
    }

    if (!boss->hp)
	return 1;
    return 0;
}

unsigned char matou_player_boss(player *player, boss *boss)
{
    if (colidiu_boss(player, boss)) {
        player->hp--;
        if (!player->hp)
            return 1;
        player->colisao = 1;
        return 0;
    }

    bullet *anterior = NULL;
    for (bullet *index = boss->arma->shots; index != NULL;
                            index = (bullet*) index->prox) {
        if ((((index->y - BULLET_TAM_Y/2 >= player->y - player->tam_y/2) &&
             (player->y + player->tam_y/2 >= index->y - BULLET_TAM_Y/2)) ||
             ((player->y - player->tam_y/2 >= index->y - BULLET_TAM_Y/2) &&
            (index->y + BULLET_TAM_Y/2 >= player->y - player->tam_y/2))) &&
            (((index->x - BULLET_TAM_X/2 >= player->x - player->tam_x/2) &&
             (player->x + player->tam_x/2 >= index->x - BULLET_TAM_X/2)) ||
             ((player->x - player->tam_x/2 >= index->x - BULLET_TAM_X/2) &&
             (index->x + BULLET_TAM_X/2 >= player->x - player->tam_x/2)))) {

            player->hp--;

            if (anterior) {
                anterior->prox = index->prox;
                bullet_destroi(index);
                index = (bullet*) anterior->prox;
            }
            else {
                boss->arma->shots = (bullet*) index->prox;
                bullet_destroi(index);
                index = boss->arma->shots;
            }

            if (!player->hp)
                return 1;
            return 0;
        }
        anterior = index;
    }

    anterior = NULL;
    if (boss->tipo == BOSS1) {
        for (bullet *index = boss->canhao->shots; index != NULL;
                            index = (bullet*) index->prox) {
            if ((((index->y - CANHAO_TAM_Y/2 >= player->y - player->tam_y/2) &&
                 (player->y + player->tam_y/2 >= index->y - CANHAO_TAM_Y/2)) ||
                 ((player->y - player->tam_y/2 >= index->y - CANHAO_TAM_Y/2) &&
                (index->y + CANHAO_TAM_Y/2 >= player->y - player->tam_y/2))) &&
                (((index->x - CANHAO_TAM_X/2 >= player->x - player->tam_x/2) &&
                 (player->x + player->tam_x/2 >= index->x - CANHAO_TAM_X/2)) ||
                 ((player->x - player->tam_x/2 >= index->x - CANHAO_TAM_X/2) &&
                (index->x + CANHAO_TAM_X/2 >= player->x - player->tam_x/2)))) {

                player->hp -= 2;

                if (anterior) {
                    anterior->prox = index->prox;
                    bullet_destroi(index);
                    index = (bullet*) anterior->prox;
                }
                else {
                    boss->canhao->shots = (bullet*) index->prox;
                    bullet_destroi(index);
                    index = boss->canhao->shots;
                }

                if (player->hp <= 0)
                    return 1;
                return 0;
            }
            anterior = index;
        }
    }

    return 0;

}

unsigned char matou_inimigo(player *player, inimigo *inimigo)
{

    bullet *anterior = NULL;
    for (bullet *index = player->arma->shots; index != NULL;
        index = (bullet*) index->prox) {
           if ((((index->y - BULLET_TAM_Y/2 >= inimigo->y - inimigo->tam_y/2) &&
                (inimigo->y + inimigo->tam_y/2 >= index->y - BULLET_TAM_Y/2)) ||
		((inimigo->y - inimigo->tam_y/2 >= index->y - BULLET_TAM_Y/2) &&
	       (index->y + BULLET_TAM_Y/2 >= inimigo->y - inimigo->tam_y/2))) &&
	       (((index->x - BULLET_TAM_X/2 >= inimigo->x - inimigo->tam_x/2) &&
		(inimigo->x + inimigo->tam_x/2 >= index->x - BULLET_TAM_X/2)) ||
		((inimigo->x - inimigo->tam_x/2 >= index->x - BULLET_TAM_X/2) &&
	      (index->x + BULLET_TAM_X/2 >= inimigo->x - inimigo->tam_x/2)))) {

		inimigo->hp--;

                if (anterior) {
	            anterior->prox = index->prox;
                    bullet_destroi(index);
		    index = (bullet*) anterior->prox;
		}
                else {
		    player->arma->shots = (bullet*) index->prox;
		    bullet_destroi(index);
		    index = player->arma->shots;
		}
		if (!inimigo->hp)
		    return 1;
		return 0;
	    }
            anterior = index;
	}

    switch (player->powerup) {
        case PU1:
            anterior = player->canhao->shots;
            if (anterior) {
                if ((((anterior->y - CANHAO_PU1_TAM_Y/2 >= inimigo->y - inimigo->tam_y/2) &&
                     (inimigo->y + inimigo->tam_y/2 >= anterior->y - CANHAO_PU1_TAM_Y/2)) ||
                     ((inimigo->y - inimigo->tam_y/2 >= anterior->y - CANHAO_PU1_TAM_Y/2) &&
                    (anterior->y + CANHAO_PU1_TAM_Y/2 >= inimigo->y - inimigo->tam_y/2))) &&
                                         (((anterior->x >= inimigo->x - inimigo->tam_x/2) &&
                                          (inimigo->x + inimigo->tam_x/2 >= anterior->x)) ||
                                          ((inimigo->x - inimigo->tam_x/2 >= anterior->x) &&
                                              (X_TELA >= inimigo->x - inimigo->tam_x/2)))) {

                    inimigo->hp = 0;
                }
            }
            break;
        case PU2:
            break;
        default:
            break;
    }

    if (!inimigo->hp)
	 return 1;
    return 0;
}


unsigned char matou_player_ini(player *player, inimigo *inimigo)
{

    if (colidiu_ini(player, inimigo)) {
	player->hp--;
	if (!player->hp)
	    return 1;
	player->colisao = 1;
	return 0;
    }
    
    if (!inimigo->arma)
	return 0;

    bullet *anterior = NULL;
    for (bullet *index = inimigo->arma->shots; index != NULL;
	index = (bullet*) index->prox) {
        if ((((index->y - BULLET_TAM_Y/2 >= player->y - player->tam_y/2) &&
	     (player->y + player->tam_y/2 >= index->y - BULLET_TAM_Y/2)) ||
	     ((player->y - player->tam_y/2 >= index->y - BULLET_TAM_Y/2) &&
	    (index->y + BULLET_TAM_Y/2 >= player->y - player->tam_y/2))) &&
	    (((index->x - BULLET_TAM_X/2 >= player->x - player->tam_x/2) &&
             (player->x + player->tam_x/2 >= index->x - BULLET_TAM_X/2)) ||
	     ((player->x - player->tam_x/2 >= index->x - BULLET_TAM_X/2) &&
            (index->x + BULLET_TAM_X/2 >= player->x - player->tam_x/2)))) {

		player->hp--;

                if (anterior) {			
		    anterior->prox = index->prox;
		    bullet_destroi(index);
		    index = (bullet*) anterior->prox;
		}
		else {
		    inimigo->arma->shots = (bullet*) index->prox;
		    bullet_destroi(index);
		    index = inimigo->arma->shots;
		}
		
		if (!player->hp)
			return 1;
		return 0;
	}
	anterior = index;
    }
    return 0;
}


unsigned char atualiza_boss(boss *boss, player *player, unsigned short time)
{
    boss_move(boss, 1, X_TELA - boss->tam_x/2 - 150, Y_TELA - boss->tam_y/2,
		boss->tam_y/2);
    if (!boss->arma->timer) {
        boss_atira(boss);
        boss->arma->timer = PISTOLA_BOSS_COOLDOWN;
    }
    else
        boss->arma->timer--;

    if (boss->hp <= 10) {
        if (boss->tipo == BOSS1) {
	    if (!boss->canhao->timer) {
	        boss_especial(boss, player->y);
	        boss->canhao->timer = CANHAO_COOLDOWN;
	    }   
	    else
                boss->canhao->timer--;

	    movimenta_canhao_boss(boss);
        }
	else {
	    if (!boss->trooper) {
		boss->trooper = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X, 
			                  player->y, time);
		boss->valid = 1;
	    }
	    else {
                if (boss->valid) {
		    if (player->y > boss->trooper->y + boss->trooper->tam_y/2)
                        boss->trooper->direcao = 2;
                    else if (player->y < boss->trooper->y - 
				    boss->trooper->tam_y/2)
                        boss->trooper->direcao = 1;
                    else
                        boss->trooper->direcao = 0;

		    inimigo_move(boss->trooper, 1, -boss->trooper->tam_x/2,
				    Y_TELA, &(boss->valid));
		    if (boss->valid) {
                        if (matou_inimigo(player, boss->trooper)) {
			    inimigo_destroi(boss->trooper);
			    boss->trooper = NULL;
			    boss->valid = 0;
			}
			if (boss->valid && !player->colisao && 
					matou_player_ini(player, boss->trooper))
			    return 1;
		    }
		}
	    }
	}
    }

    movimenta_bullets_boss(boss);

    if (matou_boss(player, boss)) {
	player->pontuacao += 100;
	return GANHOU;
    }

    if (!player->colisao && matou_player_boss(player, boss))
	return PERDEU;
    
    return 0;
}

unsigned char inicializa_powerups(powerup **powerups, unsigned char fase)
{

    switch (fase) {
        case 1:
            powerups[0] = powerup_cria(PU1, X_TELA + POWERUP_R*2,
                            Y_TELA/2, SPAWNPU1_1);
            powerups[1] = powerup_cria(PU1, X_TELA + POWERUP_R*2,
                            Y_TELA/2, SPAWNPU2_1);
	    break;
	case 2:
	    powerups[0] = powerup_cria(PU2, X_TELA + POWERUP_R*2,
                            Y_TELA/2, SPAWNPU1_2);
            powerups[1] = powerup_cria(PU2, X_TELA + POWERUP_R*2,
                            Y_TELA/2, SPAWNPU2_2);
    }

    for (size_t i = 0; i < PU_NUM; i++) {
        if (!powerups[i])
	    return 0;
    }

    return 1;

}

unsigned char inicializa_ini_fase1(inimigo **inimigos, size_t ini_num)
{
    inimigos[0] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, Y_TELA/2, 
		    SPAWN1_1);
    inimigos[1] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, Y_TELA/2, 
		    SPAWN2_1);
    inimigos[2] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, Y_TELA/2, 
		    SPAWN3_1);
    inimigos[3] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, 
		    Y_TELA - INIMIGO2_TAM_Y/2, SPAWN4_1);
    inimigos[4] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2 + INIMIGO1_TAM_Y, SPAWN5_1);
    inimigos[5] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2 - INIMIGO1_TAM_Y, SPAWN6_1);
    inimigos[6] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, 
		    Y_TELA - INIMIGO2_TAM_Y, SPAWN7_1);
    inimigos[7] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2, SPAWN8_1);
    inimigos[8] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2, SPAWN9_1);
    inimigos[9] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, 
		    Y_TELA - INIMIGO2_TAM_Y, SPAWN10_1);
    inimigos[10] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2 - INIMIGO1_TAM_Y - 20, SPAWN11_1);
    inimigos[11] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2, SPAWN12_1);
    inimigos[12] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    Y_TELA/2 + INIMIGO1_TAM_Y + 20, SPAWN13_1);
    inimigos[13] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, 
		    INIMIGO2_TAM_Y, SPAWN14_1);
    inimigos[14] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, 
		    INIMIGO1_TAM_X + 100, SPAWN15_1);

    for (size_t i = 0; i < ini_num; i++) {
        if (!inimigos[i])
	    return 0;
    }

    return 1;
}

unsigned char inicializa_ini_fase2(inimigo **inimigos, size_t ini_num)
{
    inimigos[0] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X, 
		    Y_TELA/2, SPAWN1_2);
    inimigos[1] = inimigo_cria(INIMIGO4, X_TELA + INIMIGO4_TAM_X, 
		    Y_TELA - INIMIGO4_TAM_Y/2, SPAWN2_2);
    inimigos[2] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X, 
		    Y_TELA - INIMIGO3_TAM_Y, SPAWN3_2);
    inimigos[3] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X,
                    Y_TELA + INIMIGO3_TAM_Y/2, SPAWN4_2);
    inimigos[4] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2 + INIMIGO1_TAM_Y, SPAWN5_2);
    inimigos[5] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2 - INIMIGO1_TAM_Y, SPAWN6_2);
    inimigos[6] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X,
                    Y_TELA - INIMIGO3_TAM_Y, SPAWN7_2);
    inimigos[7] = inimigo_cria(INIMIGO4, X_TELA + INIMIGO4_TAM_X,
                    Y_TELA - INIMIGO4_TAM_Y/2, SPAWN8_2);
    inimigos[8] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2, SPAWN9_2);
    inimigos[9] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X,
                    Y_TELA - INIMIGO2_TAM_Y, SPAWN10_2);
    inimigos[10] = inimigo_cria(INIMIGO4, X_TELA + INIMIGO4_TAM_X,
                    Y_TELA - INIMIGO4_TAM_Y/2, SPAWN11_2);
    inimigos[11] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X,
                    Y_TELA/2, SPAWN12_2);
    inimigos[12] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2, SPAWN13_2);
    inimigos[13] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X,
                    INIMIGO2_TAM_Y, SPAWN14_2);
    inimigos[14] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2, SPAWN15_2);
    inimigos[15] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2 - INIMIGO1_TAM_Y - 50, SPAWN16_2);
    inimigos[16] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2 + INIMIGO1_TAM_Y + 50, SPAWN17_2);
    inimigos[17] = inimigo_cria(INIMIGO4, X_TELA + INIMIGO4_TAM_X,
                    Y_TELA - INIMIGO4_TAM_Y/2, SPAWN18_2);
    inimigos[18] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2, SPAWN19_2);
    inimigos[19] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X,
                    Y_TELA - INIMIGO2_TAM_Y, SPAWN20_2);
    inimigos[20] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X,
                    INIMIGO2_TAM_Y, SPAWN21_2);
    inimigos[21] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2, SPAWN22_2);
    inimigos[22] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X,
                    Y_TELA/2 + INIMIGO3_TAM_Y + 20, SPAWN23_2);
    inimigos[23] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X,
                    Y_TELA/2 - INIMIGO3_TAM_Y - 20, SPAWN24_2);
    inimigos[24] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X,
                    Y_TELA/2, SPAWN25_2);


    for (size_t i = 0; i < ini_num; i++) {
        if (!inimigos[i])
            return 0;
    }

    return 1;
}

unsigned char atualiza_inimigos(inimigo **inimigos, size_t ini_num, unsigned char *valid, unsigned short time, player *player)
{
    
    for (size_t i = 0; i < ini_num; i++) {
        if (valid[i] && time >= inimigos[i]->spawn * FPS) {
            
            if (inimigos[i]->tipo == INIMIGO3) {
                if (player->y > inimigos[i]->y + inimigos[i]->tam_y/2)
		    inimigos[i]->direcao = 2;
		else if (player->y < inimigos[i]->y - inimigos[i]->tam_y/2)
		    inimigos[i]->direcao = 1;
		else 
		    inimigos[i]->direcao = 0;
	    }
	    inimigo_move(inimigos[i], 1, -inimigos[i]->tam_x/2, Y_TELA, 
			 &valid[i]);

	    if (valid[i]) {
	        if (inimigos[i]->arma) {
		    if (!inimigos[i]->arma->timer) {
                        inimigo_atira(inimigos[i], player->x);
			inimigos[i]->arma->timer = PISTOLA_INI_COOLDOWN;
		    }
		    else
		        inimigos[i]->arma->timer--;
		    movimenta_bullets_inimigo(inimigos[i]);
		}

	        if (matou_inimigo(player, inimigos[i])) {
                    player->pontuacao += 10;
		    inimigo_destroi(inimigos[i]);
		    valid[i] = 0;
		}
                
                if (valid[i] && !player->colisao && 
				matou_player_ini(player, inimigos[i]))
		    return PERDEU;
	    }
	}
    }

    return 0;
}

void atualiza_powerup(powerup **powerups, player *player, unsigned short time, unsigned char *valid)
{

    for (size_t i = 0; i < PU_NUM; i++) {
        if (valid[i] && time >= FPS * powerups[i]->spawn)
            powerup_move(powerups[i], &valid[i]);
 
	if(valid[i] && colidiu_powerup(powerups[i], player)) {
            player->powerup = powerups[i]->tipo;
	    powerup_destroi(powerups[i]);
	    valid[i] = 0;
        }
    }

}

void atualiza_jogo(player *player, inimigo **inimigos, boss *boss, powerup **powerups, unsigned char *valid, unsigned char *valid_pu, unsigned short time, unsigned char *gameover, size_t ini_num, unsigned char fase)
{
    movimenta_player(player);
    unsigned short boss_fight;

    if (fase == 1)
        boss_fight = SPAWNBOSS1;
    else
	boss_fight = SPAWNBOSS2;

    if (time <= FPS * boss_fight)
        *gameover = atualiza_inimigos
                             (inimigos, ini_num, valid, time, player);
    else
        *gameover = atualiza_boss(boss, player, time);

    atualiza_powerup(powerups, player, time, valid_pu);

    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    if (!player->colisao)
        al_draw_filled_rectangle(player->x - player->tam_x/2,
                                 player->y - player->tam_y/2,
                                 player->x + player->tam_x/2,
                                 player->y + player->tam_y/2,
                                 al_map_rgb(0, 0, 255));

    else {
        if ((player->timer_colisao % 15) <= 7)
            al_draw_filled_rectangle(player->x - player->tam_x/2,
                                     player->y - player->tam_y/2,
                                     player->x + player->tam_x/2,
                                     player->y + player->tam_y/2,
                                     al_map_rgb(0, 0, 255));
        player->timer_colisao--;

	if (!player->timer_colisao)
            player->colisao = 0;
    }

    for (size_t i = 0; i < ini_num; i++) {
        if (valid[i]) {
            al_draw_filled_rectangle(
                                 inimigos[i]->x - inimigos[i]->tam_x/2,
                                 inimigos[i]->y - inimigos[i]->tam_y/2,
                                 inimigos[i]->x + inimigos[i]->tam_x/2,
                                 inimigos[i]->y + inimigos[i]->tam_y/2,
                                 al_map_rgb(255, 0, 0));
            if (inimigos[i]->arma != NULL) {
                for (bullet *index = inimigos[i]->arma->shots;
                     index != NULL; index = (bullet*) index->prox) {

                    if (inimigos[i]->tipo == INIMIGO4)
                        al_draw_filled_rectangle(
                                             index->x - BULLET_TAM_Y/2,
                                             index->y - BULLET_TAM_X/2,
                                             index->x + BULLET_TAM_Y/2,
                                             index->y + BULLET_TAM_X/2,
                                             al_map_rgb(255, 255, 0));
                    else
                        al_draw_filled_rectangle(
                                             index->x - BULLET_TAM_X/2,
                                             index->y - BULLET_TAM_Y/2,
                                             index->x + BULLET_TAM_X/2,
                                             index->y + BULLET_TAM_Y/2,
                                             al_map_rgb(255, 255, 0));
                }
            }
        }
    }

    al_draw_filled_rectangle(boss->x - boss->tam_x/2,
                             boss->y - boss->tam_y/2,
                             boss->x + boss->tam_x/2,
                             boss->y + boss->tam_y/2,
                             al_map_rgb(100, 100, 100));

    for (bullet *index = boss->arma->shots; index != NULL;
                    index = (bullet*) index->prox)
        al_draw_filled_rectangle(index->x - BULLET_TAM_X/2,
                                 index->y - BULLET_TAM_Y/2,
                                 index->x + BULLET_TAM_X/2,
                                 index->y + BULLET_TAM_Y/2,
                                 al_map_rgb(0, 255, 0));
 
    bullet *index = player->canhao->shots;
    switch (player->powerup) {
        case PU1:
	    if (index)
		al_draw_filled_rectangle(index->x,
                                         index->y - CANHAO_PU1_TAM_Y/2,
                                         X_TELA,
                                         index->y + CANHAO_PU1_TAM_Y/2,
                                         al_map_rgb(255, 255, 0));
	    break;
	case PU2:
	    break;
	default:
	    break;

    }

    switch (boss->tipo) {
        case BOSS1:
	    for (bullet *index = boss->canhao->shots; index != NULL;
                    index = (bullet*) index->prox)
            al_draw_filled_rectangle(index->x - CANHAO_TAM_X/2,
                                     index->y - CANHAO_TAM_Y/2,
                                     index->x + CANHAO_TAM_X/2,
                                     index->y + CANHAO_TAM_Y/2,
                                     al_map_rgb(0, 255, 0));
	    break;
	case BOSS2:
	    if (boss->trooper && boss->valid)
                al_draw_filled_rectangle(
                             boss->trooper->x - boss->trooper->tam_x/2,
                             boss->trooper->y - boss->trooper->tam_y/2,
                             boss->trooper->x + boss->trooper->tam_x/2,
                             boss->trooper->y + boss->trooper->tam_y/2,
                             al_map_rgb(255, 0, 0));
	    break;
	default:
	    break;
    }
    for (size_t i = 0; i < PU_NUM; i++) {
        if (valid_pu[i])
            al_draw_filled_circle(powerups[i]->x, powerups[i]->y, POWERUP_R,
			            al_map_rgb(0, 255, 255));
    }

    for (bullet *index = player->arma->shots; index != NULL;
                    index = (bullet*) index->prox)
        al_draw_filled_rectangle(index->x - BULLET_TAM_X/2,
                                 index->y - BULLET_TAM_Y/2,
                                 index->x + BULLET_TAM_X/2,
                                 index->y + BULLET_TAM_Y/2,
                                 al_map_rgb(0, 255, 0));

    al_flip_display();
}

void atualiza_menu(botao **botoes, unsigned char botao_num, ALLEGRO_FONT* font)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
        for (size_t i = 0; i < botao_num; i++) {
            al_draw_filled_rectangle(botoes[i]->x - botoes[i]->tam_x/2,
                                     botoes[i]->y - botoes[i]->tam_y/2,
                                     botoes[i]->x + botoes[i]->tam_x/2,
                                     botoes[i]->y + botoes[i]->tam_y/2,
                                     al_map_rgb(100, 100, 100));
            al_draw_text(font, al_map_rgb(0, 0, 0), botoes[i]->x,
                   botoes[i]->y, ALLEGRO_ALIGN_CENTER, botoes[i]->comando);
        }

        al_flip_display();
}

int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_ttf_addon();

    ALLEGRO_TIMER* relogio = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* tela = al_create_display(X_TELA, Y_TELA);

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_display_event_source(tela));
    al_register_event_source(fila, al_get_timer_event_source(relogio));
    al_register_event_source(fila, al_get_mouse_event_source());

    size_t botao_num = 2;
    botao* botoes[botao_num];

    botoes[0] = botao_cria(X_TELA/2, 300, "Jogar");
    botoes[1] = botao_cria(X_TELA/2, 450, "Sair");

    player* player = player_cria(PLAYER_TAM_X, PLAYER_TAM_Y, PLAYER_TAM_X,
                            Y_TELA/2);    
    size_t ini_num = 0;
    unsigned char valid_fase1[INIMIGOS_FASE1];
    inimigo *inimigos_fase1[INIMIGOS_FASE1];
    powerup *powerups_fase1[PU_NUM];
    unsigned char valid_pu_fase1[PU_NUM];
    boss *boss_fase1;
    unsigned char valid_fase2[INIMIGOS_FASE2];
    inimigo *inimigos_fase2[INIMIGOS_FASE2];
    powerup *powerups_fase2[PU_NUM];
    unsigned char valid_pu_fase2[PU_NUM];
    boss *boss_fase2;

    unsigned short time = 0;
    unsigned char gameover = 0;
    unsigned char game = 0;
    unsigned char menu = 1;

    ALLEGRO_EVENT evento;
    al_start_timer(relogio);

    while(1) {
        al_wait_for_event(fila, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
	else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menu) {
            unsigned char saiu = 0;
	    for (size_t i = 0; i < botao_num; i++) {
                if (botao_click(botoes[i], evento.mouse.x, evento.mouse.y)) {
                    if (strcmp(botoes[i]->comando, "Jogar") == 0) {
		        menu = 0;
			game = 1;
		    }
		    else if (strcmp(botoes[i]->comando, "Sair") == 0)
			saiu = 1;
		}
	    }
	    if (saiu)
		break;
	}

	if (gameover == PERDEU) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 0, 0), X_TELA/2 - 50, 
		          Y_TELA/2 - 15, 0, "VOCÊ MORREU!");
            al_draw_text(font, al_map_rgb(255, 255, 255), X_TELA/2 - 110, 
       			  Y_TELA/2 + 5, 0, "PRESSIONE ENTER PARA SAIR");
            al_flip_display();
            if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) && 
		      (evento.keyboard.keycode == ALLEGRO_KEY_ENTER))
                break;
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                break;
        }
        else if (gameover == GANHOU) {
	    
	    al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(0, 255, 0), X_TELA/2 - 50,
                                Y_TELA/2 - 15, 0, "VOCÊ GANHOU!");
	    al_draw_textf(font, al_map_rgb(255, 255, 255), X_TELA/2 - 60,
				Y_TELA/2 + 5, 0, "PONTUAÇAO: %d", 
				player->pontuacao);
            if (game == 1)
	        al_draw_text(font, al_map_rgb(255, 255, 255), X_TELA/2 - 120,
                                Y_TELA/2 + 30, 0, 
				"PRESSIONE ENTER PARA CONTINUAR");
	    else 
		al_draw_text(font, al_map_rgb(255, 255, 255), X_TELA/2 - 110,
                                Y_TELA/2 + 30, 0, "PRESSIONE ENTER PARA SAIR");
            al_flip_display();
            if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) &&
                (evento.keyboard.keycode == ALLEGRO_KEY_ENTER))
                if (game == 1) {
		    player->hp = PLAYER_HP;
		    player->controle->esq = 0;
		    player->controle->dir = 0;
                    player->controle->cima = 0;
		    player->controle->baixo= 0;
		    player->controle->atira = 0;
		    player->x = PLAYER_TAM_X;
		    player->y = Y_TELA/2;
		    player->powerup = NO_PU;
		    bullet *sentinela;
                    for (bullet *index = player->arma->shots; index != NULL; 
				    index = sentinela) {
                        sentinela = (bullet*) index->prox;
                        bullet_destroi(index);
                    }
                    player->arma->shots = NULL;
		    sentinela = NULL;
		    for (bullet *index = player->canhao->shots; index != NULL;
                                    index = sentinela) {
                        sentinela = (bullet*) index->prox;
                        bullet_destroi(index);
                    }
                    player->canhao->shots = NULL;
		    game = 2;
		    time = 0;
		    gameover = 0;
		}
	        else
		    break;
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                break;
	}
	else if (menu)
	    atualiza_menu(botoes, botao_num, font);
	else if (game == 1 && !ini_num) {
	    
	    ini_num = INIMIGOS_FASE1;

	    for (size_t i = 0; i < ini_num; i++)
		valid_fase1[i] = 1;

	    for (size_t i = 0; i < PU_NUM; i++)
		valid_pu_fase1[i] = 1;

	    if (!inicializa_ini_fase1(inimigos_fase1, ini_num))
		return 1;

            if (!inicializa_powerups(powerups_fase1, game))
		return 1;

	    boss_fase1 = boss_cria(BOSS1, X_TELA + BOSS1_TAM_X, Y_TELA/2, 
			    SPAWNBOSS1);

	    if (!boss_fase1)
		return 1;

	}
	else if (game == 2 && ini_num == INIMIGOS_FASE1) {

	    ini_num = INIMIGOS_FASE2;

	    for (size_t i = 0; i < ini_num; i++)
                valid_fase2[i] = 1;

	    for (size_t i = 0; i < PU_NUM; i++)
	        valid_pu_fase2[i] = 1;

            if (!inicializa_ini_fase2(inimigos_fase2, ini_num))
                return 1;

            if (!inicializa_powerups(powerups_fase2, game))
		return 1;

            boss_fase2 = boss_cria(BOSS2, X_TELA + BOSS2_TAM_X, Y_TELA/2,
                            SPAWNBOSS2);

            if (!boss_fase2)
                return 1;

	}
	else if (!gameover && game && evento.type == ALLEGRO_EVENT_TIMER) {
            time++;
	    switch (game) {
                case 1:
	            atualiza_jogo(player, inimigos_fase1, boss_fase1,
				    powerups_fase1, valid_fase1, valid_pu_fase1
				    , time, &gameover, ini_num, game);
                    break;
		case 2:
		    atualiza_jogo(player, inimigos_fase2, boss_fase2, 
				    powerups_fase2, valid_fase2, valid_pu_fase2
				    , time, &gameover, ini_num, game);
                    break;
		default:
		    break;
	    }
	}

	else if ((evento.type == ALLEGRO_EVENT_KEY_UP && game) || 
	        (evento.type == ALLEGRO_EVENT_KEY_DOWN && game)) {
            switch (evento.keyboard.keycode) {
                case ALLEGRO_KEY_A:
	            joystick_esq(player->controle);
		    break;
		case ALLEGRO_KEY_D:
		    joystick_dir(player->controle);
		    break;
		case ALLEGRO_KEY_W:
		    joystick_cima(player->controle);
		    break;
		case ALLEGRO_KEY_S:
		    joystick_baixo(player->controle);
		    break;
		case ALLEGRO_KEY_SPACE:
		    joystick_atira(player->controle);
		    break;
		case ALLEGRO_KEY_C:
		    joystick_especial(player->controle);
		    break;
		default:
		    break;
	    }
	}	
    }

    if (game == 1) {
        for (size_t i = 0; i < ini_num; i++) {
            if (valid_fase1[i])
                inimigo_destroi(inimigos_fase1[i]);
        }
        if (boss_fase1)
            boss_destroi(boss_fase1);

	for (size_t i = 0; i < PU_NUM; i++) {
            if (valid_pu_fase1[i])
		powerup_destroi(powerups_fase1[i]);
	}

        player_destroi(player);
    }
    else if (game == 2) {
        for (size_t i = 0; i < ini_num; i++) {
            if (valid_fase2[i])
                inimigo_destroi(inimigos_fase2[i]);
        }
        if (boss_fase2)
            boss_destroi(boss_fase2);

        for (size_t i = 0; i < PU_NUM; i++) {
            if (valid_pu_fase2[i])
                powerup_destroi(powerups_fase2[i]);
        }

	player_destroi(player);
    }
    for (size_t i = 0; i < botao_num; i++)
        botao_destroi(botoes[i]);

    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_timer(relogio);
    al_destroy_event_queue(fila);

    return 0;

}
