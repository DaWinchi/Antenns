
// Antenna.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CAntennaApp:
// Сведения о реализации этого класса: Antenna.cpp
//

class CAntennaApp : public CWinApp
{
public:
	CAntennaApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CAntennaApp theApp;
