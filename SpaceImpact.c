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


unsigned char colidiu(player* player, inimigo *inimigo)
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

void movimenta_boss(boss *boss, unsigned short time)
{
    if (time >= boss->spawn) {
        boss_move(boss, 1, X_TELA - boss->tam_x/2 - 150, Y_TELA - boss->tam_y/2,
		    boss->tam_y/2);
        if (!boss->arma->timer) {
            boss_atira(boss);
            boss->arma->timer = PISTOLA_BOSS_COOLDOWN;
        }
        else
            boss->arma->timer--;

        movimenta_bullets_boss(boss);
    }
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
                index = (bullet*) index->prox;
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

unsigned char matou_player(player *player, inimigo *inimigo)
{
	
    if (colidiu(player, inimigo)) {
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
                index = (bullet*) index->prox;
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
	    inimigo_move(inimigos[i], 1, -inimigos[i]->tam_x, Y_TELA, 
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
				matou_player(player, inimigos[i]))
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

    ALLEGRO_TIMER* relogio = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* tela = al_create_display(X_TELA, Y_TELA);

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_display_event_source(tela));
    al_register_event_source(fila, al_get_timer_event_source(relogio));

    player* player = player_cria(PLAYER_TAM_X, PLAYER_TAM_Y, 100, Y_TELA/2);
    if (player == NULL) 
	return 1;
    
    inimigo* inimigos[4];
    size_t ini_num = 4;

    inimigos[0] = inimigo_cria(INIMIGO1, X_TELA + INIMIGO1_TAM_X, Y_TELA/2, 
		    30 * 2);
    inimigos[1] = inimigo_cria(INIMIGO3, X_TELA + INIMIGO3_TAM_X, Y_TELA/2, 
		    30 * 4);
    inimigos[2] = inimigo_cria(INIMIGO2, X_TELA + INIMIGO2_TAM_X, Y_TELA/2, 
		    30 * 6);
    inimigos[3] = inimigo_cria(INIMIGO4, X_TELA + INIMIGO4_TAM_X, 
		    Y_TELA - INIMIGO4_TAM_Y/2, 30 * 1);

    boss* boss = boss_cria(BOSS1, X_TELA + BOSS1_TAM_X, Y_TELA/2, 30 * 10);

    if (inimigos[0] == NULL || inimigos[1] == NULL || inimigos[2] == NULL ||
		    inimigos[3] == NULL)
	return 1;
    if (!boss)
	return 1;

    unsigned char  v[4];
    v[0] = 1;
    v[1] = 1;
    v[2] = 1;
    v[3] = 1;

    unsigned short time = 0;
    unsigned char gameover = 0;

    ALLEGRO_EVENT evento;
    al_start_timer(relogio);

    while(1) {
        al_wait_for_event(fila, &evento);

	if (gameover) {
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
	
	else if (evento.type == 30) {
            time++;
	    movimenta_player(player);
	    gameover = atualiza_inimigos(inimigos, ini_num, v, time, player);
	    movimenta_boss(boss, time);

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
                if (v[i]) {
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
        if (v[i])
            inimigo_destroi(inimigos[i]);
    }
    boss_destroi(boss);
    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_timer(relogio);
    al_destroy_event_queue(fila);
    player_destroi(player);

    return 0;

}
