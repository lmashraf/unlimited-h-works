
/*  Class Name  : GState_InMenu
    Description : Manages the Game's State: GAME
    Author      : Aleqh
*/
#include "GStateManager.h"
#include "GState_InMenu.h"


GState_InMenu GState_InMenu::Instance;

GState_InMenu::GState_InMenu()
{
            // The Game's sound assets could be better If regrouped in a single SoundBank
    SFX_Click = 0;
    BGM_Title = 0;

    // Background GFX
    surfMenuDialog  = NULL;
    surfBackground  = NULL;
}

/*************************************[ from: GEngine_OnEvent ]***********************************************/
// Handles KeyDown events.
void GState_InMenu::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
	{
		case SDLK_UP:
		{
            // TBD: Move Cursor UP
			break;
		}

		case SDLK_DOWN:
		{
            // TBD: Move Cursor DOWN
			break;
		}

		case SDLK_RETURN:
		{
		    // TBD: SELECT MENU
            GSoundBank::SoundControl.Play(SFX_Click);
		    break;
		}

		default:
		{}
	}
}


/*************************************[ from: GEngine_OnEvent ]***********************************************/
// Handles KeyUp events, practically a RESET of whats done on a KeyDown.
void GState_InMenu::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
	{
		case SDLK_UP:
		{
			// TBD: Stay put.
			break;
		}

		case SDLK_DOWN:
		{
			// TBD: Stay put
			break;
		}

        case SDLK_RETURN:
		{
            GStateManager::SetActiveAppState(APPSTATE_GAME);
		}

		default:
		{}
	}
}

/*************************************[ from: GEngine_OnInit ]***********************************************/
void GState_InMenu::OnActivate()
{
    // Activate AUDIO settings
    if(Mix_OpenAudio(AUDIO_S16, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        return;

        // BGM (PS: -1 loops the music).
        Mix_Music *music = Mix_LoadMUS("./data/audio/bgm/bgmTitle.mid");
        Mix_PlayMusic(music, -1);

        // SFX
        if((SFX_Click = GSoundBank::SoundControl.OnLoad("./data/audio/sfx/logo.wav")) == -1)
            return;

    if((surfBackground = GSurface::OnLoad("./data/gfx/bg/bg_menu.png")) == NULL)
        return;

    if((surfMenuDialog = GSurface::OnLoad("./data/gfx/bg/bg_menudialog.png")) == NULL)
        return;
}

/*************************************[ from: GEngine_OnCleanUp ]***********************************************/
void GState_InMenu::OnDeactivate()
{
    // Free GFX
    SDL_FreeSurface(surfBackground);
    SDL_FreeSurface(surfMenuDialog);

    // Free Audio
    GSoundBank::SoundControl.OnCleanUp();
    Mix_CloseAudio();
}

/*************************************[ from: GEngine_OnLoop ]***********************************************/
void GState_InMenu::OnLoop()
{}

/*************************************[ from: GEngine_OnRender ]***********************************************/
void GState_InMenu::OnRender(SDL_Surface* TheSurface)
{
	SDL_Rect Rect;

	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(TheSurface, &Rect, 0);

    // Renders a Background and makes sure It scrolls following the Camera.
	GSurface::OnDraw(TheSurface, surfBackground, 0, 0);
	GSurface::OnDraw(TheSurface, surfMenuDialog, WWIDTH/2, WHEIGHT/2 + 150);

	SDL_Flip(TheSurface);
}

/******************************************************************************************/
GState_InMenu* GState_InMenu::GetInstance()
{
    return &Instance;
}
