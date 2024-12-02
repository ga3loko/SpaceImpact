#ifndef __BOTAO__
#define __BOTAO__

#define BOTAO_TAM_X 400
#define BOTAO_TAM_Y 100

typedef struct {
    unsigned short x;
    unsigned short y;
    unsigned short tam_x;
    unsigned short tam_y;
    char* comando;
} botao;

botao* botao_cria(unsigned short x, unsigned short y, char* comando);

unsigned char botao_click(botao *botao, unsigned short x, unsigned short y);

void botao_destroi(botao *botao);

#endif
