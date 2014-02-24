#ifndef _level01_
#define _level01_


#include "SDL.h"
#include "SDL_ttf.h"
#include "Playar.h"

static const SDL_Color WHITE = {255,255,255} ;

struct gem
{
	int score;
	SDL_Rect *locn;
	SDL_Rect *type;
};

class Game
{
public:
	
	SDL_Surface *background;
	SDL_Surface *Extra;	
	SDL_Surface *message;

	TTF_Font *font;
	SDL_Color textColor;
	//SDL_Surface *black;

	SDL_Rect *window;
	SDL_Rect *eframe;
	SDL_Rect *elocn;
	SDL_Rect *walls[26];
	int wall, jump, score, gems;
	bool cup;
	struct gem *g1[10];

	Game();
	void writeBackground(SDL_Surface *);
	void blitBackground(SDL_Surface *);
	void blitExtra(SDL_Surface *);
	void blitMessage(SDL_Surface *);
	//void writeScore();
	//void blitGem();
	bool possible(Playar *,int);
	void init_walls();
	void init_gems();
	bool end(Playar *);
};

Game::Game()
{
	background = SDL_LoadBMP( "level01.BMP" );

	Extra = SDL_LoadBMP( "Extra.BMP" );
	Uint32 colorKey = SDL_MapRGB( Extra->format, 0xFF, 0, 0xFF );
	SDL_SetColorKey(Extra, SDL_SRCCOLORKEY, colorKey );

	//black = SDL_LoadBMP( "black.BMP" );

	font = TTF_OpenFont( "comic.ttf", 24 );
	if(font==NULL) return;
	textColor = WHITE;

	window = new SDL_Rect();
	elocn = new SDL_Rect();
	eframe = new SDL_Rect();
	jump=0;

	wall=26; gems=10;score=0;
	cup=false;

	window->x=0;
	window->y=0;
	window->h=480;
	window->w=640;

	elocn->x=648;
	elocn->y=384;
	elocn->w=32;
	elocn->h=32;

	eframe->x=0;
	eframe->y=0;
	eframe->h=32;
	eframe->w=32;

	init_walls();
	init_gems();
}

/*void Game::writeScore()
{
	SDL_Rect *r1 = new SDL_Rect();
	SDL_Rect *locn = new SDL_Rect();
	r1->y=32;
	r1->h=24;
	r1->w=16;
	locn->y=240;
	locn->h=24;
	locn->w=16;

	int digit = i_score%10;
	r1->x=digit*16;
	locn->x=576;	
	SDL_BlitSurface( black, NULL, buffer, locn );
	SDL_BlitSurface( score, r1, buffer, locn );

	digit = (i_score/10)%10;
	r1->x=digit*16;
	locn->x=556;	
	SDL_BlitSurface( black, NULL, buffer, locn );	
	SDL_BlitSurface( score, r1, buffer, locn );

	digit = (i_score/100)%10;
	r1->x=digit*16;
	locn->x=536;		
	SDL_BlitSurface( black, NULL, buffer, locn );
	SDL_BlitSurface( score, r1, buffer, locn );

	delete r1;
	delete locn;
}*/

void Game::writeBackground(SDL_Surface *buffer)
{
	//Score writing goes here
	SDL_BlitSurface( background, NULL, buffer, NULL );
}

void Game::blitMessage(SDL_Surface *buffer)
{
	SDL_Rect *r1=new SDL_Rect();
	r1->x=450; r1->y=0;
	char s[] = "Score: ";
	message = TTF_RenderText_Solid( font, s, textColor );
	SDL_BlitSurface(message, NULL, buffer, r1);
	char buff[10];
	_itoa_s(score,buff,10);
	message = TTF_RenderText_Solid( font, buff, textColor );
	r1->x=550;
	SDL_BlitSurface(message, NULL, buffer, r1);
	if(cup)
	{
		message = TTF_RenderText_Solid( font, "Go through the door", textColor );
		r1->x=200;
		r1->y=30;
		SDL_BlitSurface(message, NULL, buffer, r1);
	}
}

void Game::blitExtra(SDL_Surface *buffer)
{
	//Gems, Cup and Door

	for(int i=1;i<gems;i++)
	{
		if(g1[i]->score>0)
		{
			elocn->x=g1[i]->locn->x-window->x;
			elocn->y=g1[i]->locn->y-window->y;
			SDL_BlitSurface( Extra, g1[i]->type, buffer, elocn );
		}
	}
	
	if(!cup)
	{
		eframe->x=128;
		elocn->x=896-window->x;
		elocn->y=288-window->y;
		SDL_BlitSurface( Extra, eframe, buffer, elocn );
		eframe->x=64;
	}
	else
		eframe->x=96;
	elocn->x=648-window->x;
	elocn->y=384-window->y;
	SDL_BlitSurface( Extra, eframe, buffer, elocn );
}
void Game::blitBackground(SDL_Surface *buffer)
{
	SDL_Rect * r1 = new SDL_Rect();
	r1->x=0;
	r1->y=60;
	r1->h=420;
	r1->w=640;
	SDL_Rect * r2 = new SDL_Rect();
	r2->x=window->x;
	r2->y=60+window->y;
	r2->h=420;
	r2->w=640;
	SDL_BlitSurface( background, r2, buffer, r1 );
	r2->x=64;
	r2->y=96;
	r2->h=60;
	r2->w=640;
	r1->y=0;
	SDL_BlitSurface(background, r2, buffer, r1);
}

/*void Game::blitGem()
{
	int velocity = (i_score/10)%50;
	switch (v)
	{
		case 0: if(gemlocn->x<500-velocity-35) 
				{
						gemlocn->x+=velocity; 
						break;
				}
				else v=rand()%2?2:3;
		case 1: if(gemlocn->x>velocity) 
				{
						gemlocn->x-=velocity;
						break;
				}
				else v=rand()%2?2:3;
		case 2: if(gemlocn->y<480-velocity-35)
				{
					gemlocn->y+=velocity;
					break;
				}
				else v=rand()%2;
		case 3: if(gemlocn->y>velocity)
				{
					gemlocn->y-=velocity;
					break;
				}
				else v=rand()%2;
	}

	SDL_BlitSurface( gem, gemdim, buffer, gemlocn );
}*/

bool Game::possible(Playar *p, int m)
{
	//collision logic
	int topA, topB, bottomA, bottomB, leftA, leftB, rightA, rightB;
	leftA=window->x+p->locn->x;
	rightA=window->x+p->locn->x+p->locn->w;
	topA=p->locn->y;
	bottomA=p->locn->y+p->locn->h;
	switch(m)
	{
		//left
		case 0:	for(int i=1; i<wall; i++)
				{
					rightB=walls[i]->x+walls[i]->w;
					leftB=walls[i]->x;
					bottomB=walls[i]->y+walls[i]->h;
					topB=walls[i]->y;
					if(!( bottomA<=topB  ||  topA>=bottomB  ||  leftA-8>=rightB  ||  rightA<=leftB ))
						return false;
				}
				if(p->locn->x < 320 )
				{
					if(window->x>0)
					{
						window->x-=8;
						return false;
					}
				}
				break;

		//right
		case 1:	for(int i=0; i<wall; i++)
				{
					rightB=walls[i]->x+walls[i]->w;
					leftB=walls[i]->x;
					bottomB=walls[i]->y+walls[i]->h;
					topB=walls[i]->y;
					if(!( bottomA<=topB  ||  topA>=bottomB  ||  leftA>=rightB  ||  rightA+8<=leftB ))
						return false;
				}
				if(p->locn->x > 320 )
				{
					if(window->x<320)
					{
						window->x+=8;
						return false;
					}
				}
				break;

		//up
		case 2: for(int i=0; i<wall; i++)
				{
					rightB=walls[i]->x+walls[i]->w;
					leftB=walls[i]->x;
					bottomB=walls[i]->y+walls[i]->h;
					topB=walls[i]->y;
					if(!( bottomA<=topB  ||  topA-8>=bottomB  ||  leftA>=rightB  ||  rightA<=leftB ))
						return false;
				}
				break;

		//down
		case 3: for(int i=0; i<wall; i++)
				{
					rightB=walls[i]->x+walls[i]->w;
					leftB=walls[i]->x;
					bottomB=walls[i]->y+walls[i]->h;
					topB=walls[i]->y;
					if(!( bottomA+8<=topB  ||  topA>=bottomB  ||  leftA>=rightB  ||  rightA<=leftB ))
					{
						jump=0;
						return false;						
					}
				}
				
				break;

	}
	for(int i=1;i<gems;i++)
	{
		if(g1[i]->score>0)
		{
			rightB=g1[i]->locn->x+g1[i]->locn->w;
			topB=g1[i]->locn->y;
			leftB=g1[i]->locn->x;
			bottomB=g1[i]->locn->y+g1[i]->locn->h;
			if(!( bottomA<=topB  ||  topA>=bottomB  ||  leftA>=rightB  ||  rightA<=leftB ))
			{
				score+=g1[i]->score;
				g1[i]->score=0;
			}
		}
	}
	if(!cup)
	{
		rightB=896+32;
		topB=288;
		leftB=896;
		bottomB=288+32;
		if(!( bottomA<=topB  ||  topA>=bottomB  ||  leftA>=rightB  ||  rightA<=leftB ))
		{
			cup=true;
			score+=100;
		}
	}
	return true;
}

bool Game::end(Playar *p)
{
	if(cup &&  p->locn->y==384 && p->locn->x==(656-window->x))
		return true;
	return false;
}

void Game::init_walls()
{
	walls[0]=new SDL_Rect();
	walls[0]->x=0;
	walls[0]->y=0;
	walls[0]->h=448;
	walls[0]->w=32;

	walls[6]=new SDL_Rect();
	walls[6]->x=0;
	walls[6]->y=0;
	walls[6]->h=448;
	walls[6]->w=32;

	walls[1]=new SDL_Rect();
	walls[1]->x=0;
	walls[1]->y=64;
	walls[1]->h=32;
	walls[1]->w=960;

	walls[2]=new SDL_Rect();
	walls[2]->x=0;
	walls[2]->y=416;
	walls[2]->h=32;
	walls[2]->w=960;

	walls[3]=new SDL_Rect();
	walls[3]->x=928;
	walls[3]->y=96;
	walls[3]->h=448;
	walls[3]->w=32;

	walls[4]=new SDL_Rect();
	walls[4]->x=32;
	walls[4]->y=128;
	walls[4]->h=32;
	walls[4]->w=32;

	walls[5]=new SDL_Rect();
	walls[5]->x=32;
	walls[5]->y=352;
	walls[5]->h=32;
	walls[5]->w=32;

	walls[7]=new SDL_Rect();
	walls[7]->x=96;
	walls[7]->y=160;
	walls[7]->h=32;
	walls[7]->w=32;

	walls[8]=new SDL_Rect();
	walls[8]->x=96;
	walls[8]->y=288;
	walls[8]->h=32;
	walls[8]->w=32;

	walls[9]=new SDL_Rect();
	walls[9]->x=160;
	walls[9]->y=224;
	walls[9]->h=32;
	walls[9]->w=32;

	walls[10]=new SDL_Rect();
	walls[10]->x=224;
	walls[10]->y=160;
	walls[10]->h=32;
	walls[10]->w=32;

	walls[11]=new SDL_Rect();
	walls[11]->x=224;
	walls[11]->y=288;
	walls[11]->h=32;
	walls[11]->w=32;

	walls[12]=new SDL_Rect();
	walls[12]->x=224;
	walls[12]->y=352;
	walls[12]->h=32;
	walls[12]->w=240;

	walls[13]=new SDL_Rect();
	walls[13]->x=288;
	walls[13]->y=224;
	walls[13]->h=32;
	walls[13]->w=32;

	walls[14]=new SDL_Rect();
	walls[14]->x=352;
	walls[14]->y=160;
	walls[14]->h=32;
	walls[14]->w=32;

	walls[15]=new SDL_Rect();
	walls[15]->x=352;
	walls[15]->y=288;
	walls[15]->h=32;
	walls[15]->w=32;

	walls[16]=new SDL_Rect();
	walls[16]->x=416;
	walls[16]->y=224;
	walls[16]->h=32;
	walls[16]->w=32;

	walls[17]=new SDL_Rect();
	walls[17]->x=480;
	walls[17]->y=160;
	walls[17]->h=32;
	walls[17]->w=32;

	walls[18]=new SDL_Rect();
	walls[18]->x=480;
	walls[18]->y=288;
	walls[18]->h=32;
	walls[18]->w=32;

	walls[19]=new SDL_Rect();
	walls[19]->x=544;
	walls[19]->y=224;
	walls[19]->h=32;
	walls[19]->w=32;

	walls[20]=new SDL_Rect();
	walls[20]->x=616;
	walls[20]->y=352;
	walls[20]->h=64;
	walls[20]->w=32;

	walls[21]=new SDL_Rect();
	walls[21]->x=616;
	walls[21]->y=352;
	walls[21]->h=32;
	walls[21]->w=240;

	walls[22]=new SDL_Rect();
	walls[22]->x=768;
	walls[22]->y=128;
	walls[22]->h=32;
	walls[22]->w=96;

	walls[23]=new SDL_Rect();
	walls[23]->x=832;
	walls[23]->y=256;
	walls[23]->h=32;
	walls[23]->w=32;

	walls[24]=new SDL_Rect();
	walls[24]->x=896;
	walls[24]->y=192;
	walls[24]->h=32;
	walls[24]->w=32;

	walls[25]=new SDL_Rect();
	walls[25]->x=896;
	walls[25]->y=320;
	walls[25]->h=32;
	walls[25]->w=32;
}

void Game::init_gems()
{
	g1[1]=new struct gem();
	g1[1]->score=50;
	g1[1]->type=new SDL_Rect();
	g1[1]->locn=new SDL_Rect();
	g1[1]->type->h=32;
	g1[1]->type->w=32;
	g1[1]->type->x=32;
	g1[1]->type->y=0;
	g1[1]->locn->h=32;
	g1[1]->locn->w=32;
	g1[1]->locn->x=32;
	g1[1]->locn->y=96;

	g1[2]=new struct gem();
	g1[2]->score=50;
	g1[2]->type=new SDL_Rect();
	g1[2]->locn=new SDL_Rect();
	g1[2]->type->h=32;
	g1[2]->type->w=32;
	g1[2]->type->x=32;
	g1[2]->type->y=0;
	g1[2]->locn->h=32;
	g1[2]->locn->w=32;
	g1[2]->locn->x=32;
	g1[2]->locn->y=320;

	g1[3]=new struct gem();
	g1[3]->score=50;
	g1[3]->type=new SDL_Rect();
	g1[3]->locn=new SDL_Rect();
	g1[3]->type->h=32;
	g1[3]->type->w=32;
	g1[3]->type->x=32;
	g1[3]->type->y=0;
	g1[3]->locn->h=32;
	g1[3]->locn->w=32;
	g1[3]->locn->x=96;
	g1[3]->locn->y=128;

	g1[4]=new struct gem();
	g1[4]->score=50;
	g1[4]->type=new SDL_Rect();
	g1[4]->locn=new SDL_Rect();
	g1[4]->type->h=32;
	g1[4]->type->w=32;
	g1[4]->type->x=32;
	g1[4]->type->y=0;
	g1[4]->locn->h=32;
	g1[4]->locn->w=32;
	g1[4]->locn->x=224;
	g1[4]->locn->y=128;

	g1[5]=new struct gem();
	g1[5]->score=50;
	g1[5]->type=new SDL_Rect();
	g1[5]->locn=new SDL_Rect();
	g1[5]->type->h=32;
	g1[5]->type->w=32;
	g1[5]->type->x=32;
	g1[5]->type->y=0;
	g1[5]->locn->h=32;
	g1[5]->locn->w=32;
	g1[5]->locn->x=352;
	g1[5]->locn->y=128;

	g1[6]=new struct gem();
	g1[6]->score=50;
	g1[6]->type=new SDL_Rect();
	g1[6]->locn=new SDL_Rect();
	g1[6]->type->h=32;
	g1[6]->type->w=32;
	g1[6]->type->x=32;
	g1[6]->type->y=0;
	g1[6]->locn->h=32;
	g1[6]->locn->w=32;
	g1[6]->locn->x=480;
	g1[6]->locn->y=128;

	g1[7]=new struct gem();
	g1[7]->score=50;
	g1[7]->type=new SDL_Rect();
	g1[7]->locn=new SDL_Rect();
	g1[7]->type->h=32;
	g1[7]->type->w=32;
	g1[7]->type->x=32;
	g1[7]->type->y=0;
	g1[7]->locn->h=32;
	g1[7]->locn->w=32;
	g1[7]->locn->x=768;
	g1[7]->locn->y=96;

	g1[8]=new struct gem();
	g1[8]->score=50;
	g1[8]->type=new SDL_Rect();
	g1[8]->locn=new SDL_Rect();
	g1[8]->type->h=32;
	g1[8]->type->w=32;
	g1[8]->type->x=32;
	g1[8]->type->y=0;
	g1[8]->locn->h=32;
	g1[8]->locn->w=32;
	g1[8]->locn->x=544;
	g1[8]->locn->y=192;

	g1[9]=new struct gem();
	g1[9]->score=50;
	g1[9]->type=new SDL_Rect();
	g1[9]->locn=new SDL_Rect();
	g1[9]->type->h=32;
	g1[9]->type->w=32;
	g1[9]->type->x=32;
	g1[9]->type->y=0;
	g1[9]->locn->h=32;
	g1[9]->locn->w=32;
	g1[9]->locn->x=896;
	g1[9]->locn->y=160;
}

#endif