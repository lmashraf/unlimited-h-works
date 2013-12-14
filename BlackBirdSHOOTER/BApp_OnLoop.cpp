#include "BApp.h"

bool BApp::static_OnLoop(void)
{
	return b_pBApp->OnLoop();
}

// Frame Function:
// processes the logic, if true is returned HGE is halted.
bool BApp::OnLoop(void)
{
	//	time elapsed since last frame, similar to SDL_getTicks()
	delta = hge->Timer_GetDelta();

	// Background scrolling
	if(b_vBGPosition.x < 800)
		b_vBGPosition.x += BACKGROUND_SCROLLING_SPEED;
	else
		b_vBGPosition = hgeVector(-982, 0);

	// control fade-ins and fade-outs
	if(b_bBGFadeOut)
	{
		b_nBGAlpha -= b_nBGAlphaFreq;

		if(b_nBGAlpha <= BACKGROUND_ALPHA_MIN)
		{
			b_bBGFadeOut = false;
			b_bBGFadeIn  = true;
		}
	}
	else if(b_bBGFadeIn)
	{
		b_nBGAlpha += b_nBGAlphaFreq;

		if(b_nBGAlpha >= BACKGROUND_ALPHA_MAX)
		{
			b_bBGFadeOut = true;
			b_bBGFadeIn  = false;
		}
	}

	// fade them stars in and out
	b_sStars->SetColor(ARGB(b_nBGAlpha, 255, 255, 255));

	// update enemies
	if(b_lEnemies.size() < 5)
	{
		short Health = hge->Random_Int(50, 100);

		BEnemy* b_Enemy = new BEnemy(hgeVector(830, hge->Random_Int(50,550)), 
									 hgeVector(-hge->Random_Int(2,8), hge->Random_Int(-4,4)), 
									 Health, 
									 b_tEColors[hge->Random_Int(0,4)]);
		
		b_lEnemies.push_back(b_Enemy);
	}
	
	for(list<BEnemy*>::iterator e = b_lEnemies.begin(); e != b_lEnemies.end(); /**/)
	{
		if((*e)->getPosition().x < 0 || (*e)->getPosition().y > 580 || (*e)->getPosition().y < 20)
		  {
			delete (*e);
			e = b_lEnemies.erase(e);
		}
		else
		{
			(*e)->OnLoop(delta);
			e++;
		}
	}

	// update player
	b_pPlayerOne->OnLoop(delta);

	// update bullets
	if(hge->Input_KeyDown(HGEK_SPACE))
	{
		// single shot
		BBullet* b_Bullet = new BBullet(b_pPlayerOne->getPosition() + hgeVector(16,0), hgeVector(15,0), b_tBullet, 50);
		b_lBullets.push_back(b_Bullet);

		hge->Effect_PlayEx(b_eSFXGunshot, 35, 0, hge->Random_Float(1, 1.5));
	}

	for(list<BBullet*>::iterator b = b_lBullets.begin(); b != b_lBullets.end(); /**/)
	{
		(*b)->OnLoop();

		if((*b)->getPosition().x > 800 || (*b)->getPosition().x < 0	|| (*b)->getPosition().y < 0 || (*b)->getPosition().y > 600)
		{
			b = b_lBullets.erase(b);
		}
		else
		{
			b++;
		}
	}

	// Collision Bullet vs Enemy
	if(!b_lBullets.empty() && !b_lEnemies.empty())
	{
		for(list<BBullet*>::iterator b = b_lBullets.begin(); b!= b_lBullets.end(); /**/)
		{
			bool bHit = false;

			// Detect intersection between Bullt and Enemy's Bounding Boxes
			for(list<BEnemy*>::iterator e = b_lEnemies.begin(); e != b_lEnemies.end(); e++)
			{
				if((*e)->getBoundingBox().Intersect(&(*b)->getBoundingBox()))
				{
					// Enemy takes damage
					(*e)->setHealth((*e)->getHealth() - (*b)->getDamage());

					// Play Explosion SoundEffect
					hge->Effect_PlayEx(b_eSFXExplosion, 100, 0, hge->Random_Float(1, 3));

					delete (*b);
					b = b_lBullets.erase(b);

					// Marks the enemy as hit
					bHit = true;

					break;
				}
			}
			if(!bHit)
				b++;
		}
	}

	// Check Enemies Health
	for(list<BEnemy*>::iterator e = b_lEnemies.begin(); e != b_lEnemies.end(); /**/)
	{
		if((*e)->getHealth() <= 0)
		{
			delete(*e);
			e = b_lEnemies.erase(e);
		}
		else
			e++;
	}

	// Collision Enemy vs Player
	for(list<BEnemy*>::iterator e = b_lEnemies.begin(); e  != b_lEnemies.end(); /**/)
	{
		 if((*e)->getBoundingBox().Intersect(&b_pPlayerOne->getBoundingBox()))
		{
			// Player was hit, we remove enemy. Player takes damage.
			delete (*e);
			e = b_lEnemies.erase(e);

			b_pPlayerOne->setPosition(hgeVector(10, 268));
			b_pPlayerOne->setVelocity(hgeVector(0,0));

			// Play Explosion SoundEffect
			hge->Effect_PlayEx(b_eSFXExplosion, 100, 0, hge->Random_Float(1, 3));
		}
		else
			e++;
	}

	// Check whether escape has been pressed or not
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	return false;
}