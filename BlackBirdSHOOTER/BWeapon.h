#pragma once

#include <iostream>

#include "BItem.h"

class BWeapon: public BItem 
{
	private:
		int loadedAmmo;
		int damage;
		int maxAmmo;
		float range;

	public:
		BWeapon(void);
		
		BWeapon(const string& name, int id, int loadedAmmo) : BItem(name, id), loadedAmmo(loadedAmmo) 
		{}
		
		virtual ~BWeapon(void);
	
		int getLoadedAmmo(void) const 
		{
			return this->loadedAmmo;
		}

		virtual int getDamage(void) const = 0;

		virtual int getMaxAmmo(void) const = 0;

		virtual float getRange(void) const = 0;
	
		virtual int fire(void) 
		{
			return (this->loadedAmmo>0) ? --this->loadedAmmo : -1;
		}
	
		virtual void reload(void) 
		{
			this->loadedAmmo = this->maxAmmo;
		}
};
