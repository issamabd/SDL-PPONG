#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "net.h"
#include "game.h"

extern int csock;
extern SDL_sem * semWrite1, * semRead1;  

int establish_connection(char *ip, int port)
{
   struct sockaddr_in client;
    
 char buffer[32];
 char sbuffer[32]= "Player 2 is ready ..";
   
/* Open a client socket */
printf("Configuring the connexion ...\n");
csock = socket(AF_INET, SOCK_STREAM, 0);

/* Setting the address (port + IP @) of the server socket */     
client.sin_addr.s_addr = inet_addr(ip);
client.sin_family = AF_INET;
client.sin_port = htons(port);

printf("Activating the connexion ...\n");

if(connect(csock, (struct sockaddr *)&client, sizeof(client)) == -1)
{
 perror("connect");
 return 0;
}
else
{
 printf("testing the connexion ...\n");
        
 if(recv(csock, buffer, 32, 0) == -1)
 {
  perror("connect");
  return 0;
 }
 else
 {
  printf("received message : %s\n",buffer);
        
  if(send(csock, sbuffer, 32, 0) == -1)
  {
   perror("connect");
   return 0;
  }
  else
  {
   printf("send : %s\n",sbuffer);
  }
 }
}
 return 1;
}

int net(void * data)
{
 PPong_Game * game = (PPong_Game *)data;
 
 struct Node * tmp1, *tmp2;
 SDL_Rect rack1_position, ball_position;

while(*(game->play))
{

  tmp1 = (struct Node *)malloc(sizeof(struct Node));
  tmp1->next = NULL;

  tmp2 = (struct Node *)malloc(sizeof(struct Node));
  tmp2->next = NULL;
  
  send(csock, (SDL_Rect *)&game->table.rack2.position, sizeof(SDL_Rect), 0);
  recv(csock, (int *)game->p1, sizeof(int), 0);
  recv(csock, (int *)game->p2, sizeof(int), 0);
  recv(csock, (SDL_Rect *)&ball_position, sizeof(SDL_Rect), 0);
  recv(csock, (SDL_Rect *)&rack1_position, sizeof(SDL_Rect), 0);

  SDL_SemWait(semWrite1); /* ++++++++++++++++++++++++++++++++ */

    tmp1->position = ball_position;
    tmp2->position = rack1_position;
  
    add_Node (&game->buffer1, tmp1); // inline functions to ignore function-call overhead in a critical section!
    add_Node (&game->buffer2, tmp2);
  
  SDL_SemPost(semRead1); /* ++++++++++++++++++++++++++++++++ */

}
} 
