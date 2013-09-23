/*  Class Name  : GEngine
    Definition  : This class sets the stage for the whole program.
                As most games consist of 5 functions that handles the game processes, this classes enable
                these functions in a flexible manner. These processes are:
                    - Initialization
                    - Events
                    - Loops
                    - Rendering
                    - Cleaning
    Author      : Aleqh
*/

#ifndef _GEngine_H_
    #define _GEngine_H_

#include <SDL.h>
// Logging
#include <iostream>
#include <cstdio>

// Constants
#include "GConfig.h"

// SpeedFactor
#include "GFPS.h"

// AppStates
#include "GStateManager.h"

// GameEngine
#include "GEvent.h"
#include "GSurface.h"

#include "GPlayer.h"


class GEngine : public GEvent
{
    private:
        bool            statusRunning;

        // Basically the program's Main Surface
        SDL_Surface*    TheSurface;

    public:
        GEngine();
        int OnExecute();

    // Methods defining the game processes. Definitions are on separate files for easier maintenance.
    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);
            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

#endif
