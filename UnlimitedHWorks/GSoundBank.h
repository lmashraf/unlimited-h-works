/*  Class Name  : GSoundBank
    Definition  : SFX and BGM data.
    Author      : Aleqh
*/
#ifndef _GSoundBank_H_
    #define _GSoundBank_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

class GSoundBank
{
    public:
        static GSoundBank SoundControl;

        // SFX vector
        std::vector<Mix_Chunk*> SoundList;

        // BGM vector
        std::vector<Mix_Music*> MusicList;

    public:
        GSoundBank();

        // Load SFX and BGM
        int OnLoad(const char * File);
        int OnLoadMidi(const char * File);

        void OnCleanUp();

    public:
        // Play SFX and BGM
        void Play(unsigned int ID);
        void PlayMusic(unsigned int ID);
};

#endif
