/*  Class Name  : GTile
    Description : Holds basic information about the Tile sets.
                  A tile is a single square graphic that's draw on the screen.
                  A whole tile set will be loaded within a single file.
    Author      : Aleqh
*/

#ifndef _GTile_H_
	#define _GTile_H_

#include "GConfig.h"

/* Allows us to assign the TypeID of the Tile
 *
 * 1: NORMAL TILE
 * 2: BLOCK  TILE
 * 3: HIDDEN TILE
 */
enum {
    TILE_TYPE_NONE = 0,

    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK,
    TILE_TYPE_HIDDEN
};


class GTile
{
    public:
        int     TileID;
        int     TypeID;

    public:
        GTile();
};

#endif
