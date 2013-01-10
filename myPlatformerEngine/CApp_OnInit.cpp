
#include "CApp.h"


bool CApp::OnInit()
{

    // Init SDL settings
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, WBPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    // Init Maps and Areas
    if(CArea::AreaControl.OnLoad("./maps/1.area") == false)
    {
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    // Init Player settings
    if(Player.OnLoad("mainCharacter.png", 100, 100, 7) == false)
    {
    	return false;
    }

    Player.X = 50;
    Player.Y = 300;

    CEntity::EntityList.push_back(&Player);


    // Init Camera target
	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    return true;
}


