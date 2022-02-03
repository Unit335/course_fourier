// CTaskDlg.cpp: файл реализации
//

#include "pch.h"
#include "CTaskDlg.h"
#include "afxdialogex.h"

#define MY_TIMER 25600
// Диалоговое окно CTaskDlg

IMPLEMENT_DYNAMIC(CTaskDlg, CDialogEx)

CTaskDlg::CTaskDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASK_DLG, pParent)
{
	CHECK = FALSE;
}

CTaskDlg::~CTaskDlg()
{
}

void CTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TASK1, ctrl_task1);
}

BEGIN_MESSAGE_MAP(CTaskDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTaskDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Добавить дополнительную инициализацию
	if (!CHECK)//если анимация не включена, алгоритм не будет отрисовывать задание, а просто напечатает его
	{
		ctrl_task1.SetWindowText(_T("Для сигнала заданного вида вычислить дискретное преобразование\nФурье (ДПФ), нарисовать график сигнальной функции и график\nмодуля ее ДПФ, предоставить возможность изменять масштаб\nграфика по Х и по У, выбор линейного или логарифмического\nмасштаба по У для графика ДПФ, интерактивный режим изменения\nпараметров сигнала, запись в файл графиков сигнала и ДПФ\nв формате ВМР.\n\nСигнал\nx(t)=a*(1+m*sin(2*PI*Fm*t))*sin(2*PI*f*t)\nс непрерывной амплитудной модуляцией.\n\nN=100..1000;\nFd=10МГц;\nf=[0.1*Fd..0.4*Fd];\nFm=[0.01*Fd..0.09*Fd];\nm=[0..0.5];"));
		ctrl_task1.ShowWindow(SW_SHOW);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CTaskDlg::OnPaint()
{
	CTaskDlg* dlgTask = (CTaskDlg*)(AfxGetMainWnd);
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CDialogEx::OnPaint() для сообщений рисования
	if (!CHECK) return;//если анимация не включена, алгоритм не будет отрисовывать задание, а просто напечатает его
	int x = 0, y = 22;
	CRect rc;
	GetClientRect(&rc);
	CRgn rn;
	rn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	dc.SelectClipRgn(&rn);
	dc.FillSolidRect(rc, RGB(240, 240, 240));
	CPen pen1;
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen pen2;
	pen2.CreatePen(PS_SOLID, 2, RGB(22, 120, 255));
	CPen pen3;
	pen3.CreatePen(PS_SOLID, 2, RGB(250, 120, 250));
	vector<POINT> vec_p;
	for (double ix = 0; (ix < M_PI * 6.5); ix += 0.01)
	{
		double iy = sin(ix);
		POINT p;
		p.x = LONG(ix * 19 + x);
		p.y = LONG(iy * 19 + y);
		vec_p.push_back(p);
	}
	dc.SelectObject(pen1);
	dc.MoveTo(x, y);
	dc.LineTo(400, y);
	for (size_t t = 0; t < vec_p.size(); t++)
	{
		dc.SelectObject(pen3);
		if (((vec_p[t].x) % 8 * M_PI) == 0)
		{
			dc.MoveTo(vec_p[t].x, y);
			dc.LineTo(vec_p[t]);
		}
		dc.SelectObject(pen1);
		if (!t) dc.MoveTo(vec_p[t]);
		dc.LineTo(vec_p[t]);
	}
	vec_p.clear();
	int x2 = 0, y2 = 200+y;
	dc.SelectObject(pen1);
	dc.MoveTo(x2, y2);
	dc.LineTo(400, y2);
	for (double ix = 0; (ix < M_PI * 6.5); ix += 0.01)
	{
		double iy = cos(ix+ M_PI / 2);
		POINT p;
		p.x = LONG(ix * 19 + x2);
		p.y = LONG(iy * 19 + y2);
		vec_p.push_back(p);
	}
	for (size_t t = 0; t < vec_p.size(); t++)
	{
		dc.SelectObject(pen2);
		if (((vec_p[t].x) % 8 * M_PI) == 0)
		{
			dc.MoveTo(vec_p[t].x, y2);
			dc.LineTo(vec_p[t]);
		}
		dc.SelectObject(pen1);
		if (!t) dc.MoveTo(vec_p[t]);
		dc.LineTo(vec_p[t]);
	}
	LOGFONT font;
	font.lfHeight = 14;// Устанавливает высоту шрифта или символа
	font.lfWidth = 0;// Устанавливает среднюю ширину символов в шрифте
	font.lfEscapement = 0;// Устанавливает угол, между вектором наклона и осью X устройства
	font.lfOrientation = 0;// Устанавливает угол, между основной линией каждого символа и осью X устройства
	font.lfWeight = 200;// Устанавливает толщину шрифта в диапазоне от 0 до 1000
	font.lfItalic = 0;// Устанавливает курсивный шрифт
	font.lfUnderline = 0;// Устанавливает подчеркнутый шрифт
	font.lfStrikeOut = 0;// Устанавливает зачеркнутый шрифт
	font.lfCharSet = RUSSIAN_CHARSET;// Устанавливает набор символов
	font.lfOutPrecision = 0;// Устанавливает точность вывода
	font.lfClipPrecision = 0;// Устанавливает точность отсечения
	font.lfQuality = 0;// Устанавливает качество вывода
	font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта

	HFONT hfont;
	hfont = ::CreateFontIndirect(&font);

	dc.SelectObject(hfont);
	int k = 13;
	dc.TextOut(x + 2, (y * 2) + k * 0,  (_T("Для сигнала x ( t ) заданного вида вычислить дискретное")));
	dc.TextOut(x + 2, (y * 2) + k * 1,  (_T("преобразование Фурье (ДПФ), нарисовать график сигнальной")));
	dc.TextOut(x + 2, (y * 2) + k * 2,  (_T("функции и график модуля ее ДПФ, предоставить возможность")));
	dc.TextOut(x + 2, (y * 2) + k * 3,  (_T("изменять масштаб графика по Х и по У, выбор линейного или")));
	dc.TextOut(x + 2, (y * 2) + k * 4,  (_T("логарифмического масштаба по У для графика ДПФ, интерактивный")));;
	dc.TextOut(x + 2, (y * 2) + k * 5,  (_T("режим изменения параметров сигнала,запись в файл графиков")));
	dc.TextOut(x + 2, (y * 2) + k * 6,  (_T("сигнала и ДПФ в формате ВМР.")));
	dc.TextOut(x + 2, (y * 2) + k * 8,  (_T("Сигнал с непрерывной амплитудной модуляцией :")));
	dc.TextOut(x + 2, (y * 2) + k * 9,  (_T("x ( t ) = a * ( 1 + m * sin ( 2 * PI * Fm * t ) ) * sin ( 2 * PI * f * t )")));
	dc.TextOut(x + 2, (y * 2) + k * 10, (_T("N = 100..1000; Fd = 10 МГц; f = [0.1 * Fd..0.4 * Fd];")));
	dc.TextOut(x + 2, (y * 2) + k * 11, (_T("Fm = [0.01 * Fd..0.09 * Fd]; m = [0..0.5];")));
}

void CTaskDlg::OnTimer(UINT_PTR nIDEvent)//Описание работы таймера
{
	if (nIDEvent == MY_TIMER) {
		CWnd* pP = GetDlgItem(IDC_TASK1);
		if (pP)
			pP->Invalidate();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CTaskDlg::StopTimer()//Упрощение остановки таймера
{
	KillTimer(MY_TIMER);
}

void CTaskDlg::OnBnClickedOk()//Описание кнопки "ОК"
{
	CDialogEx::OnOK();
}
