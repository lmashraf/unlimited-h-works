/*  Class Name  : GArea
    Description : Holds basic information about the Area.
                  An Area is defined by a pile of Maps.
    Author      : Aleqh
*/

#ifndef _GArea_H_
    #define _GArea_H_

#include "GMap.h"


class GArea
{
    public:
        // By using this object we are allowed to manipulate an Area from any other class.
        static GArea            AreaControl;

    public:
        // A list that will hold the Maps
        std::vector<GMap>       MapList;

    private:
        // Number of Maps on the Area. (eg. AreaSize = 3 implies a 3x3 Map)
        // This could be replaced later by an AreaWidth and AreaHeight
        int                     AreaSize;
        SDL_Surface*			TilesetSurface;

    public:
        GArea();

        bool    OnLoad(const char* File);

        void    OnRender(SDL_Surface* TheSurface, int CameraX, int CameraY);

        void    OnCleanup();

    public:
        GMap*	GetMap(int X, int Y);
		GTile*	GetTile(int X, int Y);
};

#endif

