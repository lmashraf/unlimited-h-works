/*  Class Name  : GMap
    Description : Holds basic information about the Map.
                  A Map is defined by a pile of Tiles read and written from and to a TileList to a TilesetSurface.
    Author      : Aleqh
*/

#ifndef _GMap_H_
    #define _GMap_H_

#include <SDL.h>
#include <vector>

#include "GTile.h"
#include "GSurface.h"


class GMap
{
	public:
		SDL_Surface*			TilesetSurface;

	private:
        // A list that will hold the tiles.
		std::vector<GTile>      TileList;

	public:
		GMap();

	public:
		bool OnLoad(char* File);

		void OnRender(SDL_Surface* TheSurface, int MapX, int MapY);

    public:
        GTile*	GetTile(int X, int Y);
};

#endif
