#include "stdafx.h"
#include "CPlane.h"


CPlane::CPlane() {}

CPlane::CPlane(int _hp, int _damage, int _speedX, int _speedY) : hp(_hp), maxHp(_hp), damage(_damage), speedX(_speedX), speedY(_speedY) {}

int CPlane::getHp() const {
	return hp;
}

int CPlane::getDamage() const {
	return damage;
}

int CPlane::getSpeedX() const {
	return speedX;
}

int CPlane::getSpeedY() const {
	return speedY;
}

void CPlane::decreaseHp(int x) {
	hp = max(0, hp - x);
}

void CPlane::increaseHp(int x) {
	hp = min(maxHp, hp + x);
}

bool CPlane::isAlive() const {
	return hp > 0;
}