#pragma once
//Подключаем заголовок программы, заголовок подпрограмм расчётов, отрисовки графиков, описания модальных окон "Задание" и "Сохранение"
#include "course.h"
#include "MFC1GraphDlg.h"
#include "ParGraphDlg.h"
#include "SpecGraphDlg.h"
#include "CTaskDlg.h"
#include "SaveGraph.h"

class CMFCApplication1Dlg : public CDialogEx
{
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon; // переменная класса хранения иконки программы
	virtual BOOL OnInitDialog(); // переменная инициализации диалогового окна
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam),
					OnPaint(); // функция отрисовки окна
	DECLARE_MESSAGE_MAP()
public:
	m_par funcs; // структура хранения данных параметров функций
	Graphics Pnt; // объявление переменной класса расчётов координат для движения данных в эту подпрограмму
	MFC1ParGrDlg gr_Par; // переменная класса отрисовки графика функции сигнала
	MFC1SpecGrDlg gr_Spec; // переменная класса отрисовки графика ДПФ
	virtual void OnOK(); // функция настройки действия нажатия на Enter/кнопку ОК
	void	OnTimer(UINT_PTR nIDEvent), // функция настройки таймера
			StopTimer(), // собственная функция остановки таймера
			StartTimer();// собственная функция запуска таймера
	bool	Drawing(); // собственная функция запуска отрисовки графиков
	int m_int_edit_k = 10, // переменная количества точек отсчёта для проверки
		dr_p_1, // переменная счётчика точек графика функции сигнала
		dr_p_2; // переменная счётчика точек графика ДПФ
	double Fd = 10000000.; // переменная, хранящая значение параметра дискретизации в Гц
	BOOL	ANIMATEBOX_CHECK,
			M_CHECK_GR,
			ANIMATE_ERASE; // переменные класса BOOL кнопки анимации и стирания графиков
	CButton ctrl_animatebox,
			m_ctrl_check_gr,
			ctrl_reset_1,
			ctrl_reset_2,
			ctrl_erase; // переменные для настройки кнопок анимации, проверки отсчётов, сброса и стирания графиков.
	CListBox ctrl_list_view; // переменная для настройки листа значений масштаба оси OY для графика ДПФ в ListBox
	CStatic m_ctrl_static_check,
			f_txt,
			Fm_txt,
			m_txt,
			N_txt; // переменные для настройки элементов Static
	CSliderCtrl slider_f,
				slider_Fm,
				slider_m,
				slider_N,
				slider_ox,
				slider_oy; // переменные для настройки интерактивного ввода данных Slider
	CEdit	ctrl_edit_f,
			ctrl_edit_Fm,
			ctrl_edit_m,
			ctrl_edit_N,
			ctrl_edit_oy,
			ctrl_edit_ox; // переменные для настройки стандартного ввода данных EditBox
	CString m_text_static_check,
			Text_N,
			Text_m,
			Text_Fm,
			Text_f,
			cs_edit_f,
			cs_edit_Fm,
			cs_edit_m,
			cs_edit_N,
			cs_edit_ox,
			cs_edit_oy; // переменные для хранения записей в элементах Static и EditBox
	afx_msg void
		OnBnClickedButtonReset(),
		OnBnClickedButtonReset2(),
		OnBnClickedButtonErase(),
		OnBnClickedAnimationBox(),
		OnBnClickedCheck1(),			// функции, выполняемые при нажатии на кнопки,
		OnEnUpdateTextN(),
		OnEnUpdateTextF(),
		OnEnUpdateTextFm(),
		OnEnUpdateTextM(),
		OnEnUpdateGraphOx(),
		OnEnUpdateGraphOy(),										//при вводе текста, 
		OnLbnSelchangeParGraphType(),								//при выборе элемента в ListBox,
		OnIdrAboutMenu(),
		OnIdrAnimation(),
		OnIdrEnd(),
		OnIdrErase(),
		OnIdrDpfSave(),
		OnIdrDpfSaveas(),
		OnIdrGrSave(),
		OnIdrGrSaveas(),
		OnMenuTask(),												//при выборе пункта меню окна,
		OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar),
		OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//при взаимодействии со Slider
};
