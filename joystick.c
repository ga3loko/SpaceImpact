#include <stdio.h>
#include <stdlib.h>

#include "joystick.h"

joystick* joystick_cria() 
{

    joystick *new_joystick = (joystick*) malloc (sizeof(joystick));
    new_joystick->esq = 0;
    new_joystick->dir = 0;
    new_joystick->cima = 0;
    new_joystick->baixo = 0;
    new_joystick->atira = 0;
    new_joystick->especial = 0;

    return new_joystick;

}

void joystick_destroi(joystick *joystick)
{
    free(joystick);
}

void joystick_esq(joystick *joystick)
{ 
    joystick->esq = joystick->esq ^ 1;
}

void joystick_dir(joystick *joystick)
{ 
    joystick->dir = joystick->dir ^ 1;
}

void joystick_cima(joystick *joystick)
{ 
    joystick->cima = joystick->cima ^ 1;
}

void joystick_baixo(joystick *joystick)
{ 
    joystick->baixo = joystick->baixo ^ 1;
}

void joystick_atira(joystick *joystick)
{
    joystick->atira = joystick->atira ^ 1;
}

void joystick_especial(joystick *joystick)
{
    joystick->especial = joystick->especial ^ 1;
}
