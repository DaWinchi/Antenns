
// AntennaDlg.h: файл заголовка
//

#pragma once
#include "CModelDraw.h"
#include <vector>
#include "CDrawer3D.h"
#include "CDrawer2D.h"

// Диалоговое окно CAntennaDlg
class CAntennaDlg : public CDialogEx
{
// Создание
public:
	CAntennaDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANTENNA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//размеры антенного полотна
	int _xmax, _ymax, _xmin, _ymin;
	//положение указателя на полотне
	CPoint _pointMouse;
	CWnd * PicWndSurface;
	CDC * PicDcSurface;
	CRect PicSurface;
	HGLRC glRCSurface;
	double angleX, angleY, zoom;
	CPoint oldPoint;
	CDrawer3D _drawer3d;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	CRect _rectAntenns;
	CModelDraw _drawerAntenns;
	std::vector<Point> _points;
	std::vector<std::vector<Point3D>> _surfacePoints;
	std::vector<std::vector<double>> _points2D;
	double _d;
	int _R;

	void InitializeSurface();
	void InitializeSurfaceSphere();
	void CreateDistribution();
	void Initialize2DSurface();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CDrawer2D _drawer2D;
	double _lamda;
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCheck1();
	BOOL _isAnimate;
	afx_msg void OnStnClickedAntenns();
	afx_msg void OnBnClickedUpdate();
};
