RM = rm -fv
OBJECT = main.o display.o net.o buffer.o
LDFLAGS = -Wall -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer
CC = gcc

player2: $(OBJECT)
	$(CC) -o player2 $(OBJECT) $(LDFLAGS) 

main.o: main.c game.h display.h buffer.h
	$(CC) -c main.c

display.o: display.c game.h display.h buffer.h
	$(CC) -c display.c

net.o: net.c game.h net.h buffer.h
	$(CC) -c net.c

buffer.o: buffer.c buffer.h
	$(CC) -c buffer.c
	
clean: 
	$(RM) $(OBJECT)

