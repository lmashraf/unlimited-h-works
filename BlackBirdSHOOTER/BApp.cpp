#include "BApp.h"

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>

BApp* BApp::b_pBApp = NULL;

BApp::BApp(void)
{
	// for use in static function OnRender and OnInit
	b_pBApp = this;

	// init and store interface to HGE library
	hge = NULL;

	// Background
	b_tBackground	= 0;  
	b_tStars		= 0;
	b_tBGGapFix		= 0;
	
	b_sBackground	= NULL;
	b_sStars		= NULL;
	b_sBGGapFix		= NULL;
	
	b_vBGPosition	= hgeVector(0,0);

	BACKGROUND_SCROLLING_SPEED	= 2.500f;

	BACKGROUND_ALPHA_MAX		= 255;
	BACKGROUND_ALPHA_MIN		= 50;

	// Stars Effect
	b_bBGFadeIn		= false;
	b_bBGFadeOut	= true;
	b_nBGAlpha		= 255;
	b_nBGAlphaFreq	= 5;

	// Player
	b_pPlayerOne	= NULL;

	// Bullet
	b_tBullet		= 0;

	// Sounds
	b_eBGMusic0		= 0;
	b_eBGMusic1		= 0;
	b_eBGMusic2		= 0;
	b_eSFXGunshot	= 0;
	b_eSFXExplosion = 0;

	// Enemies
	b_tEExplosion	= 0;
	memset(b_tEColors, 0, 5);
}

int BApp::OnExecute(void)
{
	// intialize
	if(OnInit() == false)
	{
		return -1;
	}

	// clean up used resources
	OnCleanup();


	
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	BApp theApp;

	return theApp.OnExecute();
}