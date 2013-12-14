#pragma once

#include <iostream>

#include "BItem.h"

using namespace std;

class BItem
{  
	private:
		string name;
		int itemID;

	public:
		BItem(void);
		
		BItem(const string& name, int id): name(name), itemID(id) 
		{}
		
		~BItem(void);
    
		const string& getName(void) const 
		{ 
			return this->name; 
		}
    
		int getID(void) const 
		{ 
			return this->itemID;
		}
};
