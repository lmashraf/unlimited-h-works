// Player Entity Class

#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CEntity.h"

enum
{
    PLAYER_MOVE_LEFT = 0,
    PLAYER_MOVE_RIGHT,
    PLAYER_JUMP,
    PLAYER_ATTACK
};

class CPlayer : public CEntity
{
    public:
        CPlayer();

		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);
};

#endif


