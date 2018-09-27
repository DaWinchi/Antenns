
// AntennaDlg.h: файл заголовка
//

#pragma once
#include "CModelDraw.h"
#include <vector>

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
	CDC *dc;
public:
	afx_msg void OnStnClickedAntenns();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	CRect _rectAntenns;
	CModelDraw _drawerAntenns;
	std::vector<Point> _points;
	std::vector<std::vector<Point3D>> _surfacePoints;
	double _d;
	int _R;

	void InitializeSurface();
	afx_msg void OnBnClickedCreatesurface();
};
