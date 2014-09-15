/*  Class Name  : GSoundBank
    Definition  : SFX and BGM data.
    Author      : Aleqh
*/

#include "GSoundBank.h"

// static object for sound control
GSoundBank GSoundBank::SoundControl;

/******************************************************************************************/
GSoundBank::GSoundBank()
{}

/******************************************************************************************/
// Load SFX from file
int GSoundBank::OnLoad(const char *File)
{
    Mix_Chunk* TempSound = NULL;

    if((TempSound = Mix_LoadWAV(File)) == NULL)
    {
        return -1;
    }

    SoundList.push_back(TempSound);

    return (SoundList.size() - 1);
}

/******************************************************************************************/
// Load BGM from file
int GSoundBank::OnLoadMidi(const char *File)
{
    Mix_Music* TempMusic = Mix_LoadMUS(File);

    if(TempMusic == NULL)
    {
        return -1;
    }

    MusicList.push_back(TempMusic);

    return (MusicList.size() - 1);
}

/******************************************************************************************/
void GSoundBank::OnCleanUp()
{
    // Clear SFX vector
    for(unsigned int i = 0; i < SoundList.size(); i++)
    {
        Mix_FreeChunk(SoundList[i]);
    }

    SoundList.clear();

    // Clear BGM vector
    for(unsigned int i = 0; i < MusicList.size(); i++)
    {
        Mix_FreeMusic(MusicList[i]);
    }

    MusicList.clear();
}

/******************************************************************************************/
// Play SFX from SFX list
void GSoundBank::Play(unsigned int ID)
{
    if(ID < 0 || ID >= SoundList.size()) return;
    if(SoundList[ID] == NULL) return;

    Mix_PlayChannel(-1, SoundList[ID], 0);
}

/******************************************************************************************/
// Play BGM from BGM list
void GSoundBank::PlayMusic(unsigned int ID)
{
    if(ID < 0 ||ID >= MusicList.size()) return;
    if(MusicList[ID] == NULL) return;

    Mix_PlayMusic(MusicList[ID], -1);		// -1 loops music
}
