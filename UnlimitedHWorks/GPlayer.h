/*  Class Name  : GPlayer
    Definition  : Defines the Player entity. Overrides Entity class.
    Author      : Aleqh
*/

#ifndef _GPlayer_H_
    #define _GPlayer_H_

#include "GEntity.h"

enum
{
    PLAYER_MOVE_LEFT = 0,
    PLAYER_MOVE_RIGHT,
    PLAYER_JUMP,
    PLAYER_ATTACK
};

class GPlayer : public GEntity
{
    public:
        GPlayer();

		bool OnLoad(const char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* TheSurface);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(GEntity* Entity);

    public:
		void OnMove(float MoveX, float MoveY);

    private:
        bool PosValid(int NewX, int NewY);

};

#endif


