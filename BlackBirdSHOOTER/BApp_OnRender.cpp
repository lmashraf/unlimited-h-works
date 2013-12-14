#include "BApp.h"

bool BApp::static_OnRender(void)
{
	return b_pBApp->OnRender();
}

// Render Function:
// renders and draws things on screen
bool BApp::OnRender(void)
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

		// render backgrounds
		b_sBackground->Render(b_vBGPosition.x, b_vBGPosition.y);

		// as soon as the position gets greater than -1, we render the second background
		// with the offset -982 as follows --> [ bg1 | bg1 ]
		if(b_vBGPosition.x > -1)
			b_sBackground->Render(b_vBGPosition.x - 982 - 800, 0);

		// fix image gaps: optional
		b_sBGGapFix->Render(b_vBGPosition.x - 28, 0);

		// show stars
		b_sStars->Render(0,0);

		// show player
		b_pPlayerOne->OnRender();

		// show enemies
		for(list<BEnemy*>::iterator e = b_lEnemies.begin(); e != b_lEnemies.end(); e++)
		{
			(*e)->OnRender();
		}

		// show bullets
		for(list<BBullet*>::iterator b = b_lBullets.begin(); b != b_lBullets.end(); b++)
		{
			(*b)->OnRender();
		}

	hge->Gfx_EndScene();

	return false;
}