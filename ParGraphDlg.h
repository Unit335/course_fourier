#pragma once
#include <afxwin.h>
#include "framework.h"

class MFC1ParGrDlg : //Класс отрисовки графика функции сигнала
	public CStatic //Родитель-класс
{
public:
	MFC1ParGrDlg();//Конструктор
	~MFC1ParGrDlg();//Деструктор
	afx_msg void OnPaint();//Функция отрисовки окна
	DECLARE_MESSAGE_MAP() //Порядок выполнения операций
};