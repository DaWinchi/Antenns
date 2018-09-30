#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>
using namespace Gdiplus;
using namespace std;

class CDrawer2D : public CStatic
{

public:
	double xmin, xmax, ymin, ymax;
	int *_R;
	std::vector<std::vector<double>>* _image;
	CDrawer2D();
	~CDrawer2D();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void Update();
	REAL X(LPDRAWITEMSTRUCT RECT, float x);
	REAL Y(LPDRAWITEMSTRUCT RECT, float y);
	REAL Width(LPDRAWITEMSTRUCT RECT, float width);
	REAL Height(LPDRAWITEMSTRUCT RECT, float height);

};

