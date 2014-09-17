/*  Class Name  : GStateManager
    Description : Manages the Game's different instances and states.
    Author      : Aleqh
*/

#include "GStateManager.h"
#include "GState_InGame.h"
#include "GState_InTitle.h"
#include "GState_InMenu.h"


// Current active App State
GState* GStateManager::ActiveAppState = 0;

/******************************************************************************************/
void GStateManager::OnEvent(SDL_Event* Event)
{
    if(ActiveAppState)
    {
        ActiveAppState->OnEvent(Event);
    }
}

/******************************************************************************************/
void GStateManager::OnLoop()
{
    if(ActiveAppState)
    {
        ActiveAppState->OnLoop();
    }
}

/******************************************************************************************/
void GStateManager::OnRender(SDL_Surface* TheSurface)
{
    if(ActiveAppState)
    {
        ActiveAppState->OnRender(TheSurface);
    }
}

/******************************************************************************************/
void GStateManager::SetActiveAppState(int AppStateID)
{
    // Set the desired Active App State
    if(ActiveAppState)
        ActiveAppState->OnDeactivate();

    //Add the different App States here using the previous Enumeration:
    if(AppStateID == APPSTATE_NONE)
        ActiveAppState = 0;
    if(AppStateID == APPSTATE_INTRO)
        ActiveAppState = GState_InTitle::GetInstance();
    if(AppStateID == APPSTATE_MENU)
        ActiveAppState = GState_InMenu::GetInstance();
    if(AppStateID == APPSTATE_GAME)
        ActiveAppState = GState_InGame::GetInstance();

    if(ActiveAppState)
        ActiveAppState->OnActivate();
}

/******************************************************************************************/
GState* GStateManager::GetActiveAppState()
{
    return ActiveAppState;
}
