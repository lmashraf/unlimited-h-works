/*#include "CMusic.h"

CMusic::CMusic()
{
    play_sound = NULL;

}

void CMusic::OnCleanup()
{
    Mix_FreeMusic(play_sound);
    Mix_CloseAudio();
}

void CMusic::OnPlay(char* filename)
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    play_sound = Mix_LoadMUS(filename);
    Mix_PlayMusic(play_sound, -1);
}


*/
