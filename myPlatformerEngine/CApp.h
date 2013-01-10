// Application Class

#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>

#include "Define.h"

#include "CFPS.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEvent.h"
#include "CSurface.h"

#include "CPlayer.h"


class CApp : public CEvent
{
    private:
        bool            Running;
        SDL_Surface*    Surf_Display;

        CPlayer			Player;

    public:
        CApp();
        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);
        	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

#endif
