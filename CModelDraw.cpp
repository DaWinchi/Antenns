#include "stdafx.h"
#include "CModelDraw.h"
#include <math.h>

using namespace Gdiplus;
ULONG_PTR token1;
CModelDraw::CModelDraw()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token1, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"Îøèáêà", MB_ICONERROR);
	}
}


CModelDraw::~CModelDraw()
{
	GdiplusShutdown(token1);
}


void CModelDraw::DrawItem(LPDRAWITEMSTRUCT RECT)
{
	Graphics gr(RECT->hDC);
	Bitmap bmp(RECT->rcItem.right, RECT->rcItem.bottom, &gr);
	_width = RECT->rcItem.right;
	_height = RECT->rcItem.bottom;
	Graphics grBmp(&bmp);
	grBmp.Clear(Color::White);

	Pen penLines(Color::Black, 1);
	Pen penGreatLines(Color::LightGreen, 2);

	for (int i = 1; i < xmax; i++)
	{
		grBmp.DrawLine(&penLines, X(RECT, i), Y(RECT, ymin), X(RECT, i), Y(RECT, ymax));
	}

	for (int i = xmin +1; i < 0; i++)
	{
		grBmp.DrawLine(&penLines, X(RECT, i), Y(RECT, ymin), X(RECT, i), Y(RECT, ymax));
	}

	for (int i = 1; i < ymax; i++)
	{
		grBmp.DrawLine(&penLines, X(RECT, xmin), Y(RECT, i), X(RECT, xmax), Y(RECT, i));
	}

	for (int i = ymin + 1; i < 0; i++)
	{
		grBmp.DrawLine(&penLines, X(RECT, xmin), Y(RECT, i), X(RECT, xmax), Y(RECT, i));
	}
	
	grBmp.DrawLine(&penGreatLines, X(RECT, xmin), Y(RECT, 0), X(RECT, xmax), Y(RECT, 0));
	grBmp.DrawLine(&penGreatLines, X(RECT, 0), Y(RECT, ymin), X(RECT, 0), Y(RECT, ymax));

	if (!_points.empty())
	{
		SolidBrush brushDot(Color::Red);
		for (size_t i = 0; i < _points.size(); i++)
		{
			grBmp.FillEllipse(&brushDot, X(RECT, _points[i].X) - 6.f, Y(RECT, _points[i].Y) - 6.f, 12.f, 12.f);
		}
	}
	
	gr.DrawImage(&bmp, 0, 0);
}


REAL CModelDraw::X(LPDRAWITEMSTRUCT RECT, float x)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*((x)-xmin);
}

REAL CModelDraw::Y(LPDRAWITEMSTRUCT RECT, float y)
{
	return -(REAL)(RECT->rcItem.bottom) / (ymax - ymin)*((y)-ymax);
}

REAL CModelDraw::Width(LPDRAWITEMSTRUCT RECT, float width)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*width;
}

REAL CModelDraw::Height(LPDRAWITEMSTRUCT RECT, float height)
{
	return (REAL)(RECT->rcItem.bottom) / (ymax - ymin)*height;
}

void CModelDraw::Update()
{
	RedrawWindow();
}
BEGIN_MESSAGE_MAP(CModelDraw, CStatic)
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CModelDraw::OnLButtonDown(UINT nFlags, CPoint point)
{
	Point pt;
	double d0 = pixelToX(point.x), d1, doubInt;
	d1 = modf(d0, &doubInt);
	if (d1 > 0)
	{
		if (d1 < 0.5) pt.X = (int)doubInt;
		else pt.X = (int)++doubInt;
	}
	else
	{
		if (fabs(d1) < 0.5) pt.X = (int)doubInt;
		else pt.X = (int)--doubInt;
	}

	d0 = pixelToY(point.y);
	d1 = modf(d0, &doubInt);
	if (d1 > 0)
	{
		if (d1 < 0.5) pt.Y = (int)doubInt;
		else pt.Y = (int)++doubInt;
	}
	else
	{
		if (fabs(d1) < 0.5) pt.Y = (int)doubInt;
		else pt.Y = (int)--doubInt;
	}
	if (!_points.empty())
	{
		int position;
		bool check = false;
		for (size_t i = 0; i < _points.size(); i++)
		{
			if (_points[i].X == pt.X && _points[i].Y == pt.Y)
			{
				check = true;
				position = i;
				break;
			}
		}
		if (!check) _points.push_back(pt);
		else
		{
			_points.erase(_points.begin()+position);
		}
	}
	else _points.push_back(pt);
	Update();
	
	CStatic::OnLButtonDown(nFlags, point);
}

double CModelDraw::pixelToX(double xPx)
{
	return (xmax - xmin) / _width*xPx + xmin;
}

double CModelDraw::pixelToY(double yPx)
{
	return -(ymax - ymin) / _height * yPx + ymax;
}