#ifndef _player_
#define _player_

#include "SDL.h"
#include "level01.h"
#include "Playar.h"


class player : public Playar
{
public:

	
public:
	player();
	void blitPlayer(SDL_Surface *);
	void movePlayer(Game *, int);
	/*void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void adjustDimension(int);*/
};

player::player()
{
	PlayerImage = SDL_LoadBMP( "dave32.BMP" );
	Uint32 colorKey = SDL_MapRGB( PlayerImage->format, 0xFF, 0, 0xFF );
	SDL_SetColorKey(PlayerImage, SDL_SRCCOLORKEY, colorKey );

	lpos=rpos=false;

	locn = new SDL_Rect();
	dimension = new SDL_Rect();

	locn->x = 32;
	locn->y = 384;
	locn->h = 32;
	locn->w = 24;

	dimension->x = 48;
	dimension->y = 0;
	dimension->h = 32;
	dimension->w = 24;
}

void player::blitPlayer(SDL_Surface *buffer)
{
	SDL_BlitSurface( PlayerImage, dimension, buffer, locn );
}

/*void player::adjustDimension(int pos)
{
	if(pos==0)			//left=0
	{
		if(lpos)
		{
			lpos=false;
			dimension->x=24;
		}
		else
		{
			lpos=true;
			dimension->x=0;
		}
	}
	else if(pos==1)		//right=1
	{
		if(rpos)
		{
			rpos=false;
			dimension->x=72;
		}
		else
		{
			rpos=true;
			dimension->x=96;
		}
	}
	else if(pos=2)		//up=2
		dimension->x=48;
	else if(pos=3)		//down=3
		dimension->x=48;
}*/

void player::movePlayer(Game *G, int m)
{
	if(G->possible(this, m))
	{
		switch(m)
		{
			case 0: locn->x-=8;
					break;

			case 1: locn->x+=8;					
					break;

			case 2: locn->y-=8;
					//dimension->x=48;
					return;
					break;

			case 3: locn->y+=8;
					dimension->x=48;
					break;					
		}
	}
	if(m==0)
	{
		if(lpos)
		{
			lpos=false;
			dimension->x=24;
		}
		else
		{
			lpos=true;
			dimension->x=0;
		}
	}
	else if(m==1)
	{
		if(rpos)
		{
			rpos=false;
			dimension->x=72;
		}
		else
		{
			rpos=true;
			dimension->x=96;
		}
	}

}

/*void player::moveUp()
{
	if(
		locn->y-=8;	
	
}

void player::moveDown()
{
	if(locn->y<432)
		locn->y+=8;
	
}

void player::moveLeft()
{
	if(locn->x>0)
		locn->x-=8;
	
}

void player::moveRight()
{
	if(locn->x<468)
		locn->x+=8;
	
}*/

#endif