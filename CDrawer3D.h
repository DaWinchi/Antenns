#pragma once
#include <gl/GLU.h>
#include <gl/GL.h>
#include "glut.h"
#include <vector>
#include "CModelDraw.h"


class CDrawer3D
{
public:
	CDrawer3D();
	~CDrawer3D();

	double *angleX, *angleY, *zoom;
	void Draw();
	std::vector<std::vector<Point3D>> *points;

	/*������������� �������� ��������� OpenGl*/
	void InitiateOPGL(CRect & rt, CDC* pdc);
	CRect rect;
	CDC* pDC;

	/*������� ���������� ���������� ������ ���������*/
	BOOL bSetupPixelFormat();
};

