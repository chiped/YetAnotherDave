#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "level01.h"
#include "player.h"
#include <string>


int main( int argc, char* args[] )
{
	
	//Start	SDL
	SDL_Init( SDL_INIT_EVERYTHING );	
	TTF_Init();

	//Set window caption
	SDL_WM_SetCaption("Yet Another Dave!", NULL);

	SDL_Surface *buffer = NULL;
	SDL_Surface *message = NULL;

	bool fullscreen = false;

	if( fullscreen == true )	
		buffer = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_FULLSCREEN);
	else
		buffer = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	
	SDL_Event event ;

	Game *G1 = new Game();
	player *P1 = new player();
	
	int times=0;
	

	while(event.type != SDL_QUIT)
	{
		SDL_PollEvent( &event );
		//If a key was pressed 
		if( event.type == SDL_KEYDOWN )
		{
			//Set the proper message surface 
			switch( event.key.keysym.sym ) 
			{ 
				case SDLK_UP:   if(times==0&&G1->jump==0) times=10;//P1->movePlayer(G1, 2);
								G1->jump=1;
								break; 
				case SDLK_DOWN:	P1->movePlayer(G1, 3);		
								break; 
				case SDLK_LEFT: P1->movePlayer(G1, 0);	
								break; 
				case SDLK_RIGHT: P1->movePlayer(G1, 1);
								break;
				
				
			}			
		}
		if(times>0)
		{
			times--;
			P1->movePlayer(G1, 2);
		}
		else
		{
			G1->jump=1;
			P1->movePlayer(G1, 3);	
		}
		G1->blitBackground( buffer );				
		G1->blitExtra( buffer );
		P1->blitPlayer( buffer );
		G1->blitMessage( buffer );
		SDL_Flip( buffer );

		SDL_Delay(100);
		if(G1->end(P1))
			break;		
	}
	G1->blitBackground( buffer );
	G1->blitExtra( buffer );
	SDL_Flip( buffer );
	static const SDL_Color WHITE = {255,255,255} ;
	TTF_Font *font;
	SDL_Color textColor;	
	font = TTF_OpenFont( "comic.ttf", 24 );
	textColor = WHITE;
	SDL_Rect *r1=new SDL_Rect();
	r1->x=296; r1->y=228;
	message = TTF_RenderText_Solid( font, "GAME OVER", textColor );
	SDL_BlitSurface(message, NULL, buffer, r1);
	SDL_Flip( buffer );
	r1->x=250; r1->y=260;
	message = TTF_RenderText_Solid( font, "Final Score: ", textColor );
	SDL_BlitSurface(message, NULL, buffer, r1);
	SDL_Flip( buffer );
	char buff[10];
	_itoa_s(G1->score,buff,10);
	r1->x=400; r1->y=260;
	message = TTF_RenderText_Solid( font, buff, textColor );
	SDL_BlitSurface(message, NULL, buffer, r1);
	SDL_Flip( buffer );
	r1->x=50; r1->y=0;
	message = TTF_RenderText_Solid( font, "Thank You for Playing", textColor );
	SDL_BlitSurface(message, NULL, buffer, r1);
	SDL_Flip( buffer );
	r1->x=0; r1->y=28;
	message = TTF_RenderText_Solid( font, "Game Developed by Chinmay Pednekar", textColor );
	SDL_BlitSurface(message, NULL, buffer, r1);
	SDL_Flip( buffer );
	while(event.type != SDL_QUIT)
		SDL_PollEvent( &event );

	/*SDL_Rect *bcrop=new SDL_Rect();
	bcrop->x=0;
	bcrop->y=0;
	bcrop->h=480;
	bcrop->w=640;
		
	SDL_Rect *crop=new SDL_Rect();
	crop->x=96;
	crop->y=0;
	crop->h=32;
	crop->w=24;
	
	SDL_Rect *locn=new SDL_Rect();
	locn->x=32;
	locn->y=416;
	locn->h=32;
	locn->w=24;
	
	int lpos=24,rpos=72;
		
	while(event.type != SDL_QUIT)
	{
		SDL_PollEvent( &event );
		//If a key was pressed 
		if( event.type == SDL_KEYDOWN )
		{
			//Set the proper message surface 
			switch( event.key.keysym.sym ) 
			{ 
				case SDLK_UP: 
					if(locn->y>72) locn->y-=8;
								break; 
				case SDLK_DOWN:
					if(locn->y<416) locn->y+=8;
								break; 
				case SDLK_LEFT: 
					if(locn->x>240) locn->x-=8;
					else
					{
						if(bcrop->x>0) bcrop->x-=8;
						else if(locn->x>32) locn->x-=8;
					}
					if(lpos==0)
					{
						lpos=1;
						crop->x=0;
					}
					else
					{
						lpos=0;
						crop->x=24;
					}
								break; 
				case SDLK_RIGHT:
					if(locn->x<320) locn->x+=8;
					else
					{
						if(bcrop->x<640) bcrop->x+=8;
						else if(locn->x<584) locn->x+=8;
					}
					if(rpos==0)
					{
						rpos=1;
						crop->x=96;
					}
					else
					{
						rpos=0;
						crop->x=72;
					}
								break; 
			}
			
			
		}
		 
			SDL_BlitSurface( back, bcrop, buffer, NULL );
			SDL_BlitSurface( image, crop, buffer, locn );
			SDL_Flip( buffer );
	
			SDL_Delay(100);
		

			SDL_BlitSurface( back, bcrop, buffer, NULL );
			SDL_Flip( buffer );

	}
	*/
	/* Free up space afterwards */
	SDL_FreeSurface( buffer );
	
	//Quit 	SDL
	SDL_Quit();
	return 0;
}