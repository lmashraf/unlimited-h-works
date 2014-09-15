/*  Class Name  : GFontEngine
    Description : FontEngine based on SDL_TTF

    Author      : Aleqh
*/

#include "GFontEngine.h"

GFontEngine GFontEngine::FontControl;

GFontEngine::GFontEngine()
{}

bool GFontEngine::OnInit()
{
    return false;
}

void GFontEngine::OnCleanUp()
{}

void GFontEngine::OnLoad(char* Fontfile, int Fontsize)
{}

void GFontEngine::Print(char* Text, int X, int Y, int Fontsize)
{}
