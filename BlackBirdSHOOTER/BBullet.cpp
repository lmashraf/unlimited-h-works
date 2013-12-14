#include "bbullet.h"

HGE* BBullet::hge = NULL;
		  
BBullet::BBullet(hgeVector b_vBPosition, hgeVector b_vBVelocity, HTEXTURE& b_tBTexture, short b_nBDamage)
{
	hge = hgeCreate(HGE_VERSION);

	this->b_sBSprite			= new hgeSprite(b_tBTexture, 0, 0, 6, 3);
	this->b_sBSprite->SetHotSpot(3, 1.5);

	this->b_fBSpeed				= 0.20f;
	this->b_fBFriction			= 0.99f;

	this->b_fBCenterY			= 0;
	this->b_fBRadius			= hge->Random_Float(50.0f, 80.0f);
	this->b_fBAngle				= 0.0f;
	this->b_nBDamage			= b_nBDamage;

	this->b_bBCenterYSet		= false;
	this->b_bBOscillate			= false;
	this->b_bBOscillateReverse	= true;

	this->b_vBPosition			= b_vBPosition;
	this->b_vBVelocity			= b_vBVelocity;
}

BBullet::~BBullet(void)
{
	delete b_sBSprite;

	hge->Release();
}

// FrameFunction
void BBullet::OnLoop(void)
{
	b_vBVelocity.x	*= b_fBFriction;
	b_vBVelocity.y	*= b_fBFriction;

	b_vBPosition.x	+= b_vBVelocity.x;

	if(!b_bBOscillate)
		b_vBPosition.y	+= b_vBVelocity.y;
	else
	{
		if(!b_bBCenterYSet)
		{
			b_fBCenterY		= b_vBPosition.y;
			b_bBCenterYSet	= true;
		}

		if(!b_bBOscillateReverse)
			b_vBPosition.y	= b_fBCenterY - sin(b_fBAngle) * b_fBRadius;
		else
			b_vBPosition.y	= b_fBCenterY + sin(b_fBAngle) * b_fBRadius;

		b_fBAngle	+= 0 * hge->Timer_GetDelta();
	}

	b_sBSprite->GetBoundingBox(b_vBPosition.x, b_vBPosition.y, &b_bBBoundingBox);
}

//RenderFunction
void BBullet::OnRender(void)
{
	b_sBSprite->Render(b_vBPosition.x, b_vBPosition.y);
}

// getters & setters
short BBullet::getDamage(void)
{
	return this->b_nBDamage;
}

hgeRect BBullet::getBoundingBox(void)
{
	return this->b_bBBoundingBox;
}

hgeVector BBullet::getPosition(void)
{
	return this->b_vBPosition;
}

// setters
void BBullet::setDamage(short b_nBDamage)
{
	this->b_nBDamage = b_nBDamage;
}

void BBullet::setOscillateReverse(bool value)
{
	this->b_bBOscillateReverse = value;
}

void BBullet::setOscillate(bool value)
{
	this->b_bBOscillate;
}



