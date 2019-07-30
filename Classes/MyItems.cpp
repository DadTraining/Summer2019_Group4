#include "MyItems.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
MyItems* MyItems::s_instance = NULL;
MyItems::MyItems()
{
	for (int i = 1; i <= Objects::ITEM_TOTAL; i++) {
		item = new Item(i);
		ListItems.push_back(item);
	}
}

MyItems::~MyItems()
{

}

MyItems * MyItems::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new MyItems();
	}
	return s_instance;
}


