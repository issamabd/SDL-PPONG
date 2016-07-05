#ifndef GAME_H
#define GAME_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


#define RSPEED        5   
#define BSPEED        8 
#define VOLUME      100 	/* Volume 0..128 */

typedef struct GraphicItem
{
    SDL_Surface * surface;
    SDL_Rect position;
}PPong_GraphicItem;

typedef struct Table
{
    PPong_GraphicItem table;
    PPong_GraphicItem ball;
    PPong_GraphicItem rack1, rack2;
    PPong_GraphicItem net;
    PPong_GraphicItem topline, bottomline;
    PPong_GraphicItem rightline, leftline;    
}PPong_Table;

typedef struct Board
{
    PPong_GraphicItem board;
    PPong_GraphicItem title;
    PPong_GraphicItem time;
    PPong_GraphicItem score;
    TTF_Font *police;
}PPong_Board;

typedef struct Game
{
    SDL_Surface * screen;
    PPong_Table table;
    PPong_Board board;
    Mix_Chunk * rack_hit;
    Mix_Chunk * touchline_hit;
    int * play, * p1, * p2;
}PPong_Game;

#endif // GAME_H
