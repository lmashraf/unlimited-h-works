/*  Class Name  : CSurface
    Description : Holds every utility needed into our game that deals with SDL_Surface objects.
    Author      : Aleqh
*/
#include "GSurface.h"

/******************************************************************************************/
GSurface::GSurface()
{}

/******************************************************************************************/
// Loads a Surface from a given File.
SDL_Surface* GSurface::OnLoad(const char* File)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Surface* retSurface = NULL;

	if((tempSurface = IMG_Load(File)) == NULL)
	{
		return NULL;
	}

    // Returns a new Surface and DOES NOT overwrite the original.
	retSurface = SDL_DisplayFormatAlpha(tempSurface);

	// Freeing the original Surface
	SDL_FreeSurface(tempSurface);

	return retSurface;
}

/******************************************************************************************/
// Draws a Source Surface into a Destination Surface:
// Basically we are putting srcSurface on top of destSurface at coordinates (X, Y).
bool GSurface::OnDraw(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y)
{

	if(destSurface == NULL || srcSurface == NULL)
	{
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(srcSurface, NULL, destSurface, &DestR);

	return true;
}

/******************************************************************************************/
// Draws a Source Surface into a Destination Surface:
// Basically we are drawing A PART (X2, Y2, W, H) of srcSurface on top of destSurface at coordinate (X, Y).
bool GSurface::OnDraw(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y, int X2, int Y2, int W, int H)
{
	if(destSurface == NULL || srcSurface == NULL)
	{
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(srcSurface, &SrcR, destSurface, &DestR);

	return true;
}

/******************************************************************************************/
bool GSurface::Transparent(SDL_Surface* destSurface, int R, int G, int B)
{
	if(destSurface == NULL)
	{
		return false;
	}

	SDL_SetColorKey(destSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(destSurface->format, R, G, B));

	return true;
}

/*****************************************************************************************/
bool GSurface::FadeIn(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y)
{
    if(destSurface == NULL || srcSurface == NULL)
	{
		return false;
	}

	for(int a = SDL_GetTicks() + 3000; a >= 0; a--)
    {
        SDL_Rect DestR;

        DestR.x = X;
        DestR.y = Y;

        SDL_SetAlpha(srcSurface, SDL_RLEACCEL | SDL_SRCALPHA, a);
        SDL_BlitSurface(srcSurface, NULL, destSurface, &DestR);
        SDL_Flip(destSurface);
    }

	return true;
}

/******************************************************************************************/
bool GSurface::FadeOut(SDL_Surface* destSurface, SDL_Surface* srcSurface, int X, int Y)
{
    if(destSurface == NULL || srcSurface == NULL)
	{
		return false;
	}

	for(unsigned int a = 0;a < 3000; a++)
    {
        SDL_Rect DestR;

        DestR.x = X;
        DestR.y = Y;

        SDL_SetAlpha(srcSurface, SDL_RLEACCEL | SDL_SRCALPHA, a);
        SDL_BlitSurface(srcSurface, NULL, destSurface, &DestR);
        SDL_Flip(destSurface);
    }

	return true;
}
