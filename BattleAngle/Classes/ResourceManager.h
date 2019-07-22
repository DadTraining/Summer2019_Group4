
#pragma once
#include<string>
#include"cocos2d.h"
#include "ui/CocosGUI.h"
using namespace std;
USING_NS_CC;
using namespace ui;

class ResourceManager
{
private:
	static ResourceManager * s_instance;
	ResourceManager();
public:
	
	string m_dataFolderPath;
	map<char, Sprite*> m_sprites;
	map<char, Button*> m_buttons;
	map<char, Label*> m_labels;

	
	~ResourceManager();

	static ResourceManager* GetInstance();
	void init(string path);
	void Load(string fileName);

	Sprite* GetSpriteById(char id);
	Button* GetButtonById(char id);
	Label* GetLabelById(char id);
};

