#include "benemy.h"

HGE* BEnemy::hge	= 0;

BEnemy::BEnemy(hgeVector Position, hgeVector Velocity, short Health, HTEXTURE& Texture)
{
	hge						= hgeCreate(HGE_VERSION);

	this->b_vEPosition		= Position;
	this->b_vEVelocity		= Velocity;

	this->b_sEHealth		= Health;

	this->b_aESprite = new hgeAnimation(Texture, 6, 6, 0, 0, 40, 30);
	this->b_aESprite->SetHotSpot(20, 15);
	this->b_aESprite->Play();

	this->b_fESpeed			= 0.150f;

	this->b_fECenterY		= 0;
	this->b_fERadius		= hge->Random_Float(50.0f, 80.0f);
	this->b_fEAngle			= 0.0f;
	this->b_fEFriction		= 0.95f;
	this->b_bECenterYSet	= false;
	this->b_bEOscillate		= false;


}

BEnemy::~BEnemy()
{
	delete b_aESprite;

	hge->Release();
}

bool BEnemy::OnLoop(float delta)
{
	b_vEVelocity.x		*= b_fEFriction;
	b_vEVelocity.y		*= b_fEFriction;

	b_vEPosition.x		+= b_vEVelocity.x;

	if(!b_bEOscillate)
		b_vEPosition.y	+= b_vEVelocity.y;
	else
	{
		if(!b_bECenterYSet)
		{
			if(b_vEVelocity.y > -0.000001f && b_vEVelocity.y < 0.000001f)
			{
				b_fECenterY		= b_vEPosition.y;
				b_bECenterYSet	= true;
			}
		}

		b_vEPosition.y	= b_fECenterY + sin(b_fEAngle) * b_fERadius;
		b_fEAngle	   += 2 * delta;
	}

	b_aESprite->Update(delta);

	b_vEVelocity.x		-= b_fESpeed;

	b_aESprite->GetBoundingBox(b_vEPosition.x, b_vEPosition.y, &b_bEBoundingBox);

	return false;

}

void BEnemy::OnRender()
{
	b_aESprite->Render(b_vEPosition.x, b_vEPosition.y);
}

short BEnemy::getHealth()
{
	return this->b_sEHealth;
}

void  BEnemy::setHealth(short Health)
{
	this->b_sEHealth = Health;
}

float BEnemy::getSpeed()
{
	return this->b_fESpeed;
}

void  BEnemy::setSpeed(float Speed)
{
	this->b_fESpeed = Speed;
}

void  BEnemy::setOscillate(bool value)
{
	this->b_bEOscillate = value;
}

hgeRect BEnemy::getBoundingBox()
{
	return this->b_bEBoundingBox;
}

hgeVector BEnemy::getPosition()
{
	return this->b_vEPosition;
}