//Подключаем заголовок диалогового окна и необходимые файлы языка C++
#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MY_TIMER 25600 // Определение счётчика таймера MY_TIMER

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg(); // Определение окна "О программе"

// Данные диалогового окна "О программе"
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, ANIMATEBOX_CHECK(FALSE)
	, ANIMATE_ERASE(FALSE)
	, cs_edit_f(_T("1000000.000000"))
	, cs_edit_Fm(_T("100000.000000"))
	, cs_edit_m(_T("0.000000"))
	, cs_edit_N(_T("100"))
	, cs_edit_ox(_T("1.000000"))
	, cs_edit_oy(_T("1.000000")) // Определение начальных значений переменных
	, M_CHECK_GR(FALSE)
	, m_int_edit_k(10)
	, m_text_static_check(_T("При OX ≥ 3.125000"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON4); //Загрузка иконки приложения
	dr_p_1 = 0;
	dr_p_2 = 0;//Определение начального количества точек на графиках
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, ID_ANIMATION_BOX, ANIMATEBOX_CHECK);
	DDX_Control(pDX, IDC_PAR_F, f_txt);
	DDX_Control(pDX, IDC_PAR_FM, Fm_txt);
	DDX_Control(pDX, IDC_PAR_M, m_txt);
	DDX_Control(pDX, IDC_PAR_N, N_txt);
	DDX_Control(pDX, IDC_SLIDER_F, slider_f);
	DDX_Control(pDX, IDC_SLIDER_FM, slider_Fm);
	DDX_Control(pDX, IDC_SLIDER_M, slider_m);
	DDX_Control(pDX, IDC_SLIDER_N, slider_N);
	DDX_Control(pDX, IDC_TEXT_F, ctrl_edit_f);
	DDX_Control(pDX, IDC_TEXT_FM, ctrl_edit_Fm);
	DDX_Control(pDX, IDC_TEXT_M, ctrl_edit_m);
	DDX_Control(pDX, IDC_TEXT_N, ctrl_edit_N);
	DDX_Control(pDX, IDC_PAR_GRAPH_TYPE, ctrl_list_view);
	DDX_Control(pDX, ID_ANIMATION_BOX, ctrl_animatebox);
	DDX_Control(pDX, IDC_GRAPH_OY1, ctrl_edit_oy);
	DDX_Control(pDX, IDC_GRAPH_OX1, ctrl_edit_ox);
	DDX_Control(pDX, IDC_SLIDER_OX1, slider_ox);
	DDX_Control(pDX, IDC_SLIDER_OY1, slider_oy);
	DDX_Control(pDX, IDC_BUTTON_RESET, ctrl_reset_1);
	DDX_Control(pDX, IDC_BUTTON_DRAW, ctrl_erase);
	DDX_Control(pDX, IDC_BUTTON_RESET2, ctrl_reset_2);
	DDX_Text(pDX, IDC_TEXT_F, cs_edit_f);
	DDX_Text(pDX, IDC_TEXT_FM, cs_edit_Fm);
	DDX_Text(pDX, IDC_TEXT_M, cs_edit_m);
	DDX_Text(pDX, IDC_TEXT_N, cs_edit_N);
	DDX_Text(pDX, IDC_GRAPH_OX1, cs_edit_ox);
	DDX_Text(pDX, IDC_GRAPH_OY1, cs_edit_oy); //Определение переменных обмена данных для CheckBox, Static и управления элементами диалогового окна
	DDX_Check(pDX, IDC_CHECK1, M_CHECK_GR);
	DDX_Control(pDX, IDC_CHECK1, m_ctrl_check_gr);
	DDX_Control(pDX, IDC_CHECK, m_ctrl_static_check);
	DDX_Text(pDX, IDC_CHECK, m_text_static_check);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_LBN_SELCHANGE(IDC_PAR_GRAPH_TYPE, &CMFCApplication1Dlg::OnLbnSelchangeParGraphType)
	ON_COMMAND(IDR_ABOUT_MENU, &CMFCApplication1Dlg::OnIdrAboutMenu)
	ON_COMMAND(IDR_END, &CMFCApplication1Dlg::OnIdrEnd)
	ON_COMMAND(IDR_START, &CMFCApplication1Dlg::OnIdrErase)
	ON_COMMAND(ID_MENU_TASK, &CMFCApplication1Dlg::OnMenuTask)
	ON_COMMAND(IDR_DPF_SAVE, &CMFCApplication1Dlg::OnIdrDpfSave)
	ON_COMMAND(IDR_DPF_SAVEAS, &CMFCApplication1Dlg::OnIdrDpfSaveas)
	ON_COMMAND(IDR_GR_SAVE, &CMFCApplication1Dlg::OnIdrGrSave)
	ON_COMMAND(IDR_GR_SAVEAS, &CMFCApplication1Dlg::OnIdrGrSaveas)
	ON_COMMAND(IDR_ANIMATION, &CMFCApplication1Dlg::OnIdrAnimation)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMFCApplication1Dlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCApplication1Dlg::OnBnClickedButtonErase)
	ON_BN_CLICKED(ID_ANIMATION_BOX, &CMFCApplication1Dlg::OnBnClickedAnimationBox)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &CMFCApplication1Dlg::OnBnClickedButtonReset2)
	ON_EN_UPDATE(IDC_TEXT_N, &CMFCApplication1Dlg::OnEnUpdateTextN)
	ON_EN_UPDATE(IDC_TEXT_F, &CMFCApplication1Dlg::OnEnUpdateTextF)
	ON_EN_UPDATE(IDC_TEXT_FM, &CMFCApplication1Dlg::OnEnUpdateTextFm)
	ON_EN_UPDATE(IDC_TEXT_M, &CMFCApplication1Dlg::OnEnUpdateTextM)
	ON_EN_UPDATE(IDC_GRAPH_OX1, &CMFCApplication1Dlg::OnEnUpdateGraphOx)
	ON_EN_UPDATE(IDC_GRAPH_OY1, &CMFCApplication1Dlg::OnEnUpdateGraphOy)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, TRUE);		// Мелкий значок
	
	// TODO: добавьте дополнительную инициализацию
	gr_Par.SubclassDlgItem(IDC_GRAPH_PAR1, this); // Установка подклассового элемента поля для графика сигнала
	gr_Spec.SubclassDlgItem(IDC_GRAPH_PAR2, this); // Установка подклассового элемента поля для графика ДПФ
	slider_N.SetRange(2, 20);
	slider_f.SetRange(4, 16);
	slider_Fm.SetRange(1, 9);
	slider_m.SetRange(0, 5);
	slider_ox.SetRange(1,100);
	slider_oy.SetRange(1,250); // Установка диапазонов допустимых значений Slider
	slider_N.SetTicFreq(2);
	slider_f.SetTicFreq(2);
	slider_Fm.SetTicFreq(1);
	slider_m.SetTicFreq(1);
	slider_ox.SetTicFreq(10);
	slider_oy.SetTicFreq(25); // Установка частоты меток шкалы Slider
	ctrl_list_view.AddString(_T("Логарифмический масштаб"));
	ctrl_list_view.AddString(_T("Линейный масштаб")); // Добавление строки в ListBox
	ctrl_list_view.SetCurSel(0); // Выбор строки по умолчанию
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal(); // При нажатии на пункт "О программе" в контекстном меню открывается диалоговое окно "О программе"
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMFCApplication1Dlg::OnPaint() 
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
		dc.DrawIcon(x, y, m_hIcon); // Отрисовка клиентской рабочей области
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CMFCApplication1Dlg::OnIdrAboutMenu()
{
	StopTimer();
	CWaitCursor a;
	CAboutDlg dlgAbout;
	dlgAbout.DoModal(); // При нажатии на пункт меню "О программе" открывается диалоговое окно "О программе"
	StartTimer();
}

void CMFCApplication1Dlg::OnIdrEnd()
{
	StopTimer();
	CWaitCursor a;
	int Res = AfxMessageBox(L"Внимание !\nВы действительно хотите завершить работу программы ?", MB_YESNO, MB_ICONQUESTION);// При нажатии на пункт меню "Завершить работу" открывается окно подтверждения закрытия
	if (Res == IDYES) CDialog::OnCancel(); // если клиент подтвердил - программа закрывается
	StartTimer();
}

void CMFCApplication1Dlg::OnIdrErase()
{
	OnBnClickedButtonErase(); // Повторение функций кнопки "Стереть"
}

void CMFCApplication1Dlg::OnMenuTask()
{
	StopTimer();
	CWaitCursor a;
	CTaskDlg dlgTask;
	dlgTask.CHECK = ANIMATEBOX_CHECK;// Выбор режима - с отрисовкой или без отрисовки
	dlgTask.DoModal();// Открытие окна "Задание"
	SetTimer(MY_TIMER, UINT(41.667), NULL);
}

void CMFCApplication1Dlg::OnIdrDpfSave()
{
	CFileDialog dlgSave(FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		_T(".BMP"),
		NULL,
		OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("BMP (*.bmp)|*.bmp|Все файлы (*.*)|*.*||"),
		NULL,
		0,
		TRUE); // Выбор настроек окна сохранения
	if (IDOK == dlgSave.DoModal()) // Вызов модального диалогового окна "Сохранение"
	{
		wstring savePath = dlgSave.m_pOFN->lpstrFile;
		CWnd* GraphWnd = GetDlgItem(IDC_GRAPH_PAR2);
		SaveGraph(savePath.c_str(), GraphWnd, 0); // Вызов функции сохранения Поля графика ДПФ в файл BMP
	}
}

void CMFCApplication1Dlg::OnIdrDpfSaveas()
{
	CFileDialog dlgSave(FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		NULL,
		NULL,
		OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Все файлы (*.*)|*.*|PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|BMP (*.bmp)|*.bmp|TIFF (*.tiff)|*.tiff||"),
		NULL,
		0,
		TRUE);
	if (IDOK == dlgSave.DoModal()) // Вызов модального диалогового окна "Сохранение как"
	{
		wstring savePath = dlgSave.m_pOFN->lpstrFile;
		CWnd* GraphWnd = GetDlgItem(IDC_GRAPH_PAR2);
		SaveGraph(savePath.c_str(), GraphWnd, 1); // Вызов функции сохранения Поля графика ДПФ в файл с выбором расширений
	}
}

void CMFCApplication1Dlg::OnIdrGrSave()
{
	CFileDialog dlgSave(FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		_T(".BMP"),
		NULL,
		OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("BMP (*.bmp)|*.bmp|Все файлы (*.*)|*.*||"),
		NULL,
		0,
		TRUE);
	if (IDOK == dlgSave.DoModal()) // Вызов модального диалогового окна "Сохранение"
	{
		wstring savePath = dlgSave.m_pOFN->lpstrFile;
		CWnd* GraphWnd = GetDlgItem(IDC_GRAPH_PAR1);
		SaveGraph(savePath.c_str(), GraphWnd, 0); // Вызов функции сохранения Поля графика сигнала в файл BMP
	}
}

void CMFCApplication1Dlg::OnIdrGrSaveas()
{
	CFileDialog dlgSave(FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		NULL,
		NULL,
		OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Все файлы (*.*)|*.*|PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|BMP (*.bmp)|*.bmp|TIFF (*.tiff)|*.tiff||"),
		NULL,
		0,
		TRUE);
	if (IDOK == dlgSave.DoModal()) // Вызов модального диалогового окна "Сохранение как"
	{
		wstring savePath = dlgSave.m_pOFN->lpstrFile;
		CWnd* GraphWnd = GetDlgItem(IDC_GRAPH_PAR1);
		SaveGraph(savePath.c_str(), GraphWnd, 1); // Вызов функции сохранения Поля графика сигнала в файл с выбором расширений
	}
}

void CMFCApplication1Dlg::OnLbnSelchangeParGraphType()
{
	ctrl_reset_2.EnableWindow();
	funcs.log = ctrl_list_view.GetCurSel();

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}
	//ReDrawing();// при изменении масштаба оси OY графика ДПФ активировать кнопку "Сбросить" и перерисовать график
}

void CMFCApplication1Dlg::OnOK()
{ } // Убираем функциональность кнопки "ОК"

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == MY_TIMER)
	{
		UpdateData();
		if ((funcs.t >= Pnt.par.n)&&(funcs.t>=0))
			StopTimer();
		if (funcs.t==floor(funcs.t))
		Pnt.Transfer(funcs);
		gr_Par.Invalidate();
		gr_Spec.Invalidate();
		if (funcs.t == -2) StopTimer();
		funcs.t += 1;
	}//Описание таймера
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::StartTimer()
{
	SetTimer(MY_TIMER, UINT((1000. / 24.)), NULL);
}

void CMFCApplication1Dlg::StopTimer()
{
	KillTimer(MY_TIMER);
}//Упрощение процедуры остановки таймера

void CMFCApplication1Dlg::OnBnClickedButtonReset()
{
	UpdateData(TRUE);
	CWaitCursor a;
	ANIMATEBOX_CHECK = FALSE;
	ctrl_edit_f.SetWindowText(_T("1000000.000000"));
	ctrl_edit_Fm.SetWindowText(_T("100000.000000"));
	ctrl_edit_m.SetWindowText(_T("0.000000"));
	ctrl_edit_N.SetWindowText(_T("100"));
	slider_N.SetPos(2);
	slider_f.SetPos(1);
	slider_Fm.SetPos(1);
	slider_m.SetPos(0);
	N_txt.SetWindowText(_T("N = 100"));
	f_txt.SetWindowText(_T("f = 1000000.000000"));
	Fm_txt.SetWindowText(_T("Fm = 100000.000000"));
	m_txt.SetWindowText(_T("m = 0.000000"));
	Text_N.Format(_T("100"));
	Text_f.Format(_T("1000000.000000"));
	Text_Fm.Format(_T("100000.00000"));
	Text_m.Format(_T("0.000000"));
	cs_edit_f = _T("1000000.000000");
	cs_edit_Fm = _T("100000.000000");
	cs_edit_m = _T("0.000000");
	cs_edit_N = _T("100");
	StopTimer();
	SetDlgItemText(ID_ANIMATION_BOX, L"&Включить рисование");
	ctrl_animatebox.SetCheck(0);
	ctrl_reset_1.EnableWindow(0);
	OnBnClickedButtonErase();
	UpdateData(FALSE);
	m_ctrl_static_check.SetWindowText(_T("При OX ≥ 3.125000"));
}//Действия по нажатию кнопки "Сбросить" в группе параметров функции

void CMFCApplication1Dlg::OnBnClickedButtonErase()
{
	funcs.t = -1;
	if (ANIMATEBOX_CHECK)
		StartTimer();
	dr_p_1 = -1; // Заливка фона 
	dr_p_2 = -1; // Заливка фона
  CWnd* gr = GetDlgItem(IDC_GRAPH_PAR1); // Объект класса CWnd
	if (gr)
	{
		gr->Invalidate(); //Перерисовка графика
	}
		gr = GetDlgItem(IDC_GRAPH_PAR2); // Объект класса CWnd
	if (gr)
	{
		gr->Invalidate(); //Перерисовка графика
	}
	if (ANIMATEBOX_CHECK) Drawing();
	else {
		ANIMATE_ERASE = 1;
		CMenu* pMenu = GetMenu();
		pMenu->EnableMenuItem(IDR_START, MF_GRAYED);
		ctrl_erase.EnableWindow(0);
	}
}//Очистка линии графиков при нажатии кнопки "Стереть"

bool CMFCApplication1Dlg::Drawing()
{
	CWaitCursor a;
	if (ANIMATEBOX_CHECK)
	{
		if (Pnt.Transfer(funcs))
			return 1;
		else AfxMessageBox(_T("!"));
	}
	else return 0;
}//Запуск процесса отрисовки, передача значений параметров в подпрограмму расчёта и настройка таймера

void CMFCApplication1Dlg::OnIdrAnimation()
{
	UpdateData(TRUE);
	ANIMATE_ERASE = 0;
	funcs.t = -1;
	ANIMATEBOX_CHECK = !ANIMATEBOX_CHECK;
	if (!(funcs.N>=100.) && !(funcs.f>=100000.) && !(funcs.Fm>=1000000.) && !(funcs.m >= 0.))
	{
		ctrl_animatebox.SetCheck(0); ANIMATEBOX_CHECK = 0;
		AfxMessageBox(_T("Ошибка .\nПараметры не заполнены ."), MB_ICONHAND);
	}
	else if (!(funcs.scaleX) && !(funcs.scaleY))
	{
		ctrl_animatebox.SetCheck(0); ANIMATEBOX_CHECK = 0;
		AfxMessageBox(_T("Ошибка .\nМасштабирование не настроено ."), MB_ICONHAND);
	}
	else if (ANIMATEBOX_CHECK)
	{
		if (Drawing())
		{
			SetDlgItemText(ID_ANIMATION_BOX, L"&Выключить рисование");
			ctrl_animatebox.SetCheck(1);
			ctrl_erase.EnableWindow();
			CMenu* pMenu = GetMenu();
			pMenu->CheckMenuItem(IDR_ANIMATION, MF_CHECKED | MF_BYCOMMAND);
			pMenu->EnableMenuItem(IDR_START, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_DPF_SAVE, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_DPF_SAVEAS, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_GR_SAVE, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_GR_SAVEAS, MF_ENABLED);
			StartTimer();
		}
	}
	else {
		StopTimer();
		SetDlgItemText(ID_ANIMATION_BOX, L"&Включить рисование");
		ctrl_animatebox.SetCheck(0);
		CMenu* pMenu = GetMenu();
		pMenu->CheckMenuItem(IDR_ANIMATION, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->EnableMenuItem(IDR_DPF_SAVE, MF_GRAYED);
		pMenu->EnableMenuItem(IDR_DPF_SAVEAS, MF_GRAYED);
		pMenu->EnableMenuItem(IDR_GR_SAVE, MF_GRAYED);
		pMenu->EnableMenuItem(IDR_GR_SAVEAS, MF_GRAYED);
		if ((dr_p_1) || (dr_p_2))
		{
		}
		else
		{
			pMenu->EnableMenuItem(IDR_START, MF_GRAYED);
			ctrl_erase.EnableWindow(0);
		}
	}
}//Действия при нажатии на пункт меню "Анимация", повторяющие нажатие на кнопку

void CMFCApplication1Dlg::OnBnClickedAnimationBox()
{
	UpdateData(TRUE);
	ANIMATE_ERASE = 0;
	funcs.t = -1;
	if (!(funcs.N >= 100.) && !(funcs.f >= 100000.) && !(funcs.Fm >= 1000000.) && !(funcs.m >= 0.))
	{
		ctrl_animatebox.SetCheck(0); ANIMATEBOX_CHECK = 0;
		AfxMessageBox(_T("Ошибка .\nПараметры не заполнены ."), MB_ICONHAND);
	}
	else if (!(funcs.scaleX) && !(funcs.scaleY))
	{
		ctrl_animatebox.SetCheck(0); ANIMATEBOX_CHECK = 0;
		AfxMessageBox(_T("Ошибка .\nМасштабирование не настроено ."), MB_ICONHAND);
	}
	else if (ANIMATEBOX_CHECK)
	{
		if (Drawing())
		{
			SetDlgItemText(ID_ANIMATION_BOX, L"&Выключить рисование");
			ctrl_animatebox.SetCheck(1);
			ctrl_erase.EnableWindow();
			CMenu* pMenu = GetMenu();
			pMenu->CheckMenuItem(IDR_ANIMATION, MF_CHECKED | MF_BYCOMMAND);
			pMenu->EnableMenuItem(IDR_START, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_DPF_SAVE, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_DPF_SAVEAS, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_GR_SAVE, MF_ENABLED);
			pMenu->EnableMenuItem(IDR_GR_SAVEAS, MF_ENABLED);
			StartTimer();
		}
	}
	else {
		StopTimer();
		SetDlgItemText(ID_ANIMATION_BOX, L"&Включить рисование");
		ctrl_animatebox.SetCheck(0);
		CMenu* pMenu = GetMenu();
		pMenu->CheckMenuItem(IDR_ANIMATION, MF_UNCHECKED | MF_BYCOMMAND);
		pMenu->EnableMenuItem(IDR_DPF_SAVE, MF_GRAYED);
		pMenu->EnableMenuItem(IDR_DPF_SAVEAS, MF_GRAYED);
		pMenu->EnableMenuItem(IDR_GR_SAVE, MF_GRAYED);
		pMenu->EnableMenuItem(IDR_GR_SAVEAS, MF_GRAYED);
		if ((dr_p_1) || (dr_p_2))
		{
		}
		else
		{
			pMenu->EnableMenuItem(IDR_START, MF_GRAYED);
			ctrl_erase.EnableWindow(0);
		}
	}
}//Действия запуска/остановки отрисовки

void CMFCApplication1Dlg::OnBnClickedButtonReset2()
{
	UpdateData(TRUE);
	CWaitCursor a;
	ANIMATEBOX_CHECK = FALSE;
	ctrl_list_view.SetCurSel(0);
	funcs.log = false;
	slider_ox.SetPos(1);
	slider_oy.SetPos(1);
	ctrl_edit_ox.SetWindowText(_T("1.000000"));
	ctrl_edit_oy.SetWindowText(_T("1.000000"));
	cs_edit_ox = _T("1.000000");
	cs_edit_oy = _T("1.000000");
	StopTimer();
	SetDlgItemText(ID_ANIMATION_BOX, L"&Включить рисование");
	ctrl_animatebox.SetCheck(0);
	OnBnClickedButtonErase();
	ctrl_reset_2.EnableWindow(0);
	UpdateData(FALSE);
}//При нажатии на кнопку "Сбросить" в группе масштаба и масштабирования все значения примут изначальные данные

void CMFCApplication1Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int n = 50 * slider_N.GetPos();
	Text_N.Format(_T("%d"), n);
	ctrl_edit_N.SetWindowText(Text_N);
	N_txt.SetWindowText(_T("N = ") + Text_N);

	double F = 0.025 * Fd * slider_f.GetPos();
	Text_f.Format(_T("%f"), F);
	f_txt.SetWindowText(_T("f = ") + Text_f);
	ctrl_edit_f.SetWindowText(Text_f);

	double Fm = 0.01 * Fd * slider_Fm.GetPos();
	Text_Fm.Format(_T("%f"), Fm);
	ctrl_edit_Fm.SetWindowText(Text_Fm);
	Fm_txt.SetWindowText(_T("Fm = ") + Text_Fm);

	double m_f = 0.1 * slider_m.GetPos();
	Text_m.Format(_T("%f"), m_f);
	ctrl_edit_m.SetWindowText(Text_m);
	m_txt.SetWindowText(_T("m = ") + Text_m);

	funcs.N = _wtof(Text_N.GetString());
	funcs.f = _wtof(Text_f.GetString());
	funcs.Fm = _wtof(Text_Fm.GetString());
	funcs.m = _wtof(Text_m.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_1.EnableWindow();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}//Обработка взаимодействия с горизонтальными Slider


void CMFCApplication1Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	double ox = slider_ox.GetPos();
	cs_edit_ox.Format(_T("%f"), ox);
	ctrl_edit_ox.SetWindowText(cs_edit_ox);

	double oy = slider_oy.GetPos();
	cs_edit_oy.Format(_T("%f"), oy);
	ctrl_edit_oy.SetWindowText(cs_edit_oy);

	funcs.scaleX = _wtof(cs_edit_ox.GetString());
	funcs.scaleY = _wtof(cs_edit_oy.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_2.EnableWindow();

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}//Обработка взаимодействия с вертикальными Slider

void CMFCApplication1Dlg::OnEnUpdateTextN()
{
	ctrl_edit_N.GetWindowText(Text_N);
	int n = _wtoi(Text_N.GetString());
	if ((n <= 1000) && (n >= 100))
	{
	}
	else if (n >= 1000)
	{
		ctrl_edit_N.SetWindowText(_T("1000"));
		n = 1000;
	}
	else
	{
		ctrl_edit_N.SetWindowText(_T("100"));
		n = 100;
	}
	Text_N.Format(_T("%d"), n);
	N_txt.SetWindowText(_T("N = ") + Text_N);
	slider_N.SetPos(n / 50);

	m_text_static_check.Format(_T("%f"), (funcs.N / 32.));
	m_ctrl_static_check.SetWindowTextW(_T("При OX ≥ ") + m_text_static_check);

	UpdateData();
	if ((funcs.N / funcs.scaleX <= 32.) && (funcs.N))
	{
		m_ctrl_check_gr.EnableWindow();
	}
	else
	{
		m_ctrl_check_gr.EnableWindow(0);
		m_ctrl_check_gr.SetCheck(0);
	}

	funcs.N = _wtof(Text_N.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_1.EnableWindow();
}//Обработка взаимодействия с EditBox N и проверка на попадание в диапазон значений

void CMFCApplication1Dlg::OnEnUpdateTextF()
{
	ctrl_edit_f.GetWindowText(Text_f);
	double F = _wtof(Text_f.GetString());
	if ((F <= 4000000.) && (F >= 1000000.))
	{
	}
	else if (F > 4000000.)
	{
		ctrl_edit_f.SetWindowText(_T("4000000.000000"));
		F = 4000000.;
	}
	else
	{
		ctrl_edit_f.SetWindowText(_T("1000000.000000"));
		F = 1000000.;
	}
	slider_f.SetPos(F*4./1000000.);
	Text_f.Format(_T("%f"), F);
	f_txt.SetWindowText(_T("f = ") + Text_f);

	funcs.f = _wtof(Text_f.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_1.EnableWindow();
}//Обработка взаимодействия с EditBox f и проверка на попадание в диапазон значений

void CMFCApplication1Dlg::OnEnUpdateTextFm()
{
	ctrl_edit_Fm.GetWindowText(Text_Fm);
	double Fm = _wtof(Text_Fm.GetString());
	if ((Fm >= 100000.) && (Fm <= 900000.))
	{
	}
	else if (Fm > 900000.)
	{
		ctrl_edit_Fm.SetWindowTextW(_T("900000.000000"));
		Fm = 900000.;
	}
	else
	{
		ctrl_edit_Fm.SetWindowTextW(_T("100000.000000"));
		Fm = 100000.;
	}
	slider_Fm.SetPos(Fm/100000.);
	Text_Fm.Format(_T("%f"), Fm);
	Fm_txt.SetWindowText(_T("Fm = ") + Text_Fm);

	funcs.Fm = _wtof(Text_Fm.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_1.EnableWindow();
}//Обработка взаимодействия с EditBox Fm и проверка на попадание в диапазон значений

void CMFCApplication1Dlg::OnEnUpdateTextM()
{
	ctrl_edit_m.GetWindowText(Text_m);
	double M = _wtof(Text_m.GetString());
	if ((M >= 0.) && (M <= 0.5))
	{
	}
	else if (M > 0.5)
	{
		ctrl_edit_m.SetWindowText(_T("0.000000"));
		M = 0.5;
	}
	else
	{
		ctrl_edit_m.SetWindowText(_T("0.500000"));
		M = 0.;
	}
	slider_m.SetPos(M*10.);
	Text_m.Format(_T("%f"), M);
	m_txt.SetWindowText(_T("m = ") + Text_m);

	funcs.m = _wtof(Text_m.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_1.EnableWindow();
}//Обработка взаимодействия с EditBox m и проверка на попадание в диапазон значений

void CMFCApplication1Dlg::OnEnUpdateGraphOx()
{
	ctrl_edit_ox.GetWindowText(cs_edit_ox);
	double ox = _wtof(cs_edit_ox.GetString());
	if ((ox >= 1.) && (ox <= 100.))
	{
	}
	else if (ox > 100.)
	{
		ctrl_edit_ox.SetWindowText(_T("100.000000"));
		ox = 100.;
	}
	else
	{
		ctrl_edit_ox.SetWindowText(_T("1.000000"));
		ox = 1.;
	}
	slider_ox.SetPos(ox);
	UpdateData();
	if ((funcs.N / funcs.scaleX <= 32.)&&(funcs.N))
	{
		m_ctrl_check_gr.EnableWindow();
	}
	else
	{
		m_ctrl_check_gr.EnableWindow(0);
		m_ctrl_check_gr.SetCheck(0);
	}

	funcs.scaleX = _wtof(cs_edit_ox.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_2.EnableWindow();
}//Обработка взаимодействия с EditBox OX и проверка на попадание в диапазон значений

void CMFCApplication1Dlg::OnEnUpdateGraphOy()
{
	ctrl_edit_oy.GetWindowText(cs_edit_oy);
	double oy = _wtof(cs_edit_oy.GetString());
	if ((oy >= 1.) && (oy <= 250.))
	{
	}
	else if (oy > 250.)
	{
		ctrl_edit_oy.SetWindowText(_T("250.000000"));
		oy = 250.;
	}
	else
	{
		ctrl_edit_oy.SetWindowText(_T("1.000000"));
		oy = 1.;
	}
	slider_oy.SetPos(oy);

	funcs.scaleY = _wtof(cs_edit_oy.GetString());

	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}

	ctrl_reset_2.EnableWindow();
}//Обработка взаимодействия с EditBox OY и проверка на попадание в диапазон значений

void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	UpdateData();
	if (ANIMATEBOX_CHECK)
	{
		funcs.t = -2;
		StartTimer();
	}
}//Обработка взаимодействия с кнопкой проверки 10 отсчётов