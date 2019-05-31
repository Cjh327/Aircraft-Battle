#include "stdafx.h"
#include "CPlane.h"

CPlane::CPlane(int _hp, int _damage, int _speed) : hp(_hp), damage(_damage), speed(_speed) {}

int CPlane::getHp() const {
	return hp;
}

int CPlane::getDamage() const {
	return damage;
}

int CPlane::getSpeed() const {
	return speed;
}

void CPlane::decreaseHp(int x) {
	hp = max(0, hp - x);
}

bool CPlane::isAlive() const {
	return hp > 0;
}