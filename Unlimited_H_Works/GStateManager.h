/*  Class Name  : GStateManager
    Description : Manages the Game's different instances and states.
    Author      : Aleqh
*/

#ifndef __GSTATEMANAGER_H__
    #define __GSTATEMANAGER_H__

#include "GState.h"

// Enumerating Game States
enum
{
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_MENU,
    APPSTATE_GAME
};

// Singleton class, all methods and members are made static.
class GStateManager
{
    private:
        static GState* ActiveAppState;

    public:
        static void OnEvent(SDL_Event* Event);

        static void OnLoop();

        static void OnRender(SDL_Surface* TheSurface);

    public:
        static void SetActiveAppState(int AppStateID);

        static GState* GetActiveAppState();

};

#endif // __GSTATEMANAGER_H__
