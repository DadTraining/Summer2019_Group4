#pragma once
#include"cocos2d.h"
#include "ui\CocosGUI.h"
#include "Item.h"
#include <list> 
using namespace std;



class MyItems
{
private:
	static MyItems *s_instance;
	Item * item;
public:
	MyItems();
	~MyItems();
	list<Item*> ListItems;
	static MyItems* GetInstance();
};