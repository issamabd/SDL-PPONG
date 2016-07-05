RM = rm -fv
OBJECT = main.o display.o moveball.o player2_rpc_server.o player1_rpc_clnt.o player2_rpc_svc.o
LDFLAGS = -Wall -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -lnsl
CC = gcc

player2: $(OBJECT)
	$(CC) -o player2 $(OBJECT) $(LDFLAGS) 

main.o: main.c display.h game.h moveball.h player2_rpc.h player1_rpc.h
	$(CC) -c main.c

moveball.o: moveball.c moveball.h game.h
	$(CC) -c moveball.c

display.o: display.c game.h display.h
	$(CC) -c display.c
	
player2_rpc_server.o: player2_rpc_server.c player2_rpc.h
	$(CC) -c player2_rpc_server.c
	
player1_rpc_clnt.o: player1_rpc_clnt.c player1_rpc.h
	$(CC) -c player1_rpc_clnt.c
	
player2_rpc_svc.o: player2_rpc_svc.c 
	$(CC) -c player2_rpc_svc.c
	
clean: 
	$(RM) $(OBJECT)

