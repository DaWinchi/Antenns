#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>
using namespace Gdiplus;
using namespace std;

struct Point3D { double x, y, z; };
class CModelDraw : public CStatic
{

public:
	double xmin, xmax, ymin, ymax;
	int _width, _height;
	std::vector<Point> _points;
	CModelDraw();
	~CModelDraw();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	void Update();
	REAL X(LPDRAWITEMSTRUCT RECT, float x);
	REAL Y(LPDRAWITEMSTRUCT RECT, float y);
	REAL Width(LPDRAWITEMSTRUCT RECT, float width);
	REAL Height(LPDRAWITEMSTRUCT RECT, float height);
	double pixelToX(double xPx);
	double pixelToY(double yPx);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

