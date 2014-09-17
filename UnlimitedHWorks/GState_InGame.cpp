/*  Class Name  : GState_InTitle
    Description : Manages the Game's State: GAME
    Author      : Aleqh
*/

#include "GState_InGame.h"

GState_InGame GState_InGame::Instance;

GState_InGame::GState_InGame()
{}

/*************************************[ from: GEngine_OnEvent ]***********************************************/
// Handles KeyDown events.
void GState_InGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
	{
		case SDLK_LEFT:
		{
            // When the player is moving Left we make sure to save data accordingly (ie. Which way the player is facing?).
			Player.MoveLeft = true;
			Player.lastMoveLeft = true;
			Player.lastMoveRight = false;

			break;
		}

		case SDLK_RIGHT:
		{
            // When the player is moving Right we make sure to save data accordingly (ie. Which way the player is facing?).
			Player.MoveRight = true;
			Player.lastMoveRight = true;
			Player.lastMoveLeft = false;

			break;
		}

		case SDLK_SPACE:
		{
		    // Performs a JUMP action.
		    Player.Jump();

		    break;
		}

		case SDLK_LCTRL:
		{
		    // Performs an ATTACK action depending on which face the player was facing last.
		    // A work-around to call upon the correct animation.
		    if(Player.firstAttack == true)
		    {
		        // Initializes the ATTACK event's variables.
                Player.CanAttack = true;
                Player.firstAttack = false;

                // Performs the ATTACK action.
                Player.Attack();

                // A special effect sound can be used.
                GSoundBank::SoundControl.Play(SFX_Attack);
		    }

		    break;
		}

		default:
		{}
	}
}


/*************************************[ from: GEngine_OnEvent ]***********************************************/
// Handles KeyUp events, practically a RESET of whats done on a KeyDown.
void GState_InGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
	{
		case SDLK_LEFT:
		{
			Player.MoveLeft = false;
			break;
		}

		case SDLK_RIGHT:
		{
			Player.MoveRight = false;
			break;
		}

	    /* BUG:
	     * As long as the player is holding L_CTRL the ATTACK animation will still be ongoing.
	     */
        case SDLK_LCTRL:
		{
		    Player.CanAttack = false;
		    Player.firstAttack = true;
		    break;
		}


		default:
		{}
	}
}

/*************************************[ from: GEngine_OnInit ]***********************************************/
void GState_InGame::OnActivate()
{
    // Activate LOGGER
    using std::cout;
    using std::endl;

    // Activate AUDIO settings
    if(Mix_OpenAudio(AUDIO_S16, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        return;

        // BGM (PS: -1 loops the music).
        Mix_Music *music = Mix_LoadMUS("./data/audio/bgm/bgmTheme.mid");
        Mix_PlayMusic(music, -1);

        // SFX
        if((SFX_Attack = GSoundBank::SoundControl.OnLoad("./data/audio/sfx/attack.wav")) == -1)
            return;      

    // Activate GFX settings
    if(GArea::AreaControl.OnLoad("./data/maps/1.area") == false)
        return;


    if((bgSurface  = GSurface::OnLoad("./data/gfx/bg/bg_mymap.png")) == NULL)
        return;

/*    if((mapSurface = GSurface::OnLoad("./data/gfx/bg/bg001.png")) == NULL)
	{
		cout <<"Failure to load ./data/gfx/bg/bg001.png"<<endl<<endl;
       return;
	}*/

    // Activate Entity objects.
    if(Player.OnLoad("./data/gfx/sprites/mainCharacter__.png", 180, 180, 8) == false)
	{
		cout <<"Failure to load ./data/gfx/sprites/mainCharacter__.png"<<endl<<endl;
        return;
	}

    cout <<"Game Sprites set."<<endl;

        // Starting coordinates.
        Player.X = 70;
        Player.Y = 150;

        cout <<"MC coordinates set."<<endl;

        // Register Player as an Entity.
        GEntity::EntityList.push_back(&Player);


    // Activate Camera
	GCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    GCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    cout <<"Camera set."<<endl;
}

/*************************************[ from: GEngine_OnCleanUp ]***********************************************/
void GState_InGame::OnDeactivate()
{

    // Free Maps
	GArea::AreaControl.OnCleanup();

    // Free Entities
    for(unsigned int i = 0;i < GEntity::EntityList.size();i++)
    {
        if(!GEntity::EntityList[i])
            continue;

        GEntity::EntityList[i]->OnCleanup();
    }

    GEntity::EntityList.clear();

    // Free GFX
    SDL_FreeSurface(bgSurface);

    // Free Audio
    GSoundBank::SoundControl.OnCleanUp();
    Mix_CloseAudio();
}

/*************************************[ from: GEngine_OnLoop ]***********************************************/
void GState_InGame::OnLoop()
{
    // Runs through each Entity and call their respective OnLoop() method.
    for(unsigned int i = 0;i < GEntity::EntityList.size();i++)
    {
        if(!GEntity::EntityList[i])
            continue;

        GEntity::EntityList[i]->OnLoop();
    }

    // Collision Events between Entities
    for(unsigned int i = 0; i < GEntityCollide::EntityColList.size(); i++)
    {
        GEntity* EntityA = GEntityCollide::EntityColList[i].EntityA;
        GEntity* EntityB = GEntityCollide::EntityColList[i].EntityB;

        if(EntityA == NULL || EntityB == NULL)
            continue;

        if(EntityA->OnCollision(EntityB))
        {
            EntityB->OnCollision(EntityA);
        }
    }

    // Clears all vector entries.
    GEntityCollide::EntityColList.clear();
}

/*************************************[ from: GEngine_OnRender ]***********************************************/
void GState_InGame::OnRender(SDL_Surface* TheSurface)
{
	SDL_Rect Rect;

	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(TheSurface, &Rect, 0);

    // Renders a Background and makes sure It scrolls following the Camera.
	GSurface::OnDraw(TheSurface, mapSurface, - 50 - GCamera::CameraControl.GetX() * 1.5, + 250 -GCamera::CameraControl.GetY());
	GSurface::OnDraw(TheSurface, bgSurface, - GCamera::CameraControl.GetX(), -GCamera::CameraControl.GetY());

    // Renders the Game's area on the main Surface depending on the Camera's coordinates.
	GArea::AreaControl.OnRender(TheSurface, -GCamera::CameraControl.GetX(), -GCamera::CameraControl.GetY());

    // Runs through each Entity and call their respective OnRender() method.
    for(unsigned int i = 0;i < GEntity::EntityList.size();i++)
    {
        if(!GEntity::EntityList[i])
            continue;

        GEntity::EntityList[i]->OnRender(TheSurface);
    }

	SDL_Flip(TheSurface);
}

/******************************************************************************************/
GState_InGame* GState_InGame::GetInstance()
{
    return &Instance;
}
