#pragma once
#include "Objects.h"
class Murad_Monster : public Objects
{
public:

	Murad_Monster(Scene * scene);
	~Murad_Monster();
	void Init() override;
	void Update(float deltaTime) override;
	void Attack();

private:

};

#pragma once
