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
#include <arpa/inet.h>

# include "display.h"
# include "moveball.h"
# include "net.h"

static int SDLlibs_init();

SDL_sem * semWrite, * semRead;
extern int ssock, csock;
int main(int argc, char *argv[])
{
 PPong_Game game;

 SDL_Event event;
 SDL_Thread *thread1, *thread2;
 SDL_TimerID timer;
  
 int play = 1, p1 = 0, p2 = 0;
 game.play = &play; // to not use malloc()!
 game.p1 = &p1;
 game.p2 = &p2;


 if(!establish_connection())
	exit(EXIT_FAILURE);

/* SDL initialisation */
if(!SDLlibs_init())
	exit(EXIT_FAILURE);

/* graphic Interface creation */
game.screen            = SDL_SetVideoMode(660, 700, BITBIXEL, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);
create_game_graphicItems(&game);
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
SDL_WM_SetCaption("Player 1 ( P1 )",NULL);
SDL_EnableKeyRepeat(BSPEED, 0);
SDL_ShowCursor(0);

/*** Threads & Semaphores ***/
semWrite = SDL_CreateSemaphore(1);
semRead  = SDL_CreateSemaphore(0);

/* Send : positionRack1 & positionBall / Receive : positionRack2 */
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

			 case SDLK_RIGHT :     if( (game.table.rack1.position.x + game.table.rack1.surface->w)  < (game.table.table.surface->w -5))
						 game.table.rack1.position.x += RSPEED;
		         break;

			 case SDLK_LEFT  :      if(game.table.rack1.position.x > 3)
						  game.table.rack1.position.x -= RSPEED;
			 break;

			 case SDLK_SPACE: 	SDL_RemoveTimer(timer);
                                                timer = SDL_AddTimer(BSPEED ,MoveBall, &game);
			 break;
			
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


    SDL_RemoveTimer(timer);

    SDL_WaitThread(thread2, NULL);
    SDL_WaitThread(thread1, NULL);
    SDL_DestroySemaphore(semWrite);
    SDL_DestroySemaphore(semRead);

    /* free the video memory */
    free_video_memory(&game);

    
    TTF_CloseFont(game.board.police); // police

    Mix_CloseAudio();
    Mix_FreeChunk(game.rack_hit); // sounds
    Mix_FreeChunk(game.touchline_hit);
    
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    /* Shutdown only reception or transmission */
    shutdown(csock, SHUT_RDWR);
    closesocket(ssock);

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
