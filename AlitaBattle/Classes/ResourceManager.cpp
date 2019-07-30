#include "ResourceManager.h"
#include<iostream>
#include<sstream>

ResourceManager * ResourceManager::s_instance = nullptr;

ResourceManager::ResourceManager()
{
	init("res");
}


ResourceManager::~ResourceManager()
{

}

ResourceManager * ResourceManager::GetInstance()
{
	if (s_instance == nullptr) {
		s_instance = new ResourceManager();
	}
	return s_instance;
}

void ResourceManager::init(string path)
{
	//m_dataFolderPath = "res";
	Load("res/Data.bin");
}

void ResourceManager::Load(string fileName)
{
	auto s = FileUtils::getInstance()->getStringFromFile("res/Data.bin");

	istringstream Data(s.c_str());

	//fstream  Data;

	//Data.
	string path1, path2, ignore;
	char id;
	//Data.open("res/Data.bin", ios::in);
	Data >> ignore;
	Data >> path1;
	string path = "res";

	int n = path1[0] - '0';

	for (int i = 0; i<n; i++) {
		Data >> ignore;
		Data >> id;
		Data >> ignore;
		Data >> path1;
		path1.replace(0, 2, path);

		FileUtils::getInstance()->getWritablePath();
		auto sprice = Sprite::create(path1);
		sprice->retain();
		m_sprites.insert(pair<char,Sprite*>(id, sprice));
	}

	Data >> path1;
	Data >> path1;
	n = path1[0] - '0';
	for (int i = 0; i<n; i++) {
		Data >> ignore;
		Data >> id;
		Data >> path1;
		Data >> path1;
		path1.replace(0, 2, path);
		Data >> path2;
		Data >> path2;
		path2.replace(0, 2, path);
		auto button = Button::create(path1, path2);
		button->retain();
		m_buttons.insert(pair<char, Button*>(id, button));
	}
//	Data.close();
}

Sprite * ResourceManager::GetSpriteById(char id)
{
	map<char, Sprite*>::iterator itr;
	for (itr = m_sprites.begin(); itr != m_sprites.end(); itr++) {
		if (itr->first == id) {
			return itr->second;
		}
	}
	return nullptr;
}

Button * ResourceManager::GetButtonById(char id)
{
	map<char, Button*>::iterator itr;
	for (itr = m_buttons.begin(); itr != m_buttons.end(); itr++) {
		if (itr->first == id) {
			return itr->second;
		}
	}
	/*auto ratingButton = ui::Button::create("CloseSelected.png",
		"CloseSelected.png");*/
	return nullptr;
}

Label * ResourceManager::GetLabelById(char id)
{
	/*map<char, Label*>::iterator itr;
	for (itr = m_labels.begin(); itr != m_labels.end(); itr++) {
		if (itr->first == id) {
			return itr->second;
		}
	}*/
	return nullptr;
}
