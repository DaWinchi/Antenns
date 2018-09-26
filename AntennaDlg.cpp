
// AntennaDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Antenna.h"
#include "AntennaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAntennaDlg



CAntennaDlg::CAntennaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANTENNA_DIALOG, pParent)
	, _d(1)
	, _R(100)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntennaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANTENNS, _drawerAntenns);
	DDX_Text(pDX, IDC_EDIT1, _d);
	DDX_Text(pDX, IDC_EDIT2, _R);
}

BEGIN_MESSAGE_MAP(CAntennaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_ANTENNS, &CAntennaDlg::OnStnClickedAntenns)
	ON_WM_MOUSEMOVE()
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
	dc = GetDlgItem(IDC_ANTENNS)->GetDC();
	GetDlgItem(IDC_ANTENNS)->GetWindowRect(&_rectAntenns);
	_xmax = 5;
	_xmin = -5;
	_ymax = 5;
	_ymin = -5;
	_drawerAntenns.xmax = _xmax;
	_drawerAntenns.xmin = _xmin;
	_drawerAntenns.ymax = _ymax;
	_drawerAntenns.ymin = _ymin;


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



void CAntennaDlg::OnStnClickedAntenns()
{
	Point pt1(-1,0);
	Point pt2(1, 0);
	_points.clear();
	_points.push_back(pt1);
	_points.push_back(pt2);
}


void CAntennaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	bool IsInRect = (point.x > _rectAntenns.left) && (point.x < _rectAntenns.right)
		&& (point.y > _rectAntenns.top) && (point.y < _rectAntenns.bottom);
	CPoint bufferPoint(point.x - _rectAntenns.left, point.y - _rectAntenns.top);
	if (IsInRect) 
		_pointMouse = bufferPoint;

	CDialogEx::OnMouseMove(nFlags, point);
}

double CAntennaDlg::pixelToX(double xPx)
{
	return (_xmax - _xmin) / _rectAntenns.Width()*xPx + _xmin;
}

void CAntennaDlg::CreateXY()
{

}
