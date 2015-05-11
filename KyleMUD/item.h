#ifndef _MY_ITEM_H_
#define _MY_ITEM_H_


// THIS //
/*
#ifndef _ITEM_
#define _ITEM_
#include "item.h"
#endif
*/


//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "enum.h"


//=================//
// Not MY Includes //
//=================//
//#include <string>


//========================//
// Item Class Declaration //
//========================//
class item
{
private:
	long long m_itemID;
	EquipmentSlot m_equipmentSlot;
	int m_strBonus, m_agiBonus, m_perBonus, m_wisBonus, m_acBonus;
	std::string m_keyWords;
	std::string m_itemName;
	std::string m_itemDescription;


public:
					item();
					~item();

	void			setStrBonus(int);
	void			setAgiBonus(int);
	void			setPerBonus(int);
	void			setWisBonus(int);
	void			setACBonus(int);
	void			setItemName(std::string);
	void			setDescription(std::string);
	void			setItemKeyWords(std::string);
	void			setEquipmentSlot(EquipmentSlot);

	int				getStrBonus();
	int				getAgiBonus();
	int				getPerBonus();
	int				getWisBonus();
	int				getACBonus();
	bool			checkKeyWords(std::string);
	std::string		getItemName();
	EquipmentSlot	getEquipmentSlot();
	std::string		getDescription();
	std::string		getKeywords();

	
	void			createItemID();
	void			setItemID(long long);
	long long		getItemID();



};






#endif