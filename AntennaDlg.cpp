
// AntennaDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Antenna.h"
#include "AntennaDlg.h"
#include "afxdialogex.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define M_PI   3.141592653589793238462643

// Диалоговое окно CAntennaDlg
CRITICAL_SECTION cs;



CAntennaDlg::CAntennaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANTENNA_DIALOG, pParent)
	, _d(1)
	, _R(100)
	, _lamda(0.5)
	, _isAnimate(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntennaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANTENNS, _drawerAntenns);
	DDX_Text(pDX, IDC_EDIT1, _d);
	DDX_Text(pDX, IDC_EDIT2, _R);
	DDX_Control(pDX, IDC_3D2, _drawer2D);
	DDX_Text(pDX, IDC_LAMDA, _lamda);
	DDX_Check(pDX, IDC_CHECK1, _isAnimate);
}

BEGIN_MESSAGE_MAP(CAntennaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CLEAR, &CAntennaDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_CHECK1, &CAntennaDlg::OnBnClickedCheck1)
	ON_STN_CLICKED(IDC_ANTENNS, &CAntennaDlg::OnStnClickedAntenns)
	ON_BN_CLICKED(IDC_UPDATE, &CAntennaDlg::OnBnClickedUpdate)
END_MESSAGE_MAP()


// Обработчики сообщений CAntennaDlg

BOOL CAntennaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	InitializeCriticalSection(&cs);
	CDC* dc = GetDlgItem(IDC_3D)->GetDC();
	GetDlgItem(IDC_3D)->GetClientRect(&PicSurface);
	_drawer3d.InitiateOPGL(PicSurface, dc);
	angleX = 0;
	angleY = 0;
	zoom = 1;
	_drawer3d.angleX = &angleX;
	_drawer3d.angleY = &angleY;
	_drawer3d.zoom = &zoom;
	_drawer3d.points = &_surfacePoints;
	oldPoint.x = 0;
	oldPoint.y = 0;

	GetDlgItem(IDC_ANTENNS)->GetWindowRect(&_rectAntenns);

	_xmax = 5;
	_xmin = -5;
	_ymax = 5;
	_ymin = -5;
	_drawerAntenns.xmax = _xmax;
	_drawerAntenns.xmin = _xmin;
	_drawerAntenns.ymax = _ymax;
	_drawerAntenns.ymin = _ymin;


	_drawer2D._image = &_points2D;
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CAntennaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CAntennaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAntennaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	int dX = (point.x - oldPoint.x);
	int dY = (point.y - oldPoint.y);
	bool IsInRect = (point.x > PicSurface.left) && (point.x < PicSurface.right)
		&& (point.y > PicSurface.top) && (point.y < PicSurface.bottom);

	oldPoint.x = point.x;
	oldPoint.y = point.y;
	if (IsInRect)
	{
		if (nFlags & MK_LBUTTON)
		{
			angleX += 0.5*dY;
			angleY += 0.5*dX;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CAntennaDlg::InitializeSurface()
{
	_surfacePoints.clear();
	std::vector<Point3D> buffer;
	const size_t width = 201, height = 201;
	Point3D pt;
	pt.x = 0;
	pt.y = 0;
	pt.z = 0;
	buffer.resize(width, pt);
	_surfacePoints.resize(height, buffer);
}

void CAntennaDlg::InitializeSurfaceSphere()
{
	int height = _surfacePoints.size() - 1,
		width = _surfacePoints[0].size() - 1;

	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			Point3D pt;
			double scal = (double)_R / ((double)width - 1.0)*2.0;
			pt.x = (double)((j - width / 2))*scal;
			pt.y = (double)((i - height / 2))*scal;
			if ((pt.x*pt.x + pt.y*pt.y) >= _R*_R) pt.z = 0;
			else
			{
				pt.z = sqrt(_R*_R - pt.x*pt.x - pt.y*pt.y);
			}
			_surfacePoints[i][j] = pt;
		}
		double k = 0;
	}
}

void CAntennaDlg::CreateDistribution()
{
	int height = _surfacePoints.size() - 1,
		width = _surfacePoints[0].size() - 1;
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (_surfacePoints[i][j].z > 0 && !_points.empty())
			{ 
				double re = 0, im = 0;
				for (int antenna = 0; antenna < _points.size(); antenna++)
				{
					Point3D r;
					r.x = _surfacePoints[i][j].x - (double)_points[antenna].X;
					r.y = _surfacePoints[i][j].y - (double)_points[antenna].Y;
					r.z = _surfacePoints[i][j].z;
					double moduleR = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
					re += cos((double)2.0*M_PI / _lamda * moduleR) / moduleR;
					im += -sin((double)2.0*M_PI / _lamda * moduleR) / moduleR;
				}
				_surfacePoints[i][j].z = sqrt(re*re + im * im);
			}
		}
	}
}


void CAntennaDlg::OnTimer(UINT_PTR nIDEvent)
{
	EnterCriticalSection(&cs);
	if(_isAnimate)	angleY += 2;
	_drawer3d.Draw();
	LeaveCriticalSection(&cs);

	CDialog::OnTimer(nIDEvent);
}


BOOL CAntennaDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	zoom += zDelta / 1000.;
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CAntennaDlg::Initialize2DSurface()
{
	_points2D.clear();
	size_t width = _surfacePoints[0].size(),
		height = _surfacePoints.size();
	for (size_t i = 0; i < height; i++)
	{
		std::vector<double> bufferLine;
		for (size_t j = 0; j < width; j++)
		{
			bufferLine.push_back(_surfacePoints[i][j].z);
		}
		_points2D.push_back(bufferLine);
	}
}


void CAntennaDlg::OnBnClickedClear()
{
	_points.clear();
	_drawerAntenns._points.clear();
	_drawerAntenns.Update();
	OnStnClickedAntenns();
}


void CAntennaDlg::OnBnClickedCheck1()
{
	UpdateData(TRUE);
}


void CAntennaDlg::OnStnClickedAntenns()
{
	UpdateData(TRUE);
	_points = _drawerAntenns._points;
	for (size_t i = 0; i < _points.size(); i++)
	{
		_points[i].X *= _d;
		_points[i].Y *= _d;

	}
	InitializeSurface();
	InitializeSurfaceSphere();
	CreateDistribution();
	Initialize2DSurface();
	_drawer2D.RedrawWindow();
	SetTimer(1, 30, NULL);
}


void CAntennaDlg::OnBnClickedUpdate()
{
	UpdateData(TRUE);
	_points = _drawerAntenns._points;
	for (size_t i = 0; i < _points.size(); i++)
	{
		_points[i].X *= _d;
		_points[i].Y *= _d;

	}
	InitializeSurface();
	InitializeSurfaceSphere();
	CreateDistribution();
	Initialize2DSurface();
	_drawer2D.RedrawWindow();
	SetTimer(1, 30, NULL);
}
