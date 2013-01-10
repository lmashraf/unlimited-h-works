/*#ifndef _CMUSIC_H_
#define _CMUSIC_H_

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

class CMusic
{
    private:
        Mix_Music *play_sound;

    public:
        CMusic();

    public:
        void OnCleanup();
        void OnPlay();

};

#endif*/
