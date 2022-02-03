//Подключаем библиотеки для работы с математическими функциями и константами, классом string, vector, wstring
#include <string>
#include <vector>
#include <cvt/wstring>
#define _USE_MATH_DEFINES
#include "math.h"

#pragma once

using namespace std;

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы

// CMFCApplication1App:
// Сведения о реализации этого класса: MFCApplication1.cpp
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;
