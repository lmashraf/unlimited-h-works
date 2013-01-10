#include "CApp.h"


void CApp::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}


void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch(sym)
	{
		case SDLK_LEFT:
		{
			Player.MoveLeft = true;
			Player.lastMoveLeft = true;
			Player.lastMoveRight = false;

			break;
		}

		case SDLK_RIGHT:
		{
			Player.MoveRight = true;
			Player.lastMoveRight = true;
			Player.lastMoveLeft = false;
			break;
		}

		case SDLK_SPACE:
		{
		    Player.Jump();
		    break;
		}

		case SDLK_LCTRL:
		{
		    Player.CanAttack = true;
		    Player.Attack();
		    break;
		}

		default:
		{}
	}
}


void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	switch(sym)
	{
		case SDLK_LEFT:
		{
			Player.MoveLeft = false;
			break;
		}

		case SDLK_RIGHT:
		{
			Player.MoveRight = false;
			break;
		}

        case SDLK_LCTRL:
		{
		    Player.CanAttack = false;
		    break;
		}


		default:
		{}
	}
}


void CApp::OnExit()
{
	Running = false;
}
