#include <stdio.h>
#include <stdlib.h>

#include "atualiza.h"
#include "defines.h"

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

    if (player->canhao->shots) {
        switch (player->powerup) {
            case NO_PU:
                break;
            case PU1:
                player->canhao->shots->y = player->y;
                player->canhao->shots->x = player->x + player->tam_x/2;
                break;
            case PU2:
                bullet_move(player->canhao->shots);
                if (player->canhao->shots->x > X_TELA) {
                    bullet_destroi(player->canhao->shots);
                    player->canhao->shots = NULL;
                }
                break;
            default:
                break;
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

    anterior = NULL;
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

void atualiza_player(player *player)
{

    if (player->controle->esq)
        player_move(player, ESQ, X_TELA, Y_TELA);
    if (player->controle->dir)
        player_move(player, DIRE, X_TELA, Y_TELA);
    if (player->controle->cima)
        player_move(player, CIMA, X_TELA, Y_TELA);
    if (player->controle->baixo)
        player_move(player, BAIXO, X_TELA, Y_TELA);
    if (player->controle->atira) {
        if (!player->arma->timer) {
            player_atira(player);
            player->arma->timer = PISTOLA_COOLDOWN;
        }
    }

    if (player->arma->timer > 0)
        player->arma->timer--;

    if (player->controle->especial) {
        joystick_especial(player->controle);
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
                if (!player->canhao->shots) {
                    player_especial(player);
                    player->canhao->detonou = 0;
                }
                else {
                    player->canhao->detonou = 1;
                    player->canhao->timer = DETONOU_COOLDOWN;
                    player->canhao->shots->trajetoria = 3;
                }
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
            if (player->canhao->shots && !player->canhao->timer &&
                            player->canhao->detonou) {
                bullet_destroi(player->canhao->shots);
                player->canhao->shots = NULL;
                player->powerup = NO_PU;
            }
            break;
        default:
            break;
    }

    if ((player->powerup == PU1 && player->canhao->timer) ||
        (player->powerup == PU2 && player->canhao->timer
                                && player->canhao->detonou))
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
                return MATOU;
            return N_MATOU;
        }
        anterior = index;
    }

    anterior = player->canhao->shots;
    switch (player->powerup) {
        case PU1:
            if (anterior) {
                if ((((anterior->y - CANHAO_PU1_TAM_Y/2 >=
                                boss->y - boss->tam_y/2) &&
                     (boss->y + boss->tam_y/2 >=
                      anterior->y - CANHAO_PU1_TAM_Y/2)) ||
                     ((boss->y - boss->tam_y/2 >=
                       anterior->y - CANHAO_PU1_TAM_Y/2) &&
                    (anterior->y + CANHAO_PU1_TAM_Y/2 >=
                              boss->y - boss->tam_y/2))) &&
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
            if (anterior) {
                if (!player->canhao->detonou) {
                    if ((((anterior->y - CANHAO_PU2_R1 >=
                                boss->y - boss->tam_y/2) &&
                      (boss->y + boss->tam_y/2 >=
                                 anterior->y - CANHAO_PU2_R1)) ||
                     ((boss->y - boss->tam_y/2 >=
                                  anterior->y - CANHAO_PU2_R1) &&
                          (anterior->y + CANHAO_PU2_R1 >=
                              boss->y - boss->tam_y/2))) &&
                        (((anterior->x - CANHAO_PU2_R1 >=
                                boss->x - boss->tam_x/2) &&
                      (boss->x + boss->tam_x/2 >=
                                 anterior->x - CANHAO_PU2_R1)) ||
                     ((boss->x - boss->tam_x/2 >=
                                  anterior->x - CANHAO_PU2_R1) &&
                          (anterior->x + CANHAO_PU2_R1 >=
                              boss->x - boss->tam_x/2)))) {

                        if (boss->hp >= 5)
                            boss->hp -= 5;
                        else
                            boss->hp = 0;

                        bullet_destroi(player->canhao->shots);
                        player->canhao->shots = NULL;
                        player->powerup = NO_PU;

                    }
                }
                if (player->canhao->detonou) {
                    if ((((anterior->y - CANHAO_PU2_R2 >=
                                boss->y - boss->tam_y/2) &&
                      (boss->y + boss->tam_y/2 >=
                                 anterior->y - CANHAO_PU2_R2)) ||
                     ((boss->y - boss->tam_y/2 >=
                                  anterior->y - CANHAO_PU2_R2) &&
                          (anterior->y + CANHAO_PU2_R2 >=
                              boss->y - boss->tam_y/2))) &&
                        (((anterior->x - CANHAO_PU2_R2 >=
                                boss->x - boss->tam_x/2) &&
                      (boss->x + boss->tam_x/2 >=
                                 anterior->x - CANHAO_PU2_R2)) ||
                     ((boss->x - boss->tam_x/2 >=
                                  anterior->x - CANHAO_PU2_R2) &&
                          (anterior->x + CANHAO_PU2_R2 >=
                              boss->x - boss->tam_x/2)))) {

                        if (boss->hp >= 5)
                            boss->hp -= 5;
                        else
                            boss->hp = 0;

                        bullet_destroi(player->canhao->shots);
                        player->canhao->shots = NULL;
                        player->powerup = NO_PU;
                    }
                }
            }
            break;
        case NO_PU:
            break;
        default:
            break;
    }

    if (!boss->hp)
        return MATOU;
    return N_MATOU;
}

unsigned char matou_player_boss(player *player, boss *boss)
{
    if (colidiu_boss(player, boss)) {
        player->hp--;
        if (!player->hp)
            return MATOU;
        player->colisao = 1;
        return N_MATOU;
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
                return MATOU;
            return N_MATOU;
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
                    return MATOU;
                return N_MATOU;
            }
            anterior = index;
        }
    }

    return N_MATOU;

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
                    return MATOU;
                return N_MATOU;
            }
            anterior = index;
        }

    anterior = player->canhao->shots;
    switch (player->powerup) {
        case PU1:
            if (anterior) {
                if ((((anterior->y - CANHAO_PU1_TAM_Y/2 >=
                                inimigo->y - inimigo->tam_y/2) &&
                     (inimigo->y + inimigo->tam_y/2 >=
                            anterior->y - CANHAO_PU1_TAM_Y/2)) ||
                     ((inimigo->y - inimigo->tam_y/2 >=
                             anterior->y - CANHAO_PU1_TAM_Y/2) &&
                    (anterior->y + CANHAO_PU1_TAM_Y/2 >=
                              inimigo->y - inimigo->tam_y/2))) &&
                    (((anterior->x >= inimigo->x - inimigo->tam_x/2) &&
                     (inimigo->x + inimigo->tam_x/2 >= anterior->x)) ||
                     ((inimigo->x - inimigo->tam_x/2 >= anterior->x) &&
                         (X_TELA >= inimigo->x - inimigo->tam_x/2))))

                    inimigo->hp = 0;
            }
            break;
        case PU2:
            if (anterior) {
                if (!player->canhao->detonou) {
                    if ((((anterior->y - CANHAO_PU2_R1 >=
                                inimigo->y - inimigo->tam_y/2) &&
                      (inimigo->y + inimigo->tam_y/2 >=
                                 anterior->y - CANHAO_PU2_R1)) ||
                     ((inimigo->y - inimigo->tam_y/2 >=
                                  anterior->y - CANHAO_PU2_R1) &&
                          (anterior->y + CANHAO_PU2_R1 >=
                              inimigo->y - inimigo->tam_y/2))) &&
                        (((anterior->x - CANHAO_PU2_R1 >=
                                inimigo->x - inimigo->tam_x/2) &&
                      (inimigo->x + inimigo->tam_x/2 >=
                                 anterior->x - CANHAO_PU2_R1)) ||
                     ((inimigo->x - inimigo->tam_x/2 >=
                                  anterior->x - CANHAO_PU2_R1) &&
                          (anterior->x + CANHAO_PU2_R1 >=
                              inimigo->x - inimigo->tam_x/2)))) {

                        inimigo->hp = 0;

                        bullet_destroi(player->canhao->shots);
                        player->canhao->shots = NULL;
                        player->powerup = NO_PU;


                    }
                }
                if (player->canhao->detonou) {
                    if ((((anterior->y - CANHAO_PU2_R2 >=
                                inimigo->y - inimigo->tam_y/2) &&
                      (inimigo->y + inimigo->tam_y/2 >=
                                 anterior->y - CANHAO_PU2_R2)) ||
                     ((inimigo->y - inimigo->tam_y/2 >=
                                  anterior->y - CANHAO_PU2_R2) &&
                          (anterior->y + CANHAO_PU2_R2 >=
                              inimigo->y - inimigo->tam_y/2))) &&
                        (((anterior->x - CANHAO_PU2_R2 >=
                                inimigo->x - inimigo->tam_x/2) &&
                      (inimigo->x + inimigo->tam_x/2 >=
                                 anterior->x - CANHAO_PU2_R2)) ||
                     ((inimigo->x - inimigo->tam_x/2 >=
                                  anterior->x - CANHAO_PU2_R2) &&
                          (anterior->x + CANHAO_PU2_R2 >=
                              inimigo->x - inimigo->tam_x/2)))) {

                        inimigo->hp = 0;

                    }
                }
            }
            break;
        default:
            break;
    }

    if (!inimigo->hp)
         return MATOU;
    return N_MATOU;
}

unsigned char matou_player_ini(player *player, inimigo *inimigo)
{

    if (colidiu_ini(player, inimigo)) {
        player->hp--;
        if (!player->hp)
            return MATOU;
        player->colisao = 1;
        return N_MATOU;
    }

    if (!inimigo->arma)
        return N_MATOU;

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
                    return MATOU;
                return N_MATOU;
        }
        anterior = index;
    }
    return N_MATOU;
}

unsigned char atualiza_boss(boss *boss, player *player, unsigned short time)
{
    boss_move(boss, X_TELA - boss->tam_x/2 - 150, Y_TELA - boss->tam_y/2,
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
                        boss->trooper->direcao = BAIXO;
                    else if (player->y < boss->trooper->y -
                                    boss->trooper->tam_y/2)
                        boss->trooper->direcao = CIMA;
                    else
                        boss->trooper->direcao = ESQ;

                    inimigo_move(boss->trooper, -boss->trooper->tam_x/2,
                                    Y_TELA, &(boss->valid));
                    if (boss->valid) {
                        if (matou_inimigo(player, boss->trooper)) {
                            inimigo_destroi(boss->trooper);
                            boss->trooper = NULL;
                            boss->valid = 0;
                        }
                        if (boss->valid && !player->colisao &&
                                        matou_player_ini(player, boss->trooper))
                            return PERDEU;
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

    return N_MATOU;
}

unsigned char atualiza_inimigos(inimigo **inimigos, size_t ini_num, unsigned char *valid, unsigned short time, player *player)
{

    for (size_t i = 0; i < ini_num; i++) {
        if (valid[i] && time >= inimigos[i]->spawn * FPS) {

            if (inimigos[i]->tipo == INIMIGO3) {
                if (player->y > inimigos[i]->y + inimigos[i]->tam_y/2)
                    inimigos[i]->direcao = BAIXO;
                else if (player->y < inimigos[i]->y - inimigos[i]->tam_y/2)
                    inimigos[i]->direcao = CIMA;
                else
                    inimigos[i]->direcao = ESQ;
            }
            inimigo_move(inimigos[i], -inimigos[i]->tam_x/2, Y_TELA,
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

    return N_MATOU;
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

void atualiza_tela(player *player, inimigo **inimigos, boss *boss, powerup **powerups, unsigned char *valid, unsigned char *valid_pu, size_t ini_num, ALLEGRO_BITMAP **imagens, ALLEGRO_FONT *font)
{
    player->frame_time++;

    if (player->frame_time / FPS >= FRAME_DELAY) {
        player->frame_atual = (player->frame_atual + 1) % NUM_FRAMES;
        player->frame_time = 0;
    }

    unsigned short frame_y = al_get_bitmap_height(imagens[animacao]);
    unsigned short frame_x = al_get_bitmap_width(imagens[animacao]);
    frame_y = frame_y / NUM_FRAMES;

    int y = frame_y * player->frame_atual;

    if (!player->colisao) {
        al_draw_bitmap(imagens[jogador],
                       player->x - player->tam_x/2,
                       player->y - player->tam_y/2, 0);
        if (player->controle->esq || player->controle->dir ||
            player->controle->cima || player->controle->baixo) {
            al_draw_bitmap_region(imagens[animacao], 0, y, frame_x, frame_y,
                                  player->x - player->tam_x/2 - frame_x/2,
                                  player->y - player->tam_y/2, 0);
        }

    }
    else {
        if (player->timer_colisao % 15 <= 7) {
            al_draw_bitmap(imagens[jogador],
                           player->x - player->tam_x/2,
                           player->y - player->tam_y/2, 0);
            if (player->controle->esq || player->controle->dir ||
                player->controle->cima || player->controle->baixo) {
                al_draw_bitmap_region(imagens[animacao], 0, y, frame_x, frame_y,
                                      player->x - player->tam_x/2 - frame_x/2,
                                      player->y - player->tam_y/2, 0);
            }

        }

        player->timer_colisao--;

        if (!player->timer_colisao)
            player->colisao = 0;
    }


    unsigned short bullet_x = al_get_bitmap_width(imagens[bala]);
    unsigned short bullet_y = al_get_bitmap_height(imagens[bala]);

    for (size_t i = 0; i < ini_num; i++) {
        if (valid[i]) {
            switch (inimigos[i]->tipo) {
                case INIMIGO1:
                    al_draw_bitmap(imagens[inimigo1],
                                   inimigos[i]->x - inimigos[i]->tam_x/2,
                                   inimigos[i]->y - inimigos[i]->tam_y/2, 0);
                    break;
                case INIMIGO2:
                    al_draw_bitmap(imagens[inimigo2],
                                   inimigos[i]->x - inimigos[i]->tam_x/2,
                                   inimigos[i]->y - inimigos[i]->tam_y/2, 0);
                    break;
                case INIMIGO3:
                    al_draw_bitmap(imagens[inimigo3],
                                   inimigos[i]->x - inimigos[i]->tam_x/2,
                                   inimigos[i]->y - inimigos[i]->tam_y/2, 0);
                    break;
                case INIMIGO4:
                    al_draw_bitmap(imagens[inimigo4],
                                   inimigos[i]->x - inimigos[i]->tam_x/2,
                                   inimigos[i]->y - inimigos[i]->tam_y/2, 0);
                    break;
                default:
                    break;
            }
            if (inimigos[i]->arma != NULL) {
                for (bullet *index = inimigos[i]->arma->shots;
                     index != NULL; index = (bullet*) index->prox) {

                    if (inimigos[i]->tipo == INIMIGO4)
                        al_draw_rotated_bitmap(imagens[bala],
                                               bullet_x / 2, bullet_y /2,
                                               index->x - BULLET_TAM_X/2,
                                               index->y - BULLET_TAM_Y/2,
                                               ALLEGRO_PI/2, 0);

                    else
                        al_draw_rotated_bitmap(imagens[bala],
                                               bullet_x / 2, bullet_y /2,
                                               index->x - BULLET_TAM_X/2,
                                               index->y - BULLET_TAM_Y/2,
                                               ALLEGRO_PI, 0);
                }
            }
        }
    }

    switch (boss->tipo) {
        case BOSS1:
            al_draw_bitmap(imagens[boss1],
                                   boss->x - boss->tam_x/2,
                                   boss->y - boss->tam_y/2, 0);
            break;
        case BOSS2:
            al_draw_bitmap(imagens[boss2],
                                   boss->x - boss->tam_x/2,
                                   boss->y - boss->tam_y/2, 0);
            break;
        default:
            break;
    }

    for (bullet *index = boss->arma->shots; index != NULL;
                    index = (bullet*) index->prox)
        al_draw_rotated_bitmap(imagens[bala], bullet_x / 2, bullet_y /2,
                               index->x - BULLET_TAM_X/2,
                               index->y - BULLET_TAM_Y/2, ALLEGRO_PI, 0);

    bullet *index = player->canhao->shots;
    unsigned short raio_x;
    if (index) {
        switch (player->powerup) {
            case PU1:
                raio_x = al_get_bitmap_width(imagens[raio]);
                for (unsigned short x = index->x; x < X_TELA; x += raio_x)
                    al_draw_bitmap(imagens[raio], x,
                                    index->y - CANHAO_PU1_TAM_Y/2, 0);
                break;
            case PU2:
                if (!player->canhao->detonou)
                    al_draw_bitmap(imagens[nuke1], index->x - CANHAO_PU2_R1,
                                   index->y - CANHAO_PU2_R1, 0);
                else
                    al_draw_bitmap(imagens[nuke2], index->x - CANHAO_PU2_R2,
                               index->y - CANHAO_PU2_R2, 0);
                break;
            default:
                break;
        }
    }


    switch (boss->tipo) {
        case BOSS1:
            for (bullet *index = boss->canhao->shots; index != NULL;
                    index = (bullet*) index->prox)
                al_draw_bitmap(imagens[wave],
                               index->x - CANHAO_TAM_X/2,
                               index->y - CANHAO_TAM_Y/2, 0);
            break;
        case BOSS2:
            if (boss->trooper && boss->valid)
                al_draw_bitmap(imagens[inimigo3],
                               boss->trooper->x - boss->trooper->tam_x/2,
                               boss->trooper->y - boss->trooper->tam_y/2, 0);
            break;
        default:
            break;
    }
    for (size_t i = 0; i < PU_NUM; i++) {
        if (valid_pu[i])
            al_draw_bitmap(imagens[especial],
                           powerups[i]->x - POWERUP_R,
                           powerups[i]->y - POWERUP_R, 0);
    }
    for (bullet *index = player->arma->shots; index != NULL;
                    index = (bullet*) index->prox)
        al_draw_bitmap(imagens[bala],
                       index->x - BULLET_TAM_X/2,
                       index->y - BULLET_TAM_Y/2, 0);
    
    al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 30, 0, "VIDA: %d", player->hp);
    al_flip_display();

}

void atualiza_jogo(player *player, inimigo **inimigos, boss *boss, powerup **powerups, unsigned char *valid, unsigned char *valid_pu, unsigned short time, unsigned char *gameover, size_t ini_num)
{
    atualiza_player(player);

    if (time <= FPS * boss->spawn)
        *gameover = atualiza_inimigos
                             (inimigos, ini_num, valid, time, player);
    else
        *gameover = atualiza_boss(boss, player, time);

    atualiza_powerup(powerups, player, time, valid_pu);

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


