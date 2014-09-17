/*  Class Name  : GState_InGame
    Description : Manages the Game's State: GAME
    Author      : Aleqh
*/

#ifndef __GSTATE_INGAME_H__
    #define __GSTATE_INGAME_H__

#include <iostream>

#include "GState.h"

#include "GArea.h"
#include "GCamera.h"
#include "GEntity.h"
#include "GSurface.h"
#include "GSoundBank.h"

#include "GPlayer.h"

class GState_InGame : public GState
{
    private:
        static GState_InGame Instance;

        // The Player object. We can have more.
        GPlayer	Player;

        // The Game's sound assets could be better If regrouped in a single SoundBank
        int SFX_Attack;

        int BGM_BossFight;

        // Background GFX
        SDL_Surface* bgSurface;
        SDL_Surface* mapSurface;

    public:
        GState_InGame();

    public:
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender(SDL_Surface* TheSurface);

    public:
        static GState_InGame* GetInstance();
};

#endif
