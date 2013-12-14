#ifndef _BAPP_H_
#define _BAPP_H_

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>

#include "BPlayer.h"
#include "BBullet.h"
#include "BEnemy.h"

#include <list>
using namespace std;

class BApp
{
	private:
		// init and store interface to HGE library
		HGE*			hge;

		// Background
		HTEXTURE		b_tBackground;
		HTEXTURE		b_tStars;
		HTEXTURE		b_tBGGapFix;
	
		hgeSprite*		b_sBackground;
		hgeSprite*		b_sStars;
		hgeSprite*		b_sBGGapFix;
	
		hgeVector		b_vBGPosition;
		
		float			BACKGROUND_SCROLLING_SPEED;

		int				BACKGROUND_ALPHA_MIN;
		int				BACKGROUND_ALPHA_MAX;

		// Effect to stars
		bool			b_bBGFadeIn;
		bool			b_bBGFadeOut;
		short			b_nBGAlpha;
		short			b_nBGAlphaFreq;

		// Player
		BPlayer*		b_pPlayerOne;
		float			delta;

		// Bullet
		BBullet*		b_bBullet;
		HTEXTURE		b_tBullet;
		list<BBullet*>  b_lBullets;

		// Enemies
		list<BEnemy*>	b_lEnemies;
		HTEXTURE		b_tEColors[5];
		HTEXTURE		b_tEExplosion;

		
		// Sounds
		HEFFECT			b_eBGMusic0;
		HEFFECT			b_eBGMusic1;
		HEFFECT			b_eBGMusic2;
		HEFFECT			b_eSFXGunshot;
		HEFFECT			b_eSFXExplosion;

	// only work around to OO FrameFunc and RenderFunc 
	private:
		// will contain this pointer
		static BApp* b_pBApp;

		// return this' dynamic equivalent
		static bool static_OnLoop(void);
		static bool static_OnRender(void);

	public:
		BApp(void);
		int OnExecute(void);

	public:
		bool OnInit(void);
		bool OnLoop(void);
		bool OnRender(void);
		void OnCleanup(void);
};

#endif