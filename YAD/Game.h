#ifndef _Player_
#define _Player_


class Player
{
public:
	SDL_Rect *locn;
	SDL_Rect *dimension;
	SDL_Surface *PlayerImage;
	bool rpos, lpos;
	
};

#endif