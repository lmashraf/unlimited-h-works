// Map Class (A pile of tiles.)

#ifndef _CMAP_H_
    #define _CMAP_H_

#include <SDL.h>
#include <vector>

#include "CTile.h"
#include "CSurface.h"


class CMap
{
	public:
		SDL_Surface*			Surf_Tileset;

	private:
		std::vector<CTile>      TileList;

	public:
		CMap();

	public:
		bool OnLoad(char* File);

		void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);

    public:
        CTile*	GetTile(int X, int Y);
};

#endif
