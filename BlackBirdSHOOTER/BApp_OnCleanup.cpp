#include "BApp.h"

// cleanups
void BApp::OnCleanup(void)
{
	// remove Backgrounds
	hge->Texture_Free(b_tBackground);
	hge->Texture_Free(b_tStars);
	hge->Texture_Free(b_tBGGapFix);

	delete b_sBackground;
	delete b_sStars;
	delete b_sBGGapFix;

	// remove players
	delete b_pPlayerOne;

	// remove bullets
	hge->Texture_Free(b_tBullet);

	for(list<BBullet*>::iterator b = b_lBullets.begin(); b != b_lBullets.end(); ++b)
	{
		delete (*b);
		//b_lBullets.erase(b); by ayoub
	}

	b_lBullets.clear(); // by ayoub

	// clean music
	hge->Effect_Free(b_eBGMusic0);
	hge->Effect_Free(b_eBGMusic1);
	hge->Effect_Free(b_eBGMusic2);
	hge->Effect_Free(b_eSFXGunshot);

	// clean enemimes
	for(short i = 0; i < 5; i++)
		hge->Texture_Free(b_tEColors[i]);

	// close HGE
	hge->System_Shutdown();
	hge->Release();
}