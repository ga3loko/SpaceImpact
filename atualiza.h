#ifndef __ATUALIZA__
#define __ATUALIZA__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "player.h"
#include "powerup.h"
#include "inimigo.h"
#include "boss.h"
#include "botao.h"

//Atualiza as balas normais e especiais do player
void movimenta_bullets_player(player *player);

//Atualiza as balas dos inimigos
void movimenta_bullets_inimigo(inimigo *inimigo);

//Atualiza as balas normais e especias dos boss
void movimenta_bullets_boss(boss *boss);

//Verifica se o player se colidiu com um inimigo
unsigned char colidiu_ini(player* player, inimigo *inimigo);

//Verifica se o player se colidiu com um powerup
unsigned char colidiu_powerup(powerup* powerup, player *player);

//Verifica se o player se colidiu com o boss
unsigned char colidiu_boss(player* player, boss *boss);

//Atualiza o player
void atualiza_player(player *player);

//Verifica se o boss morreu
unsigned char matou_boss(player *player, boss *boss);

//Verifica se o boss matou o player
unsigned char matou_player_boss(player *player, boss *boss);

//Verifica se o inimigo morreu
unsigned char matou_inimigo(player *player, inimigo *inimigo);

//Verifica se o inimigo matou o player
unsigned char matou_player_ini(player *player, inimigo *inimigo);

//Atualiza o boss
unsigned char atualiza_boss(boss *boss, player *player, unsigned short time);

//Atualiza os inimigos
unsigned char atualiza_inimigos(inimigo **inimigos, size_t ini_num, unsigned char *valid, unsigned short time, player *player);

//Atualiza os powerups
void atualiza_powerup(powerup **powerups, player *player, unsigned short time, unsigned char *valid);

//Atualiza a tela
void atualiza_tela(player *player, inimigo **inimigos, boss *boss, powerup **powerups, unsigned char *valid, unsigned char *valid_pu, size_t ini_num, ALLEGRO_BITMAP **imagens, ALLEGRO_FONT *font);

//Atualiza os componentes do jogo
void atualiza_jogo(player *player, inimigo **inimigos, boss *boss, powerup **powerups, unsigned char *valid, unsigned char *valid_pu, unsigned short time, unsigned char *gameover, size_t ini_num);

//Atualiza as telas de menu
void atualiza_menu(botao **botoes, unsigned char botao_num, ALLEGRO_FONT* font);

#endif
