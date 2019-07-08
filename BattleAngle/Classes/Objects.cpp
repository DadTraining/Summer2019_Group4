
#include "Objects.h"

Objects::Objects()
{
	this->m_dame;
	this->m_hp;
	this->m_dame;
	this->m_isAlive = true;
}

Objects::~Objects()
{
}

void Objects::Init()
{

}

void Objects::Update()
{
}

void Objects::setSprite(Sprite* m_sprite)
{
	this->m_sprite = m_sprite;
}

Sprite * Objects::getSprite()
{
	return this->m_sprite;
}

void Objects::setHP(int* m_hp)
{
	this->m_hp = m_hp;
}

int * Objects::getHP()
{
	return this->m_hp;
}

void Objects::setDame(int* m_dame)
{
	this->m_dame = m_dame;
}

int * Objects::getDame()
{
	return this->m_dame;
}
