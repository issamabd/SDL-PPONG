RM = rm -fv
OBJECT = main.o display.o net.o
LDFLAGS = -Wall -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer
CC = gcc

player2: $(OBJECT)
	$(CC) -o player2 $(OBJECT) $(LDFLAGS) 

main.o: main.c game.h display.h 
	$(CC) -c main.c

display.o: display.c game.h display.h 
	$(CC) -c display.c

net.o: net.c game.h net.h 
	$(CC) -c net.c

clean: 
	$(RM) $(OBJECT)

