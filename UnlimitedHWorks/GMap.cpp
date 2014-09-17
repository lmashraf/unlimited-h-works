/*  Class Name  : GMap
    Description : Holds basic information about our Maps. Straight forward:
                - Our maps will be text files.
                - Each map is going to have a width and height defining the number of tiles.
                - The file format for example can be as follows:
                        0:0 0:0 0:0 0:0
                        1:0 1:0 1:0 0:0
                        1:0 1:0 1:0 0:0
                        1:0 1:0 1:0 0:0
                        1:0 1:0 1:0 0:0
                The number are defined by TileID:TypeID as seen before.
    Author      : Aleqh
*/

#include "GMap.h"

/******************************************************************************************/
GMap::GMap()
{
	TilesetSurface = NULL;
}

/******************************************************************************************/
// Loads the Map from a file and populates the TileList
bool GMap::OnLoad(char* File)
{
    // Clear any old Tileset
    TileList.clear();

    // Open the requested Map file.
    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        return false;
    }

    // Loops on Y axis going from the top row to the bottom row of the map.
    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        // Loops on X axis going from the left most tile to the right most tile.
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            // A temporary Tile
            GTile tempTile;

            // Load file information into the temporary Tile
            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            // Push the temporary Tile into our TileList to save it.
            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

/******************************************************************************************/
// Puts the Tile on the screen and draws them using the TilsetSurface
// MapX and MapY: tells where to render this map on the screen.
void GMap::OnRender(SDL_Surface* TheSurface, int MapX, int MapY)
{
    // Checks for a valid Tileset
	if(TilesetSurface == NULL)
        return;

    // Retrieve the Tileset's Width and Height to deduce Tiles number
	int TilesetWidth  = TilesetSurface->w / TILE_SIZE;
	// UNUSED: int TilesetHeight = TilesetSurface->h / TILE_SIZE;

	// A counter to to Tiles
	int ID = 0;

    // Loops following Y-axis to render tiles. Y is also a number of a Tile.
	for(int Y = 0;Y < MAP_HEIGHT;Y++)
	{
	    // Loops following X-axis to render tiles. X is also a number of a Tile.
		for(int X = 0;X < MAP_WIDTH;X++)
		{
            // Should this Tile even be drawn?
			if(TileList[ID].TypeID == TILE_TYPE_NONE)
			{
                // No. Then how about the next Tile?
				ID++;
				continue;
			}

			// Convert X,Y coordinates Tiles to Pixels
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

            /* Calculates where on the Tileset to grab the appropriate tile.
             * This is done by grabing the TileID of the tile first, and then converting to a Tile coordinate.
             *
             * For example:
             *
             * [CALUCLATE X]
             * 2x2 tileset and TileID of 1. Figuring out X, we would get 1%2 which is 1 still.
             * When we multiply that by TILE_SIZE we get 32. That is the correct X coordinate for the Tile
             *
             * [CALUCLATE Y]
             * The same goes with Y, we put 1/2 which is 0.5. Since this is an integer operation, the .5 is dropped.
             * We are left with 0. Which is also the correct row.
             *
             */
			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

            // Draw Tile to screen using the coordinates we just calculated.
			GSurface::OnDraw(TheSurface, TilesetSurface, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

            // Increase the ID to go to the next Tile.
			ID++;
		}
	}
}

/******************************************************************************************/
GTile* GMap::GetTile(int X, int Y)
{
    unsigned int ID = 0;

    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));

    if(ID < 0 || ID >= TileList.size())
    {
    	return NULL;
    }

    return &TileList[ID];
}
