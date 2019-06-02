#pragma once
#include "GameObject.h"

class CPlane : public CGameObject {
protected:
	int hp;
	int damage;
	int speed;

public:
	CPlane(int _hp, int _damage, int _speed);
	int getHp() const;
	int getSpeed() const;
	int getDamage() const;
	void decreaseHp(int x);
	bool isAlive() const;
};

