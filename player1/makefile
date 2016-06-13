RM = rm -fv
OBJECT = main.o display.o net.o moveball.o 
LDFLAGS = -Wall -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer
CC = gcc

player1: $(OBJECT)
	$(CC) -o player1 $(OBJECT) $(LDFLAGS) 

main.o: main.c display.h game.h
	$(CC) -c main.c

moveball.o: moveball.c moveball.h game.h
	$(CC) -c moveball.c

display.o: display.c game.h display.h
	$(CC) -c display.c
	
net.o: net.c game.h net.h
	$(CC) -c net.c

clean: 
	$(RM) $(OBJECT)

