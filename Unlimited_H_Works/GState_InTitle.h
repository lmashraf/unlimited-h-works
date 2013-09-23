/*  Class Name  : GState_InTitle
    Description : Manages the Game's State: INTRO
    Author      : Aleqh
*/

#ifndef __GSTATE_INTITLE_H__
    #define __GSTATE_INTITE_H__

#include "GState.h"
#include "GSurface.h"

#include "GSoundBank.h"

#include "GConfig.h"

class GState_InTitle : public GState
{
    private:
        static GState_InTitle Instance;

        // LOGO
        SDL_Surface* surfLogo;

        // SFX
        int SFX_Logo;

        int StartTime;

    private:
        GState_InTitle();

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender(SDL_Surface* TheSurface);

    public:
        static GState_InTitle* GetInstance();
};

#endif
