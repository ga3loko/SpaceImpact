#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "atualiza.h"
#include "defines.h"

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

int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();

    ALLEGRO_TIMER* relogio = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* tela = al_create_display(X_TELA, Y_TELA);
    ALLEGRO_BITMAP *background1 = al_load_bitmap("Imagens/back1.png");
    ALLEGRO_BITMAP *background2 = al_load_bitmap("Imagens/back2.png");
    ALLEGRO_BITMAP *imagens[IMAGENS_NUM];

    imagens[inimigo1] = al_load_bitmap("Imagens/inimigo1.png");
    imagens[inimigo2] = al_load_bitmap("Imagens/inimigo2.png");
    imagens[inimigo3] = al_load_bitmap("Imagens/inimigo3.png");
    imagens[inimigo4] = al_load_bitmap("Imagens/inimigo4.png");
    imagens[boss1] = al_load_bitmap("Imagens/boss1.png");
    imagens[boss2] = al_load_bitmap("Imagens/boss2.png");
    imagens[bala] = al_load_bitmap("Imagens/bullet.png");
    imagens[especial] = al_load_bitmap("Imagens/powerup.png");
    imagens[raio] = al_load_bitmap("Imagens/raio.png");
    imagens[wave] = al_load_bitmap("Imagens/wave.png");
    imagens[nuke1] = al_load_bitmap("Imagens/nuke1.png");
    imagens[nuke2] = al_load_bitmap("Imagens/nuke2.png");
    imagens[jogador] = al_load_bitmap("Imagens/player.png");
    imagens[animacao] = al_load_bitmap("Imagens/animacao.png");

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

    unsigned short bg_X = al_get_bitmap_width(background1);
    short bg_offset = 0;

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
		    bg_offset = 0;
		    time = 0;
		    gameover = 0;
		    al_destroy_bitmap(background1);
		    background1 = NULL;
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
	    bg_offset -= BG_VEL;
	    if (bg_offset <= -bg_X)
		bg_offset = 0;

	    al_clear_to_color(al_map_rgb(0, 0, 0));
	    switch (game) {
                case 1:
	            al_draw_bitmap(background1, bg_offset, 0, 0);
                    al_draw_bitmap(background1, bg_offset + bg_X, 0, 0);
		    atualiza_jogo(player, inimigos_fase1, boss_fase1,
				    powerups_fase1, valid_fase1, valid_pu_fase1
				    , time, &gameover, ini_num);
		    atualiza_tela(player, inimigos_fase1, boss_fase1,
				    powerups_fase1, valid_fase1, valid_pu_fase1
				    , ini_num, imagens, font);
                    break;
		case 2:
		    al_draw_bitmap(background2, bg_offset, 0, 0);
                    al_draw_bitmap(background2, bg_offset + bg_X, 0, 0);
		    atualiza_jogo(player, inimigos_fase2, boss_fase2, 
				    powerups_fase2, valid_fase2, valid_pu_fase2
				    , time, &gameover, ini_num);
		    atualiza_tela(player, inimigos_fase2, boss_fase2,
                                    powerups_fase2, valid_fase2, valid_pu_fase2
                                    , ini_num, imagens, font);
                    break;
		default:
		    break;
	    }

	}

	else if (evento.type == ALLEGRO_EVENT_KEY_DOWN && game && 
			evento.keyboard.keycode == ALLEGRO_KEY_C)
		joystick_especial(player->controle);

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

    for (size_t i = 0; i < IMAGENS_NUM; i++)
	al_destroy_bitmap(imagens[i]);

    al_destroy_bitmap(background2);
    if (background1)
	al_destroy_bitmap(background1);
    al_destroy_font(font);
    al_destroy_display(tela);
    al_destroy_timer(relogio);
    al_destroy_event_queue(fila);

    return 0;

}
