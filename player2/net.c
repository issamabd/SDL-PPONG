#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "net.h"
#include "game.h"

extern int csock;
PPong_FIFO fifo1;
extern SDL_sem * semWrite1, * semRead1;  

int establish_connection()
{
   struct sockaddr_in client;
    
 char buffer[32];
 char sbuffer[32]= "Player 2 is ready ..";
   
/* Open a client socket */
printf("Configuring the connexion ...\n");
csock = socket(AF_INET, SOCK_STREAM, 0);

/* Setting the address (port + IP @) of the server socket */     
client.sin_addr.s_addr = inet_addr("127.0.0.1");
client.sin_family = AF_INET;
client.sin_port = htons(23);

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
 
 struct Node * tmp;
 SDL_Rect ball;

while(*(game->play))
{

  send(csock, (SDL_Rect *)&game->table.rack2.position, sizeof(SDL_Rect), 0);
  recv(csock, (int *)game->p1, sizeof(int), 0);
  recv(csock, (int *)game->p2, sizeof(int), 0);
  recv(csock, (SDL_Rect *)&ball, sizeof(SDL_Rect), 0);
  recv(csock, (SDL_Rect *)&game->table.rack1.position, sizeof(SDL_Rect), 0);

  tmp = (struct Node *)malloc(sizeof(struct Node));
  tmp->position = ball;
  tmp->next = NULL;

 SDL_SemWait(semWrite1); /* ++++++++++++++++++++++++++++++++ */
 
  if(fifo1.head == NULL)
  {
	fifo1.head = tmp;
	fifo1.tail  = tmp;
	fifo1.count++;
  }
  else
  {
        fifo1.tail->next = tmp;
	fifo1.tail = tmp;      
	fifo1.count++;
  }

 SDL_SemPost(semRead1); /* ++++++++++++++++++++++++++++++++ */

}
} 

void initialise_FIFO ()
{
 fifo1.count = 0;
 fifo1.head = NULL;
 fifo1.tail = NULL;
}

void free_FIFO()
{
       struct Node* tmp;

   while (fifo1.head != NULL)
    {
       tmp = fifo1.head;
       fifo1.head = fifo1.head->next;
       free(tmp);
    }
}
