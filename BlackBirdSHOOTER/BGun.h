#pragma once

#include <iostream>

#include "BWeapon.h"

using namespace std;

class BGun : public BWeapon
{

	public:
		BGun(void);
		BGun(const string& name, int id, int ammo): BWeapon(name, id, ammo)
		{}
	
		virtual ~BGun(void);
	
		int getAmmo(void) const;
	
		virtual int getDamage(void) const 
		{
			return this->getDamage();
		}
	
		virtual int getMaxAmmo(void) const 
		{
			return this->getMaxAmmo();
		}
	
		virtual float getRange(void) const 
		{
			return this->getRange();
		}
};
