#ifndef __POWERUP__
#define __POWERUP__

#define POWERUP_VEL 5
#define POWERUP_R 10

typedef struct {
    unsigned char tipo;
    unsigned short x;
    unsigned short y;
} powerup;

powerup* powerup_cria(unsigned char tipo, unsigned short x, unsigned short y);

void powerup_move(powerup *powerup);

void powerup_destroi(powerup *powerup);

#endif
