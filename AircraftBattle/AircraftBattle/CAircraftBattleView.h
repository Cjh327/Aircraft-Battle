#pragma once
#include <afxwin.h>
#include "CPlane.h"
class CAircraftBattleView :	public CView
{
private:
	CPlane* pPlane;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

