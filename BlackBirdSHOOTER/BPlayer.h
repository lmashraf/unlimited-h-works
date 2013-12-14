#ifndef _BPLAYER_H_
#define _BPLAYER_H_
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#include "BWeapon.h"

class BPlayer
{
	private:
		static HGE*		hge;				
		hgeVector		b_vPPosition;		// positionning
		hgeVector		b_vPVelocity;		// velocity
		HTEXTURE		b_tPTexture;		// sprite sheet
		hgeAnimation*	b_aPSprite;			// sprite animation
		hgeRect			b_rPBoudingBox;		// collision detection
		float			b_fPSpeed;			// speed
		float			b_fPFriction;		// friction
		
		BWeapon*		pWeapon;

	public:
		BPlayer(hgeVector b_vPPosition, hgeVector b_vPVelocity);
		~BPlayer(void);

		bool OnLoop(float delta);
		void OnRender();

		void setVelocity(hgeVector velocity);
		void setPosition(hgeVector position);
		hgeRect getBoundingBox(void);
		hgeVector getPosition(void);
		
		void setWeapon(BWeapon* weapon) { delete this->pWeapon; this->pWeapon = weapon; }
		BWeapon* getWeapon(void) const { return this->pWeapon; }
};

#endif