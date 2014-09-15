#ifndef __GFONTENGINE_H_
    #define __GFONTENGINE_H__

#include "SDL_ttf.h"

class GFontEngine
{
    static GFontEngine  FontControl;

    private:
        //TTF_Font myFont;

    public:
        GFontEngine();

        bool OnInit();

        void OnCleanUp();

    public:
        void OnLoad(char* Fontfile, int Fontsize);

        void Print(char* Text, int X, int Y, int Fontsize);
};
#endif // __GFONTENGINE_H_
