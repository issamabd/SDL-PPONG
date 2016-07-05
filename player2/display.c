#include <SDL/SDL_image.h>
#include "display.h"

int create_game_graphicItems(PPong_Game * game)
{

/* the table */
game->table.table.surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 
                                                 640,                   /* width */
                                                 game->screen->h -60,   /* height */ 
                                                 BITBIXEL,              /* resolution or depth in bit per pixel */
                                                 0, 0, 0, 0             /* RGBA mask: Rmask, Gmask, Bmask, Amask */
                                                );

if(!game->table.table.surface)
    return 0;

game->table.net.surface = SDL_CreateRGBSurface(SDL_HWSURFACE, game->table.table.surface->w, 
                            1,BITBIXEL, 0, 0, 0, 0);

if(!game->table.net.surface)
    return 0;

game->table.leftline.surface  = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 
                            game->table.table.surface->h-1,  BITBIXEL, 0, 0, 0, 0);

if(!game->table.leftline.surface)
    return 0;

game->table.rightline.surface  = SDL_CreateRGBSurface(SDL_HWSURFACE, 1,
                            game->table.table.surface->h-1,  BITBIXEL, 0, 0, 0, 0);

if(!game->table.rightline.surface)
    return 0;

game->table.topline.surface  = SDL_CreateRGBSurface(SDL_HWSURFACE, game->table.table.surface->w-1,
                            1,  BITBIXEL, 0, 0, 0, 0);

if(!game->table.topline.surface)
    return 0;

game->table.bottomline.surface  = SDL_CreateRGBSurface(SDL_HWSURFACE, game->table.table.surface->w,
                            1,  BITBIXEL, 0, 0, 0, 0);

if(!game->table.bottomline.surface)
    return 0;

/* Images */
game->table.ball.surface  = IMG_Load("data/ball.png");

if(!game->table.ball.surface)
    return 0;

game->table.rack1.surface = IMG_Load("data/rack.png");

if(!game->table.rack1.surface)
    return 0;

game->table.rack2.surface = IMG_Load("data/rack.png");

if(!game->table.rack2.surface)
    return 0;

/* The Score Board */
game->board.board.surface     = SDL_CreateRGBSurface(SDL_HWSURFACE, 640,
                                                     30,  BITBIXEL, 0, 0, 0, 0);

if(!game->board.board.surface)
    return 0;

return 1;

}

void set_graphicItems_positions(PPong_Game * game)
{

 game->table.table.position.x = game->screen->w/2 - game->table.table.surface->w/2; 
 game->table.table.position.y = 50;

 game->board.board.position.x = game->screen->w/2 - game->table.table.surface->w/2;
 game->board.board.position.y = 10;

 game->table.net.position.x = 0;
 game->table.net.position.y = game->table.table.surface->h/2;

 game->table.rightline.position.x = 0;
 game->table.rightline.position.x = 0;

 game->table.leftline.position.x = game->table.table.surface->w - 1;
 game->table.leftline.position.y = 0;

 game->table.topline.position.x  = 1;
 game->table.topline.position.y  = 0;


 game->table.bottomline.position.x  = 0;
 game->table.bottomline.position.y  = game->table.table.surface->h - 1;

 game->table.rack1.position.x = game->table.table.surface->w/2 - game->table.rack1.surface->w/2;
 game->table.rack1.position.y = game->table.table.surface->h - 
                    game->table.rack1.surface->h -3 - game->table.ball.surface->h;

 game->table.rack2.position.x = game->table.table.surface->w/2 - game->table.rack2.surface->w/2;
 game->table.rack2.position.y =  3 + game->table.ball.surface->h;

 game->table.ball.position.x = game->table.table.surface->w/2 - game->table.ball.surface->w/2;
 game->table.ball.position.y = game->table.rack1.position.y - game->table.ball.surface->h;

}

int display(PPong_Game * game)
{
  int ticks;
  char clock[10], p1_p2[20];

/* Render the borad is different TTF items */
  // the title
  game->board.title.surface  = TTF_RenderText_Blended(game->board.police, "PING-PONG", GREEN);
  game->board.title.position.x = game->board.board.surface->w/2 - game->board.title.surface->w/2;
  game->board.title.position.y = game->board.board.surface->h/2 - game->board.title.surface->h/2;
  
  // the time
  ticks = SDL_GetTicks()/1000; 
  sprintf(clock,"%02d:%02d:%02d",ticks/3600, (ticks%3600)/60, (ticks%3600)%60);
  game->board.time.surface = TTF_RenderText_Blended(game->board.police, clock, GREEN); 
  game->board.time.position.x = game->board.board.surface->w - game->board.time.surface->w -10;
  game->board.time.position.y = game->board.board.surface->h/2 - game->board.time.surface->h/2;

  // the score
  sprintf(p1_p2,"P1 - P2 : %2d - %2d",*(game->p1),*(game->p2));
  game->board.score.surface = TTF_RenderText_Blended(game->board.police, p1_p2, GREEN);
  game->board.score.position.x = 10;
  game->board.score.position.y = game->board.board.surface->h/2 - game->board.score.surface->h/2;
  
/* Fill the board with color in the memory */
  SDL_FillRect(game->board.board.surface,   NULL, SDL_MapRGBA(game->board.board.surface->format,   0, 0, 0, 0));
    
/* Fill The table's different surface with colors in memory */
  SDL_FillRect(game->table.table.surface,         NULL, SDL_MapRGBA(game->table.table.surface ->format, 0, 0, 0, 0));
  SDL_FillRect(game->table.net.surface,           NULL, SDL_MapRGBA(game->table.net.surface->format, 15, 15, 15, 0));
  SDL_FillRect(game->table.rightline.surface,     NULL, SDL_MapRGBA(game->table.rightline.surface->format, 15, 15, 15, 0));
  SDL_FillRect(game->table.leftline.surface,      NULL, SDL_MapRGBA(game->table.leftline.surface->format, 15, 15, 15, 0));
  SDL_FillRect(game->table.topline.surface,       NULL, SDL_MapRGBA(game->table.topline.surface->format, 15, 15, 15, 0));
  SDL_FillRect(game->table.bottomline.surface,    NULL, SDL_MapRGBA(game->table.bottomline.surface->format, 15, 15, 15, 0));

/* Blit score board's graphic items on the board iteself */  
  SDL_BlitSurface(game->board.title.surface,      NULL, game->board.board.surface, &game->board.title.position);
  SDL_BlitSurface(game->board.time.surface,	  NULL, game->board.board.surface, &game->board.time.position);
  SDL_BlitSurface(game->board.score.surface,      NULL, game->board.board.surface,   &game->board.score.position);

/* Blit the table's graphic items on the table itself */  
  SDL_BlitSurface(game->table.ball.surface,       NULL, game->table.table.surface, &game->table.ball.position); 
  SDL_BlitSurface(game->table.rack1.surface,      NULL, game->table.table.surface, &game->table.rack1.position);
  SDL_BlitSurface(game->table.rack2.surface,      NULL, game->table.table.surface, &game->table.rack2.position);
  SDL_BlitSurface(game->table.rightline.surface,  NULL, game->table.table.surface, &game->table.rightline.position);
  SDL_BlitSurface(game->table.leftline.surface,   NULL, game->table.table.surface, &game->table.leftline.position);
  SDL_BlitSurface(game->table.topline.surface,    NULL, game->table.table.surface, &game->table.topline.position);
  SDL_BlitSurface(game->table.bottomline.surface, NULL, game->table.table.surface, &game->table.bottomline.position);
  SDL_BlitSurface(game->table.net.surface,        NULL, game->table.table.surface, &game->table.net.position); 
  
/* Blit the board and the table surfaces on the screen */  
  SDL_BlitSurface(game->board.board.surface,      NULL, game->screen,  &game->board.board.position); 	      
  SDL_BlitSurface(game->table.table.surface,      NULL, game->screen,  &game->table.table.position);
  
/* Flip the screen and visualize the game's graphical interface */
  SDL_Flip(game->screen);
   
 return 1; 
} 
 
 
void free_video_memory( PPong_Game * game)
{
    SDL_FreeSurface(game->table.rack1.surface);
    SDL_FreeSurface(game->table.rack2.surface);
    SDL_FreeSurface(game->table.ball.surface);
    SDL_FreeSurface(game->table.topline.surface);
    SDL_FreeSurface(game->table.bottomline.surface);
    SDL_FreeSurface(game->table.leftline.surface);
    SDL_FreeSurface(game->table.rightline.surface);
    SDL_FreeSurface(game->table.net.surface);
    SDL_FreeSurface(game->table.table.surface); // table
    
    SDL_FreeSurface(game->board.time.surface);
    SDL_FreeSurface(game->board.score.surface);
    SDL_FreeSurface(game->board.title.surface);
    SDL_FreeSurface(game->board.board.surface); // board
 }
