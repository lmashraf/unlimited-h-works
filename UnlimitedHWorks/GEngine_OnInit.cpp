/*  Class Name  : GEngine
    Description : Handles the loading of all data whether be textures, maps, NPCs, or whatever.
                  Here, everything is initialized.
    Author      : Aleqh
*/
#include "GEngine.h"


bool GEngine::OnInit()
{
    // Initialize LOGGER
     using std::cout;
     using std::endl;

     freopen( "output.txt", "w", stdout );

    // Initialize SDL settings
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    { return false; }

    cout <<"SDL initialized."<<endl;

    if((TheSurface = SDL_SetVideoMode(WWIDTH, WHEIGHT, WBPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    { return false; }

    // Makes the surface White.
    SDL_FillRect(TheSurface, NULL, 0xFFFFFF); // 0xFFFFFF = white in RGB, NULL = full window
    SDL_Flip(TheSurface);

    cout <<"Game Scene initialized."<<endl;

		// A remedy for the Keyboard button mashing afficionado.
        SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    // Load Game State: INTRO
    GStateManager::SetActiveAppState(APPSTATE_INTRO);

    // Engine loaded.
    cout <<"HWGE succesfully loaded."<<endl;
    cout <<"Done."<<endl;

    return true;
}
