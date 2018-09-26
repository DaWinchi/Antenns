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
	Graphics grBmp(&bmp);
	grBmp.Clear(Color::Yellow);

	Pen penLines(Color::Red, 1);
	Pen penGreatLines(Color::OrangeRed, 2);

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