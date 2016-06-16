RM = rm -fv
OBJECT = main.o display.o net.o moveball.o buffer.o
LDFLAGS = -Wall -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer
CC = gcc

player1: $(OBJECT)
	$(CC) -o player1 $(OBJECT) $(LDFLAGS) 

main.o: main.c display.h game.h buffer.h net.h moveball.h
	$(CC) -c main.c

moveball.o: moveball.c moveball.h game.h buffer.h
	$(CC) -c moveball.c

display.o: display.c game.h display.h buffer.h
	$(CC) -c display.c
	
net.o: net.c game.h net.h
	$(CC) -c net.c

	
buffer.o: buffer.c buffer.h
	$(CC) -c buffer.c
	
clean: 
	$(RM) $(OBJECT)

