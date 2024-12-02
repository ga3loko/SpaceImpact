#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "player.h"
#include "inimigo.h"
#include "boss.h"

#define X_TELA 1080
#define Y_TELA 720
#define FPS 30
#define SPAWN1 100
#define SPAWN2 100
#define SPAWN3 100
#define SPAWN4 100
#define SPAWNBOSS1 100
#define SPAWNBOSS2 3

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
	else
            player->arma->timer--;
    }

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
	    if (!boss->trooper)
		boss->trooper = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X, 
			                  player->y, time);
	    else {
                if (boss->valid) {
		    if (player->y > boss->trooper->y + boss->trooper->tam_y/2)
                        boss->trooper->direcao = 2;
                    else if (player->y < boss->trooper->y - boss->trooper->tam_y/2)
                        boss->trooper->direcao = 1;
                    else
                        boss->trooper->direcao = 0;

		    inimigo_move(boss->trooper, 1, -boss->trooper->tam_x/2,
				    Y_TELA, &(boss->valid));
		    if (boss->valid) {
                        if (matou_inimigo(player, boss->trooper)) {
			    inimigo_destroi(boss->trooper);
			    boss->valid = 0;
			}
			if (boss->valid && !player->colisao && matou_player_ini(player,
					       	boss->trooper))
			    return 1;
		    }
		}
	    }
	}
    }

    movimenta_bullets_boss(boss);

    if (matou_boss(player, boss))
	return 2;

    if (!player->colisao && matou_player_boss(player, boss))
	return 1;
    
    return 0;
}


unsigned char atualiza_inimigos(inimigo **inimigos, size_t ini_num, unsigned char *valid, unsigned short time, player *player)
{
    
    for (size_t i = 0; i < ini_num; i++) {
        if (valid[i] && time >= inimigos[i]->spawn) {
            
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
                    inimigo_destroi(inimigos[i]);
		    valid[i] = 0;
		}
                
                if (valid[i] && !player->colisao && 
				matou_player_ini(player, inimigos[i]))
		    return 1;
	    }
	}
    }

    return 0;
}

int main()
{
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_TIMER* relogio = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* tela = al_create_display(X_TELA, Y_TELA);

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_display_event_source(tela));
    al_register_event_source(fila, al_get_timer_event_source(relogio));

    player* player = player_cria(PLAYER_TAM_X, PLAYER_TAM_Y, 100, Y_TELA/2);
    if (!player) 
	return 1;
    
    size_t ini_num = 4;
    inimigo* inimigos[ini_num];
    unsigned char valid[ini_num];
    
    for (size_t i = 0; i < ini_num; i++)
	valid[i] = 1;


    inimigos[0] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, Y_TELA/2, 
		    FPS * SPAWN1);
    inimigos[1] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X, Y_TELA/2, 
		    FPS * SPAWN2);
    inimigos[2] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, Y_TELA/2, 
		    FPS * SPAWN3);
    inimigos[3] = inimigo_cria(INIMIGO4, X_TELA + INIMIGO4_TAM_X, 
		    Y_TELA - INIMIGO4_TAM_Y/2, FPS * SPAWN4);

    boss* boss = boss_cria(BOSS2, X_TELA + BOSS2_TAM_X, Y_TELA/2, FPS * SPAWNBOSS2);

    if (!inimigos[0] || !inimigos[1] || !inimigos[2] || !inimigos[3])
	return 1;

    if (!boss)
	return 1;

    unsigned short time = 0;
    unsigned char gameover = 0;

    ALLEGRO_EVENT evento;
    al_start_timer(relogio);

    while(1) {
        al_wait_for_event(fila, &evento);

	if (gameover == 1) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 0, 0), X_TELA/2 - 50, 
		          Y_TELA/2 - 15, 0, "VOCÊ MORREU!");
            al_draw_text(font, al_map_rgb(255, 255, 255), X_TELA/2 - 110, 
       			  Y_TELA/2 + 5, 0, "PRESSIONE ESPAÇO PARA SAIR");
            al_flip_display();
            if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) && 
		      (evento.keyboard.keycode == ALLEGRO_KEY_SPACE))
                break;
            else if (evento.type == 42)
                break;
        }
        else if (gameover == 2) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(0, 255, 0), X_TELA/2 - 50,
                                Y_TELA/2 - 15, 0, "VOCÊ GANHOU!");
                al_draw_text(font, al_map_rgb(255, 255, 255), X_TELA/2 - 110,
                                Y_TELA/2 + 5, 0, "PRESSIONE ESPAÇO PARA SAIR");
                al_flip_display();
                if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) &&
                    (evento.keyboard.keycode == ALLEGRO_KEY_SPACE))
                    break;
                else if (evento.type == 42)
                    break;
	}
	else if (!gameover && evento.type == 30) {
            time++;
	    movimenta_player(player);
	    if (time <= FPS * SPAWNBOSS2)
	        gameover = atualiza_inimigos
			            (inimigos, ini_num, valid, time, player);
	    else
	        gameover = atualiza_boss(boss, player, time);

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
                            
                            if (inimigos[i]->tipo == 3)
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

	    if (boss->tipo == BOSS2) {
		if (boss->trooper && boss->valid)
                    al_draw_filled_rectangle(
                                         boss->trooper->x - boss->trooper->tam_x/2,
                                         boss->trooper->y - boss->trooper->tam_y/2,
                                         boss->trooper->x + boss->trooper->tam_x/2,
                                         boss->trooper->y + boss->trooper->tam_y/2,
                                         al_map_rgb(255, 0, 0));

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
	else if ((evento.type == ALLEGRO_EVENT_KEY_UP) || 
	        (evento.type == ALLEGRO_EVENT_KEY_DOWN)) {
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
		case ALLEGRO_KEY_C:
		    joystick_atira(player->controle);
		    break;
		default:
		    break;
	    }
	}
	else if (evento.type == 42)
	    break;
	
    }

    for (size_t i = 0; i < ini_num; i++) {
        if (valid[i])
            inimigo_destroi(inimigos[i]);
    }
    if (boss)
        boss_destroi(boss);
    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_timer(relogio);
    al_destroy_event_queue(fila);
    player_destroi(player);

    return 0;

}
