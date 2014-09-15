/*  Class Name  : GState_InTitle
    Description : Manages the Game's State: INTRO
    Author      : Aleqh
*/

#include "GState_InTitle.h"
#include "GStateManager.h"
#include "GState_InMenu.h"

#include "GSoundBank.h"

#include "GSurface.h"

GState_InTitle GState_InTitle::Instance;

/******************************************************************************************/
GState_InTitle::GState_InTitle()
{
    surfLogo  = NULL;
    SFX_Logo  = 0;
    StartTime = 0;
}

/******************************************************************************************/
GState_InTitle* GState_InTitle::GetInstance()
{
    return &Instance;
}

/******************************************************************************************/
void GState_InTitle::OnActivate()
{
    // Load Logo
    surfLogo = GSurface::OnLoad("./data/gfx/bg/splash_screen.png");

    // Load SFX
    if((SFX_Logo = GSoundBank::SoundControl.OnLoad("./data/audio/sfx/logo.wav")) == -1)
        return;

    GSoundBank::SoundControl.Play(SFX_Logo);

    StartTime = SDL_GetTicks();
}

/******************************************************************************************/
void GState_InTitle::OnDeactivate()
{
    if(surfLogo)
    {
        SDL_FreeSurface(surfLogo);
        surfLogo = NULL;
    }

    // Free Audio
    GSoundBank::SoundControl.OnCleanUp();
    Mix_CloseAudio();
}

/******************************************************************************************/
void GState_InTitle::OnLoop()
{
    // Splash screen visible for 3 seconds.
    if((unsigned) StartTime + 4000 < SDL_GetTicks())
    {
        GStateManager::SetActiveAppState(APPSTATE_MENU);
    }
}

/******************************************************************************************/
void GState_InTitle::OnRender(SDL_Surface* TheSurface)
{
    if(surfLogo)
    {
            GSurface::FadeOut(TheSurface, surfLogo, WWIDTH/2 - 200, WHEIGHT/2 - 80);
    }
}
