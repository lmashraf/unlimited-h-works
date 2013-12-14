#include "BApp.h"

bool BApp::OnInit(void)
{
	// create pointer to HGE's interface
	hge = hgeCreate(HGE_VERSION);

	// set HGE's system states, most of them are default
	hge->System_SetState(HGE_FRAMEFUNC, static_OnLoop);		// set frame function
	hge->System_SetState(HGE_RENDERFUNC, static_OnRender);	// set rendering function
	hge->System_SetState(HGE_WINDOWED, true);				// windowed/fullscreen mode
	hge->System_SetState(HGE_USESOUND, true);				// enable/disable sounds
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);			// vsync
	hge->System_SetState(HGE_TITLE, "Black Bird");			// window title

	// initialize HGE's with set system states
	if(hge->System_Initiate())
	{
		// initialize music
		b_eBGMusic0			= hge->Effect_Load("snd/deep_space.ogg");
		b_eBGMusic1			= hge->Effect_Load("snd/space_ambient.ogg");
		b_eBGMusic2			= hge->Effect_Load("snd/ambiance_space.ogg");
		b_eSFXGunshot		= hge->Effect_Load("snd/gun_shot.ogg");
		b_eSFXExplosion		= hge->Effect_Load("snd/explosion.aif");

		hge->Effect_PlayEx(b_eBGMusic0,  40, 0, 0, true);
		hge->Effect_PlayEx(b_eBGMusic1, 100, 0, 0, true);
		hge->Effect_PlayEx(b_eBGMusic2,  10, 0, 0, true);

		// initialize player
		b_pPlayerOne		= new BPlayer(hgeVector(10, 268), hgeVector(5, 0));

		// initialize bullets
		b_tBullet			= hge->Texture_Load("img/bullet.png");

		// initialize enemies
		b_tEColors[0]		= hge->Texture_Load("img/eSpritesheet_40x30.png");
		b_tEColors[1]		= hge->Texture_Load("img/eSpritesheet_40x30_hue1.png");
		b_tEColors[2]		= hge->Texture_Load("img/eSpritesheet_40x30_hue2.png");
		b_tEColors[3]		= hge->Texture_Load("img/eSpritesheet_40x30_hue3.png");
		b_tEColors[4]		= hge->Texture_Load("img/eSpritesheet_40x30_hue4.png");

		// initialize backgrounds
		b_tBackground		= hge->Texture_Load("img/farback.jpg");
		b_tStars			= hge->Texture_Load("img/starfield.png");
		b_tBGGapFix			= hge->Texture_Load("img/bg_gapfix.jpg");

			// subtle way to duplicate the background using them as tiles themselves
			b_sBackground	= new hgeSprite(b_tBackground, 0, 0, 1782, 600);
			b_sStars		= new hgeSprite(b_tStars,      0, 0,  800, 600);
			b_sBGGapFix		= new hgeSprite(b_tBGGapFix,   0, 0,   64, 600);
		
		// position of the background is set on the right side and also scrolls to right
		// backgroudnd is 1782px width and window is 800px.
		// 800 - 1782 = -982;
		b_vBGPosition		= hgeVector(-982, 0);	

		// start game loop
		hge->System_Start();
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return false;
	}

	return true;
}