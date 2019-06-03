#pragma once
#include "GameObject.h"

class CPlane : public CGameObject {
protected:
	int hp;
	int damage;
	int speedX;
	int speedY;

public:
	CPlane();
	CPlane(int _hp, int _damage, int _speedX, int _speedY);
	int getHp() const;
	int getSpeedX() const;
	int getSpeedY() const;
	int getDamage() const;
	void decreaseHp(int x);
	bool isAlive() const;
};

