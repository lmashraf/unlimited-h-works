/*  Class Name  : GState_InMenu
    Description : Manages the Game's State: GAME
    Author      : Aleqh
*/

#ifndef __GSTATE_INMENU_H__
    #define __GSTATE_INMENU_H__

#include "GState.h"

#include "GConfig.h"

#include "GSurface.h"
#include "GSoundBank.h"

class GState_InMenu : public GState
{
    private:
        static GState_InMenu Instance;

        // The Game's sound assets could be better If regrouped in a single SoundBank
        int SFX_Click;
        int BGM_Title;

        // Background GFX
        SDL_Surface* surfMenuDialog;
        SDL_Surface* surfBackground;

    public:
        GState_InMenu();

    public:
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender(SDL_Surface* TheSurface);

    public:
        static GState_InMenu* GetInstance();
};

#endif
