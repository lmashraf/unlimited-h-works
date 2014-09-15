/*  Class Name  : GEngine
    Description : Cleans any loaded resources.
    Author      : Aleqh
*/

#include "GEngine.h"

void GEngine::OnCleanup()
{
    // Free Game State: NONE
    GStateManager::SetActiveAppState(APPSTATE_NONE);

    // Free GFX
    SDL_FreeSurface(TheSurface);

    // Quit SDL
    SDL_Quit();
}


