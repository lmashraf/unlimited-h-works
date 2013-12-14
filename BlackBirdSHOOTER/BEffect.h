#ifndef _BEFFECT_H_
#define _BEFFECT_H_
#pragma once

#include <hge.h>
#include <hgeanim.h>
#include <hgevector.h>

class BEffect
{
	private:
		hgeAnimation*		b_aEffAnimation;
		hgeVector			b_vEffPosition;

	public:
		BEffect(void);
		~BEffect(void);

		void createExplosion(hgeVector Position);
};

#endif