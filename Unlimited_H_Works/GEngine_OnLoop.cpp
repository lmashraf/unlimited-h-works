/*  Class Name  : GEngine
    Description : Handles all the data updates, such as NPCs moving across the screen, decreasing your health bar, or whatever.
    Author      : Aleqh
*/

#include "GEngine.h"

void GEngine::OnLoop()
{
    // Loop Game State: GAME
    GStateManager::OnLoop();

    // FPS calculation
    GFPS::FPSControl.OnLoop();

    char Buffer[255];

    sprintf(Buffer, "%d", GFPS::FPSControl.GetFPS());

    SDL_WM_SetCaption(Buffer, Buffer);
}
