#ifndef _BBULLET_H_
#define _BBULLET_H_

#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

class BBullet
{
	private:	
		static HGE*		hge;
		hgeVector		b_vBPosition;
		hgeVector		b_vBVelocity;
		hgeSprite*		b_sBSprite;
		hgeRect			b_bBBoundingBox;
		HTEXTURE		b_tBTexture;

		float			b_fBSpeed;
		float			b_fBFriction;
		short			b_nBDamage;

		// bullet oscillation
		float			b_fBCenterY;
		float			b_fBRadius;
		float			b_fBAngle;

		bool			b_bBCenterYSet;
		bool			b_bBOscillate;
		bool			b_bBOscillateReverse;

	public:
		BBullet(hgeVector b_vBPosition, hgeVector b_vBVelocity, HTEXTURE& b_tBTexture, short b_fBDamage);
		~BBullet(void);

		void OnLoop(void);
		void OnRender(void);

		// getters
		short getDamage(void);
		hgeRect getBoundingBox(void);
		hgeVector getPosition(void);

		// setters
		void setDamage(short b_nBDamage);
		void setOscillateReverse(bool value);
		void setOscillate(bool value);

		// 
		//virtual void CalculateTrajectory();
		//virtual void DoDamage();
};

#endif