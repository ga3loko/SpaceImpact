#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct {
    unsigned char dir;
    unsigned char esq;
    unsigned char cima;
    unsigned char baixo;
    unsigned char atira;
    unsigned char especial;
} joystick;

joystick* joystick_cria();
void joystick_destroi(joystick *joystick);
void joystick_dir(joystick *joystick);
void joystick_esq(joystick *joystick);
void joystick_cima(joystick *joystick);
void joystick_baixo(joystick *joystick);
void joystick_atira(joystick *joystick);
void joystick_especial(joystick *joystick);

#endif
