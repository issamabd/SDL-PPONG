#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "net.h"
#include "game.h"


extern SDL_sem * semWrite, * semRead;
int ssock, csock;

int net(void * data)
{

 PPong_Game * game = (PPong_Game *)data;
 int p1, p2;
 SDL_Rect ball_position, rack1_position, rack2_position;
 
 struct Node * tmp = (struct Node *)malloc(sizeof(struct Node));
   
 while(*(game->play))
 {
     
  recv(csock, (SDL_Rect *)&rack2_position, sizeof(SDL_Rect), 0);
         
  SDL_SemWait(semWrite);/* ++++++++++++++++++++++++++++++++ */

    p1 = (*game->p1);
    p2 = (*game->p2);
    ball_position = game->table.ball.position;
    rack1_position = game->table.rack1.position;
    
    tmp->position = rack2_position;
    tmp->next = NULL;

    add_Node (&game->buffer, tmp); // inline function ..
    
  SDL_SemPost(semRead);/* ++++++++++++++++++++++++++++++++ */
  
  send(csock, (int *)&p1, sizeof(int), 0);
  send(csock, (int *)&p2, sizeof(int), 0);
  send(csock, (SDL_Rect *)&ball_position,  sizeof(SDL_Rect), 0);
  send(csock, (SDL_Rect *)&rack1_position, sizeof(SDL_Rect), 0);
  
 }
 
 //free(tmp);
 return 1; 
}  

int establish_connection(char *ip, int port)
{
 char buffer[32] = "ready ?";
 char sbuffer[32];
 struct sockaddr_in server, client;
 socklen_t client_size ;

/* Open a server socket */
client_size = sizeof(client);

printf("Configuring the connection ...\n");        
ssock = socket(AF_INET, SOCK_STREAM, 0);

if (ssock < 0)
{
 perror("socket");
 return 0;
}
else
{
  /*Setting the address (port + IP @) of the server socket */
  server.sin_addr.s_addr    = inet_addr(ip);  /* IP @ of the server */ 
  server.sin_family         = AF_INET;                  		/* Address format that goes with the internet mamespace (domain) */ 
  server.sin_port           = htons(port);                		/* Port number : telnet protocol */            
                
 /* Assigning the adress to the server socket */
 printf("Binding the adress to the server (player1) socket...\n");

 if(bind(ssock, (struct sockaddr*)&server, sizeof(server)) < 0)
 {
  perror("bind");
  return 0;
 }           	   
 else
 {         
  printf("Establishing the connection ...\n");
          
  if(listen(ssock, 1) < 0)
  {
   perror("listen");
   return 0;
  } 
  else
  {
   printf("Waiting for player 2 to connect ...\n");        
            
   csock = accept(ssock, (struct sockaddr*)&client, &client_size);
   if(csock == -1)
   {
    printf("No connection request ...\n");
    return 0;
   }
   else
   {
    printf("Player 2 try to connect ...\n");
    printf("Connection request accepted ...\n");
    printf("Testing the connexion ...\n");
      
    if(send(csock, buffer, 32, 0) == -1)
    {
     perror("send");
     return 0;
    }
    else
    {
     printf("send message : %s\n",buffer);

     if(recv(csock, sbuffer, 32, 0) == -1)
     {
      perror("recv");
      return 0;
     }
     else
     {
      printf("received message : %s\n", sbuffer);
      printf("The connection was tested succefully ...\n");  
     }
    }
   }         
  }
 }
}
}


