#pragma once
#include <afxwin.h>
#include "framework.h"

class MFC1SpecGrDlg : //Класс отрисовки графика функции сигнала
	public CStatic //Родитель-класс
{
public:
	MFC1SpecGrDlg();//Конструктор
	~MFC1SpecGrDlg();//Деструктор
	afx_msg void OnPaint();//Функция отрисовки окна
	DECLARE_MESSAGE_MAP() //Порядок выполнения операций
};