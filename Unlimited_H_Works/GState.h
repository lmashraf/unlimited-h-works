/*  Class Name  : GState
    Description : Manages the Game's different instances and states.
    Author      : Aleqh
*/
#ifndef __GState_H__
    #define __GState_H__

#include "GEvent.h"

class GState : public GEvent
{
    public:
        GState();

    // Methods are required to be defined in a child class, hence the '=0' ..
    public:
        virtual void OnActivate() = 0;

        virtual void OnDeactivate() = 0;

        virtual void OnLoop() = 0;

        virtual void OnRender(SDL_Surface* TheSurface) = 0;
};

#endif // __GState_H__
