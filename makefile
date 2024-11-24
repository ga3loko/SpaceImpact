TARGET = gcn23
SOURCES = SpaceImpact.c player.c joystick.c inimigo.c boss.c bullet.c pistola.c
ALLEGRO_FLAGS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags)
FLAGS = -Wall -Wextra -pedantic -g

all:
	gcc $(SOURCES) -o $(TARGET) $(ALLEGRO_FLAGS) $(FLAGS)

clean:
	rm -f $(TARGET)
