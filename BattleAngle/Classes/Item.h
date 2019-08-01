#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include<iostream>

class Item :public Objects
{
private:
	bool use = false, buy = false;
	int sum =0, id , gold;
public:
	
	Item(int ID);
	~Item();
	void Init() override;
	void Update(float deltaTime) override;
	
	void setBuy(bool buy) {
		this->buy = buy;
	}
	bool getBuy() {
		return this->buy;
	}
	void setUse(bool use) {
		this->use = use;
	}

	bool getUse() {
		return this->use;
	}
	void setSum(int sum) {
		this->sum = sum;
	}
	int getSum() {
		return sum;
	}
	int getId() {
		return this->id;
	}
	int getGold() {
		return gold;
	}
};