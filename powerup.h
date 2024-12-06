#ifndef __POWERUP__
#define __POWERUP__

#define POWERUP_VEL 5
#define POWERUP_R 20
enum tipoPower {
    PU1,
    PU2,
    NO_PU
};

typedef struct {
    enum tipoPower tipo;
    unsigned short x;
    unsigned short y;
    unsigned short spawn;
} powerup;

powerup* powerup_cria(enum tipoPower tipo, unsigned short x, unsigned short y, unsigned short spawn);

void powerup_destroi(powerup *powerup);

void powerup_move(powerup *powerup, unsigned char *valid);

#endif
