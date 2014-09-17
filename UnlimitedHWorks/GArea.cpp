/*  Class Name  : GArea
    Description : Holds basic information about the Area structure.
                  Each Area will have its own file and file format. We define in each file
                  the structure of the Area based on already existing Maps.
                  For example:
                  ----------------------------------.
                  ./tileset.png                     | <--- tileset file
                  2                                 | <--- n*n area's size
                  ./map_one.map ./map_two.map       | <--- which map to load on the matrix A[n]
                  ./map_two.map ./map_three.map     |
                  _________________________________/
    Author      : Aleqh
*/

#include "GArea.h"
#include <iostream>

// static object
GArea GArea::AreaControl;

/******************************************************************************************/
GArea::GArea()
{
    // Init size of the Area
    AreaSize = 0;
}

/******************************************************************************************/
// Loads the Area from a file and populates the Maps and their TileList accordingly
bool GArea::OnLoad(const char* File)
{
    // Clear any old Tileset or existing Map
    OnCleanup();

    // Open the requested Area file.
    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        return false;
    }

    char TilesetFile[255];

    // We retrieve the TilesetFile location..
    fscanf(FileHandle, "%s\n", TilesetFile);

    // .. then we load the Tileset to a Surface, first!
    if((TilesetSurface = GSurface::OnLoad(TilesetFile)) == false)
    {
        fclose(FileHandle);

        return false;
    }

    // We retrieve the supposed size of the Area.
    fscanf(FileHandle, "%d\n", &AreaSize);

    // Loops through X-axis Maps.
    for(int X = 0; X < AreaSize; X++)
    {
        // Loops through Y-axis Maps
        for(int Y = 0; Y < AreaSize; Y++)
        {
            char MapFile[255];

            fscanf(FileHandle, "%s ", MapFile);

            // A temporary Map
            GMap tempMap;

            // Load file information into the temporary Map
            if(tempMap.OnLoad(MapFile) == false)
            {
                fclose(FileHandle);
                return false;
            }

            // Load file information into the temporary Map's TilesetSurface
            tempMap.TilesetSurface = TilesetSurface;

            // Push the temporary Map into our MapList to save it.
            MapList.push_back(tempMap);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

/******************************************************************************************/
/* Draws the Maps on the screen
 *
 * Since an Area can contain up to any number of Maps. Say 100x100 !
 * We don't want to have the program load all the Maps at a time.
 * We will render only Maps that are visible for our size of Screen.
 */
void GArea::OnRender(SDL_Surface* TheSurface, int CameraX, int CameraY)
{
    // Calculates the Maps Width and Height in pixels; allows us to find the first Map to render.
	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

    // ID of the first "VISIBLE" Map to render.
	int FirstID = -CameraX / MapWidth;

    /* By knowing the first Map to render, we can deduce the three others which are:
     *      - At Right - At Bottom - At the Bottom Right
     *
     *       .----------------------.
     *       |          |           |
     *       | firstMap |   Right   |
     *       |          |           |
     *       |       [X]|           |
     *       |----------|-----------|
     *       |          |           |
     *       |  Bottom  |  botRight |
     *       |          |           |
     *       |__________|___________|
     *
     * On other words, we translate Camera coordinates into Map coordinates
     * in order to know which Maps should be rendered.
     */
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

    // We go through each Map that should be rendered.
	for(int i = 0; i < 4; i++)
	{
	    // Calculates the ID of the Map to be rendered.
		unsigned int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        // Checks if the ID is good.
		if(ID < 0 || ID >= MapList.size())
            continue;

        // Turns an ID into an actual Pixel coordinate and then offsets the coordinates
        // by the Camera making them seem like moving.
		int X = ((ID % AreaSize) * MapWidth) + CameraX;
		int Y = ((ID / AreaSize) * MapHeight) + CameraY;

        // Finally render the Map to the exact Coordinates
		MapList[ID].OnRender(TheSurface, X, Y);
	}
}

/******************************************************************************************/
// Free Surfaces and clears all the Maps
void GArea::OnCleanup()
{
	if(TilesetSurface)
	{
		SDL_FreeSurface(TilesetSurface);
	}

	MapList.clear();
}

/******************************************************************************************/
GMap* GArea::GetMap(int X, int Y)
{
    // Calculates the dimensions of the Map in Pixels.
	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

    unsigned int ID = X / MapWidth;

    ID = ID + ((Y / MapHeight) * AreaSize);

    if(ID < 0 || ID >= MapList.size())
    {
        return NULL;
    }

    return &MapList[ID];
}

/******************************************************************************************/
GTile* GArea::GetTile(int X, int Y)
{
    // Calculates the dimensions of the Map in Pixels.
	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

    // Grabs the Map.
	GMap* Map = GetMap(X, Y);

	if(Map == NULL)
        return NULL;

	// Convert X and Y from Pixels coordinates to Tile coordinates
	X = X % MapWidth;
	Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}


