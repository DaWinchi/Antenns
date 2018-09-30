#include "stdafx.h"
#include "CDrawer3D.h"


CDrawer3D::CDrawer3D()
{
}


CDrawer3D::~CDrawer3D()
{
	wglMakeCurrent(pDC->GetSafeHdc(), 0);
	wglDeleteContext(wglGetCurrentContext());
}

void CDrawer3D::Draw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 0.5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200, 200, -200, 200, -200, 200);

	glTranslated(0.f, 0.f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotated(*angleX, 1, 0, 0);
	glRotated(*angleY, 0, 1, 0);
	glScaled(*zoom, *zoom, *zoom);
	glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);//
	glBegin(GL_QUADS);
	
	double max = 0, width = points[0][0].size()/2;
	for (int i = 0; i < points[0].size(); i++)
	{
		for (int j = 0; j < points[0][i].size(); j++)
		{
			if (points[0][i][j].z > max) max = points[0][i][j].z;
		}
	}

	for (int i = 0; i < points[0].size(); i++)
	{
		for (int j = 0; j < points[0][i].size(); j++)
		{
			points[0][i][j].z = points[0][i][j].z / max * width;
		}
	}

	for (int i = 0; i < points[0].size(); i++)
	{
		for (int j = 0; j < points[0][i].size(); j++)
		{
			glColor3d(255, 255, 255);
			int iright = i + 1;
			int jup = j + 1;
			if (iright == points[0].size())
			{
				iright -=2 ;
			}
			if (jup == points[0][i].size())
			{
				jup -= 2;
			}
			glColor3f(points[0][i][j].z / max, 0, 0);
			glVertex3d(points[0][i][j].x , points[0][i][j].y,points[0][i][j].z);
			glColor3f(points[0][iright][j].z / max, 0, 0);
			glVertex3d(points[0][iright][j].x, points[0][iright][j].y, points[0][iright][j].z);
			glColor3f(points[0][iright][jup].z / max, 0, 0);
			glVertex3d(points[0][iright][jup].x, points[0][iright][jup].y, points[0][iright][jup].z);
			glColor3f(points[0][i][jup].z / max, 0, 0);
			glVertex3d(points[0][i][jup].x, points[0][i][jup].y, points[0][i][jup].z);
		}
	}
	glEnd();
	/*glBegin(GL_LINES);
	glColor3d(1.0, 0, 0);
	glVertex3d(1,0,1)
	glEnd();*/
	glFinish();
	SwapBuffers(wglGetCurrentDC());
}

void CDrawer3D::InitiateOPGL(CRect & rt, CDC* pdc)
{
	rect = rt;
	pDC = pdc;
	HGLRC hrc; //rendering context for OpGL(�������������� �������� ��� OpGl)
	if (!bSetupPixelFormat())
	{
		return;
	}

	hrc = wglCreateContext(pDC->GetSafeHdc()); //������������� ��� ����������� cdc
	ASSERT(hrc != NULL); //���� �������� ������������������, �� ���������� ���������, ����� ����������� ����������

	wglMakeCurrent(pDC->GetSafeHdc(), hrc); //��������� ��������� �������� ���������

	glViewport(0, 0, rect.right, rect.bottom);

	glCullFace(GL_FRONT);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0, 0.0, 0.0, 1.0);


}

BOOL CDrawer3D::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |          // support OpenGL
		PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd)) == 0)
	{
		return FALSE;
	}

	if (SetPixelFormat(pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}