//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "item.h"



//==========//
// Forwards //
//==========//
using namespace std;

long long getRandID();		//random number - Unique 12 digit ID


//=======================//
// Item Class Definition //
//=======================//
item::item()
{
	createItemID();
	m_equipmentSlot = NOEQUIP;
	m_strBonus = 0;
	m_agiBonus = 0;
	m_perBonus = 0;
	m_wisBonus = 0;
	m_acBonus = 0;
	m_itemName = "Nothing";
	m_itemDescription = "A whole lot of nothing";
	m_keyWords = "nothing";
}
item::~item()
{
}

void			item::setStrBonus(int x)
{
	m_strBonus = x;
}
void			item::setAgiBonus(int x)
{
	m_agiBonus = x;
}
void			item::setPerBonus(int x)
{
	m_perBonus = x;
}
void			item::setWisBonus(int x)
{
	m_wisBonus = x;
}
void			item::setACBonus(int x)
{
	m_acBonus = x;
}
void			item::setItemName(string str)
{
	m_itemName = str;
}
void			item::setDescription(string str)
{
	m_itemDescription = str;
}
void			item::setItemKeyWords(string str)
{
	m_keyWords = str;
}
void			item::setEquipmentSlot(EquipmentSlot eqs)
{
	m_equipmentSlot = eqs;
}


int				item::getStrBonus()
{
	return m_strBonus;
}
int				item::getAgiBonus()
{
	return m_agiBonus;
}
int				item::getPerBonus()
{
	return m_perBonus;
}
int				item::getWisBonus()
{
	return m_wisBonus;
}
int				item::getACBonus()
{
	return m_acBonus;
}
bool			item::checkKeyWords(string str2)
{
	string str1 = m_keyWords;
	string::iterator it;
	size_t result;
	for (it = str1.begin(); it != str1.end(); ++it)
	{
		*it = toupper(*it);
	}
	for (it = str2.begin(); it != str2.end(); ++it)
	{
		*it = toupper(*it);
	}
	
	result = str1.find(str2);

	if (result != string::npos) 
	{return true;}
	else
	{return false;}
}
string			item::getItemName()
{
	return m_itemName;
}
EquipmentSlot	item::getEquipmentSlot()
{
	return m_equipmentSlot;
}
string			item::getDescription()
{
	return m_itemDescription;
}
string			item::getKeywords()
{
	return m_keyWords;
}

void			item::createItemID()
{
	m_itemID = getRandID();
}
void			item::setItemID(long long x)
{
	m_itemID = x;
}
long long		item::getItemID()
{
	return m_itemID;
}
