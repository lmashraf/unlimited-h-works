/*  Class Name  : GEngine
    Description : Handles all the rendering of anything that shows up on the screen.
    Author      : Aleqh
*/

#include "GEngine.h"

void GEngine::OnRender()
{
	// Render Game State: GAME
    GStateManager::OnRender(TheSurface);

    // Updates surface.
	SDL_Flip(TheSurface);
}


