#ifndef _BENEMY_H_
#define _BENEMY_H_
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

class BEnemy
{
	private:
		static HGE*			hge;
		hgeVector			b_vEPosition;
		hgeVector			b_vEVelocity;
		hgeAnimation*		b_aESprite;
		hgeRect				b_bEBoundingBox;
		
		float				b_fESpeed;
		float				b_fECenterY;
		float				b_fERadius;
		float				b_fEAngle;
		float				b_fEFriction;

		bool				b_bECenterYSet;
		bool				b_bEOscillate;

		short				b_sEHealth;

		// Explosion effect
		hgeAnimation*		b_aEExplosionAnim;
		hgeVector			b_aEExplosionPos;

	public:
		BEnemy(hgeVector Position, hgeVector Velocity, short Health, HTEXTURE& Texture);
		~BEnemy();

		bool OnLoop(float delta);
		void OnRender();

		void createExplosion(hgeVector Position);

		short getHealth();
		void  setHealth(short Health);
		float getSpeed();
		void  setSpeed(float Speed);

		void  setOscillate(bool value);

		hgeRect getBoundingBox();
		hgeVector getPosition();
};

#endif;