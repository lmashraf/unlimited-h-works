/*  Class Name  : GSurface
    Description : Holds every utility needed into our game that deals with SDL_Surface objects.
    Author      : Aleqh
*/


#ifndef _GSurface_H_
    #define _GSurface_H_

#include <SDL.h>
#include <SDL_image.h>


class GSurface
{
	public:
		GSurface();

    // Surface functions
	public:
		static SDL_Surface* OnLoad(const char* File);

		static bool OnDraw(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y);
		static bool OnDraw(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y, int X2, int Y2, int W, int H);

		static bool Transparent(SDL_Surface* destSurface, int R, int G, int B);

    public:
		static bool FadeIn(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y);
		static bool FadeOut(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y);
};

#endif
