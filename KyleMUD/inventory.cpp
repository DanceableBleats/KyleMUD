//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "inventory.h"
#include "item.h"



//=================//
// Not My Includes //
//=================//
//#include <iostream>
//#include <vector>


//==========//
// Forwards //
//=========//
using namespace std;

int getRandID();			//random 12-digit ID
int getRand(int, int);		//random number in range


//================================//
// Inventory Class Implementation //
//================================//
long long inventory::getInvID()
{
	return m_inventoryID;
}

void inventory::setInvID(long long x)
{
	m_inventoryID = x;
}

// DEPRECIATING
/*void inventory::createNewInvID()
{
	int x = getRand(1, 9);
	for (int i = 1; i < 10; ++i)
	{
		x += (pow((float)10, i) + getRand(1, 9));
	}


	m_inventoryID = x;

}
*/

//=======================================//
// Player Inventory Class Implementation //
//=======================================//
//search inventory / equipment lists
bool playerInventory::searchInv(string str, item **x, vector<item*>::iterator *it1)
{
	item *p_item; 

	if (!m_itemList.empty())
	{
		for (*it1 = m_itemList.begin(); *it1 != m_itemList.end(); ++(*it1))
		{
			p_item = **it1;
			if (p_item->checkKeyWords(str))
			{
				*x = p_item;
				return 1;
			}
		}
	}
	else 
	{
	return 0;
	}
}
bool playerInventory::searchEquip(string str, item **x, map<EquipmentSlot, item*>::iterator *it1)
{
	item *p_equip;
	if ( !m_equippedItems.empty())
	{
		for ( *it1 = m_equippedItems.begin(); *it1 != m_equippedItems.end(); ++(*it1))
		{
			p_equip = (*it1)->second;
			if (p_equip->checkKeyWords(str))
			{
				*x = p_equip;
				return 1;
			}
		}
	}
	else
	{return 0;}	
}


//add items / equipment to lists
bool playerInventory::addItem(item* p_item)
{
	m_itemList.push_back(p_item);
	return true;
}
bool playerInventory::addEquip(item *p_equip)
{	
	m_equippedItems.insert( pair<EquipmentSlot, item*>(p_equip->getEquipmentSlot(), p_equip) );
	return 1;
}


//remove items / equipment from lists
bool playerInventory::removeItem(vector<item*>::iterator *it1)
{
	m_itemList.erase(*it1);
	return 1;
}
bool playerInventory::removeEquip(map<EquipmentSlot, item*>::iterator *it1)
{
	m_equippedItems.erase(*it1);
	return 1;
}

//Show item / equipment list
void playerInventory::showInventory()
{
	vector<item*>::iterator it1;
	for ( it1 = m_itemList.begin(); it1 != m_itemList.end(); ++it1 )
	{
		item *p_item = *it1;
		cout << p_item->getItemName() << endl;
	}
}
void playerInventory::showEquipment()
{
	map<EquipmentSlot, item*>::iterator it1;
	for ( it1 = m_equippedItems.begin(); it1 != m_equippedItems.end(); ++it1 )
	{
		cout << it1->second->getItemName() << " " << it1->second->getEquipmentSlot()<< endl;
	}
}

//check for previously equipped equipment
bool playerInventory::checkEquipped(EquipmentSlot eq, item **p_item)
{
	map<EquipmentSlot, item*>::iterator it;

	for ( it = m_equippedItems.begin(); it != m_equippedItems.end(); ++it )
	{
		if ( eq == it->second->getEquipmentSlot())
		{ 
			*p_item = it->second;
			return 1;
		}
		
	}
	return 0;
	
}

vector<item*>*	playerInventory::getItemListPtr()
{
	return &m_itemList;
}

map<EquipmentSlot, item*>* playerInventory::getEqListPtr()
{
	return &m_equippedItems;
}




//=====================================//
// Room Inventory Class Implimentation //
//=====================================//

void roomInventory::addItem(item *p_item)
{
	m_itemList.push_back(p_item);

}

bool roomInventory::searchInv(string str, item **x, vector<item*>::iterator *it1)
{
	item *p_item; 

	if (!m_itemList.empty())
	{
		for (*it1 = m_itemList.begin(); *it1 != m_itemList.end(); ++(*it1))
		{
			p_item = **it1;
			if (p_item->checkKeyWords(str))
			{
				*x = p_item;
				return 1;
			}
		}
	}
	else 
	{
	return 0;
	}
}

bool roomInventory::removeItem(vector<item*>::iterator *it1)
{
	m_itemList.erase(*it1);
	return 1;
}

void roomInventory::showInventory()
{
	vector<item*>::iterator it1;
	for ( it1 = m_itemList.begin(); it1 != m_itemList.end(); ++it1 )
	{
		item *p_item = *it1;
		cout << p_item->getItemName() << endl;
	}
}