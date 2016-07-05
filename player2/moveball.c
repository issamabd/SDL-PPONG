# include "game.h"
# include "moveball.h"

static int sens;

Uint32 MoveBall(Uint32 interval, void * data)
{
    PPong_Game * game = (PPong_Game *)data;
     
     int BallCenter   = game->table.ball.position.x + game->table.ball.surface->w/2;
     int limit_rack2  = game->table.rack2.position.x + game->table.rack2.surface->w;
     int limit_rack1  = game->table.rack1.position.x + game->table.rack1.surface->w;
     
     int low = game->table.rack1.position.y;
     int top = game->table.rack2.surface->h + game->table.rack2.position.y;
     int right = game->table.table.surface->w - game->table.ball.surface->w;
     
     int RSection1 = 1*game->table.rack1.surface->w/5;     
     int RSection2 = 2*game->table.rack1.surface->w/5;     
     int RSection3 = 3*game->table.rack1.surface->w/5;     
     int RSection4 = 4*game->table.rack1.surface->w/5;     
                                         
     int tolerence1 = game->table.ball.surface->w/2;
     int tolerence2 = game->table.ball.surface->w/2;

   if (game->table.ball.position.y  + game->table.ball.surface->h == low)
   {
 
     if((BallCenter <= limit_rack1  + tolerence1)&&(BallCenter > game->table.rack1.position.x + RSection4 ))
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 1;}
     if((BallCenter <= game->table.rack1.position.x + RSection4 )&&(BallCenter > game->table.rack1.position.x + RSection3 ))
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 2;}
     if((BallCenter >= game->table.rack1.position.x + RSection2 )&&(BallCenter <= game->table.rack1.position.x + RSection3))
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 3;}
     if((BallCenter >= game->table.rack1.position.x + RSection1 )&&(BallCenter < game->table.rack1.position.x +RSection2))   
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 4;}
     if((BallCenter < game->table.rack1.position.x + RSection1)&&(BallCenter >= game->table.rack1.position.x - tolerence1))  	
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 5;}
     
   }


   if (game->table.ball.position.y == top)
   {
     if((BallCenter <= limit_rack2 + tolerence2)&&(BallCenter > game->table.rack2.position.x + RSection4))      
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 6;}
     if((BallCenter <= game->table.rack2.position.x + RSection4 )&&(BallCenter > game->table.rack2.position.x + RSection3 )) 
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 7;}
     if((BallCenter >= game->table.rack2.position.x + RSection2 )&&(BallCenter <= game->table.rack2.position.x + RSection3)) 
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 8;}
     if((BallCenter >= game->table.rack2.position.x + RSection1 )&&(BallCenter < game->table.rack2.position.x + RSection2))  
	{Mix_PlayChannel(2, game->rack_hit, 0); sens = 9;}
     if((BallCenter < game->table.rack2.position.x + RSection1)&&(BallCenter >= game->table.rack2.position.x - tolerence2))  
	{Mix_PlayChannel(2, game->rack_hit, 0); sens =10;}
   }

   if(game->table.ball.position.x == right) {Mix_PlayChannel(2, game->touchline_hit, 0);}
   if(game->table.ball.position.x == 0)     {Mix_PlayChannel(2, game->touchline_hit, 0);}
   if(game->table.ball.position.y + game->table.ball.surface->h >= game->table.table.surface->h)
   {    
	sens = 0;
        
	(*(game->p2)) ++;
	game->table.ball.position.x = game->table.table.surface->w/2 -game->table.ball.surface->w/2;
	game->table.ball.position.y = game->table.rack2.position.y + game->table.rack2.surface->h;
	game->table.rack1.position.x = game->table.table.surface->w/2 - game->table.rack1.surface->w/2;
	game->table.rack2.position.x = game->table.table.surface->w/2 - game->table.rack2.surface->w/2;
	SDL_SetTimer(0, NULL);
        
   }


   if(game->table.ball.position.y  == 0)
   {
	sens = 0;
	(*(game->p1)) ++;
	game->table.ball.position.x = game->table.table.surface->w/2 -game->table.ball.surface->w/2;
	game->table.ball.position.y = game->table.rack1.position.y - game->table.ball.surface->h;
	game->table.rack1.position.x = game->table.table.surface->w/2 - game->table.rack1.surface->w/2;
	game->table.rack2.position.x = game->table.table.surface->w/2 - game->table.rack2.surface->w/2;
	SDL_SetTimer(0, NULL);
        
   }
  
   switch(sens)
       {                                                                                                              
                       
	case 1:   game->table.ball.position.x += BDIRECTION;                                            
		   game->table.ball.position.y -= BDIRECTION;                                            
	          
                  if(game->table.ball.position.x == right)                                      
		    sens = -1;
	            
        break;
	case -1 :   game->table.ball.position.x-= BDIRECTION;
		    game->table.ball.position.y-= BDIRECTION;
	            
                    if((game->table.ball.position.y == top)&&(BallCenter<= limit_rack2 + tolerence1)&&(BallCenter> game->table.rack2.position.x - tolerence1))
			sens = 10;

        break; 
       	case 2 :   game->table.ball.position.x += BDIRECTION;                        
		   game->table.ball.position.y -= 2*BDIRECTION;
		   if(game->table.ball.position.x == right)
			sens = -2;
		     
		   if((game->table.ball.position.y == top)&&(BallCenter<= limit_rack2 + tolerence1)&&(BallCenter> game->table.rack2.position.x - tolerence1))
			sens = 20;
					     		    
        break;
        case -2 :   game->table.ball.position.x-= BDIRECTION;
		    game->table.ball.position.y-= 2*BDIRECTION;
		    if((game->table.ball.position.y == top)&&(BallCenter<= limit_rack2 + tolerence1)&&(BallCenter> game->table.rack2.position.x - tolerence1))
			sens = 20;
			
	break;
	case 3 :   game->table.ball.position.y -= 2*BDIRECTION;
        if((game->table.ball.position.y == game->table.rack2.position.y + game->table.rack2.surface->h)&&(BallCenter< limit_rack2 + tolerence1)&&(BallCenter> game->table.rack2.position.x - tolerence1))
		      sens = -3;

        break;
	case 4 :    game->table.ball.position.x-= BDIRECTION;                                     
		    game->table.ball.position.y-= 2*BDIRECTION;                                 
		    if(game->table.ball.position.x == 0)
			sens = -4;
		      
		    if((game->table.ball.position.y == top)&&(BallCenter<= limit_rack2 + tolerence1)&&(BallCenter>= game->table.rack2.position.x - tolerence1))
			sens = 40; 
		 
        break;  
	case -4 :   game->table.ball.position.x += BDIRECTION;
		    game->table.ball.position.y -= 2*BDIRECTION ;
		    if((game->table.ball.position.y == top)&&(BallCenter<= limit_rack2 + tolerence1)&&(BallCenter>= game->table.rack2.position.x - tolerence1))
			sens = 40;
   
        break;
	case 5 :   game->table.ball.position.x -= BDIRECTION;
	           game->table.ball.position.y -= BDIRECTION;
		   if(game->table.ball.position.x == 0)                                
			sens = -5;
	            
                     
        break;
	case -5 :   game->table.ball.position.x += BDIRECTION;
		    game->table.ball.position.y -= BDIRECTION;
	            if((game->table.ball.position.y == top)&&(BallCenter<= limit_rack2 + tolerence1)&&(BallCenter>= game->table.rack2.position.x - tolerence1))
		      sens = 50;

	break;                                               
	case 6:   game->table.ball.position.x += BDIRECTION;
		  game->table.ball.position.y += BDIRECTION;
		   if(game->table.ball.position.x == right)                             
		      sens = -6;
		
        break;
	case -6 :   game->table.ball.position.x -= BDIRECTION;
		    game->table.ball.position.y += BDIRECTION;
		 if((game->table.ball.position.y + game->table.ball.surface->w == low )&&(BallCenter>= game->table.rack1.position.x -tolerence2)&&(BallCenter<= limit_rack1  + tolerence2))
		      sens = 60;
		     
        break;
        case 7 :    game->table.ball.position.x += BDIRECTION;
		    game->table.ball.position.y += 2*BDIRECTION;
		    if(game->table.ball.position.x == right)
		      sens = -7;
		  
	       	 if((game->table.ball.position.y + game->table.ball.surface->w == low )&&(BallCenter>= game->table.rack1.position.x -tolerence2)&&(BallCenter<= limit_rack1  + tolerence2))
		     sens = 70;
		    
	break;
	case -7 :    game->table.ball.position.x -= BDIRECTION;
		     game->table.ball.position.y += 2*BDIRECTION;
		 if((game->table.ball.position.y + game->table.ball.surface->w == low )&&(BallCenter>= game->table.rack1.position.x -tolerence2)&&(BallCenter<= limit_rack1  + tolerence2))
		       sens = 70;
	              
        break;
	case 8 :   game->table.ball.position.y += 2*BDIRECTION;
	if((game->table.ball.position.y + game->table.ball.surface->w == game->table.rack1.position.y)&&(BallCenter>= game->table.rack1.position.x - tolerence2)&&(BallCenter<= limit_rack1  +tolerence2))
		     sens = -8;
		      
        break;
	case 9 :    game->table.ball.position.x -= BDIRECTION;
		    game->table.ball.position.y += 2*BDIRECTION;
		if(game->table.ball.position.x == 0)                                          
	 	  sens = -9;
		     
		if((game->table.ball.position.y +game->table.ball.surface->h == low)&&(BallCenter>= game->table.rack1.position.x - tolerence2)&&(game->table.ball.position.x<= limit_rack1 + tolerence2))
		  sens= 90;
		      		  
        break;
	case -9 :  game->table.ball.position.x+= BDIRECTION;
		    game->table.ball.position.y+= 2*BDIRECTION;
		if((game->table.ball.position.y +game->table.ball.surface->h == low)&&(BallCenter>= game->table.rack1.position.x - tolerence2)&&(game->table.ball.position.x<= limit_rack1 + tolerence2))
		  sens= 90;
		      
	break; 
	case 10 :  game->table.ball.position.x -= BDIRECTION;
		   game->table.ball.position.y += BDIRECTION;
		   if(game->table.ball.position.x == 0)                                 
			sens = -10;

		  
        break;
	case -10 :  game->table.ball.position.x+= BDIRECTION;
		    game->table.ball.position.y+= BDIRECTION;
	       if((game->table.ball.position.y +game->table.ball.surface->h == low)&&(BallCenter>= game->table.rack1.position.x - tolerence2)&&(game->table.ball.position.x<= limit_rack1  + tolerence2))
	         sens= 100;
				 
	break;
	default :   sens = 0;
	break;
	}
 
return interval; 
}
