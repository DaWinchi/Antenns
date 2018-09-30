#include "stdafx.h"
#include "CDrawer2D.h"
#include <math.h>

using namespace Gdiplus;
ULONG_PTR token2;
CDrawer2D::CDrawer2D()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token2, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"Îøèáêà", MB_ICONERROR);
	}
}


CDrawer2D::~CDrawer2D()
{
	GdiplusShutdown(token2);
}


void CDrawer2D::DrawItem(LPDRAWITEMSTRUCT RECT)
{
	Graphics gr(RECT->hDC);
	if (_image[0].size()>0)
	{
		size_t width = _image[0][0].size();
		size_t height = _image->size();
		xmin = 0;
		xmax = width;
		ymin = 0;
		ymax = height;

		double max = 0;
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				if (_image[0][i][j] > max) max = _image[0][i][j];
			}
		}

		Bitmap bmpBuffer(width, height);

//#pragma omp parallel for
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				double val = _image[0][i][j]/max*255.0;
				Color color;
				color = Color::MakeARGB(255, val, val, val);
				bmpBuffer.SetPixel(j, height -1 - i, color);
			}
		}
		Rect rect(0, 0, RECT->rcItem.right, RECT->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}	
}


REAL CDrawer2D::X(LPDRAWITEMSTRUCT RECT, float x)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*((x)-xmin);
}

REAL CDrawer2D::Y(LPDRAWITEMSTRUCT RECT, float y)
{
	return -(REAL)(RECT->rcItem.bottom) / (ymax - ymin)*((y)-ymax);
}

REAL CDrawer2D::Width(LPDRAWITEMSTRUCT RECT, float width)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*width;
}

REAL CDrawer2D::Height(LPDRAWITEMSTRUCT RECT, float height)
{
	return (REAL)(RECT->rcItem.bottom) / (ymax - ymin)*height;
}

void CDrawer2D::Update()
{
	RedrawWindow();
}