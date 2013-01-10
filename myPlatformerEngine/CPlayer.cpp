#include "CPlayer.h"

CPlayer::CPlayer()
{}

bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames)
{
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false)
    {
        return false;
    }

    return true;
}


void CPlayer::OnLoop()
{
	CEntity::OnLoop();
}


void CPlayer::OnRender(SDL_Surface* Surf_Display)
{
	CEntity::OnRender(Surf_Display);
}


void CPlayer::OnCleanup()
{
	CEntity::OnCleanup();
}


void CPlayer::OnAnimate()
{
    if(SpeedX != 0)
    {
       Anim_Control.MaxFrames = 7;
    }
    else
    {
        Anim_Control.MaxFrames = 4;
    }

	CEntity::OnAnimate();
}


bool CPlayer::OnCollision(CEntity* Entity)
{
    Jump();
    Attack();
    return true;
}
