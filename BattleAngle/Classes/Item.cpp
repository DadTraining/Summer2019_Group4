#include "Item.h"

Item::Item(int ID)
{
	id = ID;
	if (ID == ID_DART1) {
		//Sprite* sprite = Sprite::create("res/shop/PNG/Dart1.png");
		this->m_sprite = Sprite::create("res/shop/PNG/Dart1.png");
		this->setDame(2);
		this->setHP(0);
		this->gold = 1000;
	}
	if (ID == ID_DART2) {
		//Sprite* sprite = Sprite::create("res/shop/PNG/Dart2.png");
		this->m_sprite = Sprite::create("res/shop/PNG/Dart2.png");
		this->setDame(4);
		this->setHP(0);
		this->gold = 1500;
	}
	if (ID == ID_DART3) {
		//Sprite* sprite = Sprite::create("res/shop/PNG/Dart3.png");
		this->m_sprite = Sprite::create("res/shop/PNG/Dart3.png");
		this->setDame(6);
		this->setHP(0);
		this->gold = 2000;
	}
	if (ID == ID_DART4) {
		//Sprite* sprite = Sprite::create("res/shop/PNG/Dart4.png");
		this->m_sprite = Sprite::create("res/shop/PNG/Dart4.png");
		this->setDame(8);
		this->setHP(0);
		this->gold = 3000;
	}
	if (ID == ID_BottleBlood) {
		//Sprite* sprite = Sprite::create("res/shop/PNG/Blood.png");
		this->m_sprite = Sprite::create("res/shop/PNG/Blood.png");
		this->setDame(0);
		this->setHP(10);
		this->gold = 200;
	}
	this->m_sprite->retain();
}

Item::~Item()
{
}

void Item::Init()
{
}

void Item::Update(float deltaTime)
{
}
