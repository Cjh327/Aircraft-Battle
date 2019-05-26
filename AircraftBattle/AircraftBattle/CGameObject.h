#pragma once
#include <afx.h>
class CGameObject : public CObject
{
protected:
	CPoint point;
public:
	CGameObject(int x, int y);
};

