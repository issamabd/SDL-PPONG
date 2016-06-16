/*

SDL-PPONG: An implementation of the Table Tennis game using C and SDL.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

Copyright (C) 2010-2016 Issam Abdallah, Tunisia
Email:iabdallah@yandex.com
Web Site: issamabd.com
*/

#include <getopt.h>

#include "display.h"
#include "net.h"
#include "buffer.h"

static int SDLlibs_init();
static void print_usage (char * program_name, FILE * stream, int exit_code);

int csock;
SDL_sem * semWrite1, * semRead1;  

int main(int argc, char *argv[])
{
 PPong_Game game;
 
 SDL_Event event;
 SDL_Thread *thread1, *thread2;

 int play = 1, p1 = 0, p2 = 0;
 game.play = &play; // to not use malloc()!
 game.p1 = &p1;
 game.p2 = &p2;

 const char* const short_options = "hi:p:";
 const struct option long_options[] = {
     
     {"help", 0, NULL, 'h'},  
     {"ip", 1, NULL, 'i'},
     {"port", 1, NULL, 'p'},
     {NULL, 0, NULL, 0}
      
 };

 char * program_name = argv[0];
 int next_option;
 const char *port = NULL;
 char *ip = NULL;

 /* scan command options (refer to GNU getopt.h API) */
 do{
  next_option = getopt_long(argc, argv, short_options, long_options, NULL);   
  switch(next_option)
  {
      case 'h': print_usage(program_name, stdout, EXIT_SUCCESS);
      
      case 'i': ip = (char *)optarg;
      break;
      
      case 'p': port = optarg;
      break;
      
      case '?': print_usage(program_name, stderr, EXIT_FAILURE);
    
      case -1:
      break;
      default: abort();
  }
}while(next_option != -1);
 
/* verify that IP:PORT are scanned */
if(!ip || !port)
    print_usage(program_name, stderr, EXIT_FAILURE);

/* Establish connection with player1 */
if(!establish_connection(ip, atoi(port)))
    exit(EXIT_FAILURE);
 
if(!SDLlibs_init())
    exit(EXIT_FAILURE);

initialise_Buffer (&game.buffer1); // ball positions
initialise_Buffer (&game.buffer2); // Rack1 positions

/* screen */
game.screen   = SDL_SetVideoMode(660, 700, BITBIXEL, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);

if(!create_game_graphicItems(&game))
    exit(EXIT_FAILURE);

set_graphicItems_positions(&game);

/* police */
game.board.police = TTF_OpenFont("data/digital.ttf", 20);

/* sounds */
Mix_OpenAudio(22050, AUDIO_U8, 1, 512);

game.rack_hit = Mix_LoadWAV("data/hit.wav");
game.touchline_hit = Mix_LoadWAV("data/mur.wav");

Mix_VolumeChunk(game.rack_hit, VOLUME);
Mix_VolumeChunk(game.touchline_hit, VOLUME);
	
/* Keyboard & Mouse */
 SDL_WM_SetCaption("Player 2 ( P2 )",NULL);
 SDL_EnableKeyRepeat(BSPEED, 0);
 SDL_ShowCursor(0);

/*** Threads & Semaphores ***/
 semWrite1 = SDL_CreateSemaphore(1);
 semRead1  = SDL_CreateSemaphore(0);

/*Send : positionRack2 / Receive : positionRack1 & positionBall */
 thread1 = SDL_CreateThread(net, &game);

/* Display */
 thread2 = SDL_CreateThread(display, &game);

while(play)
{
    /* SDL_MUSTLOCK(surface); */
    SDL_WaitEvent(&event);
    switch(event.type)
    {
 	case SDL_QUIT: play = 0;
 	break;

        case SDL_KEYDOWN:

	                switch(event.key.keysym.sym)
		        {		
			 case SDLK_RIGHT    :	if( (game.table.rack2.position.x + game.table.rack2.surface->w)  < (game.table.table.surface->w -5))
						 game.table.rack2.position.x += RSPEED;
			 break;

			 case SDLK_LEFT	:	 if(game.table.rack2.position.x > 3)
						  game.table.rack2.position.x -= RSPEED;
			 break;

			 /* End the game and Quit */
			 case SDLK_q:	play = 0;
                         break;


			 default:
			 break;
		      }

      break;
      default :
      break;
    }

}

    SDL_WaitThread(thread2, NULL);
    SDL_WaitThread(thread1, NULL);    
    SDL_DestroySemaphore(semWrite1);
    SDL_DestroySemaphore(semRead1);

    /* free the video memory */
    free_video_memory(&game);
    
    TTF_CloseFont(game.board.police); // police

    Mix_CloseAudio();
    Mix_FreeChunk(game.rack_hit); // sounds
    Mix_FreeChunk(game.touchline_hit);
    
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    closesocket(csock);
    
    free_Buffer(&game.buffer1);
    free_Buffer(&game.buffer2);
    
    return EXIT_SUCCESS;
}


int SDLlibs_init()
{
/* initialisation of SDL */
  if( SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
	fprintf(stderr, "SDL_Init Error : %s\n", SDL_GetError());
	return 0;
 	}

/* initialisation of SDL_ttf */
  if(TTF_Init() == -1)
    {
	fprintf(stderr, "TTF_Init Error : %s\n", TTF_GetError());
	return 0;
	}
/* initialisation of SDL_mixer */
  if(Mix_Init(0) == -1)
    {
	fprintf(stderr, "TTF_Init Error : %s\n", Mix_GetError());
	return 0;
	}

	return 1;
}

static void print_usage (char * program_name, FILE * stream, int exit_code)
{
    fprintf(stream, "Usage: %s [-i player1_address] [-p port]\n\n", program_name);
    fprintf(stream, "  -h, --help\t\t Display this usage information.\n");
    fprintf(stream, "  -i, --ip\t\t IP address of player1.\n");
    fprintf(stream, "  -p, --port\t\t Port number to use.\n");
    exit(exit_code);
}

