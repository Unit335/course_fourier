#include "pch.h"
#include "MFCApplication1Dlg.h"
#include <stdlib.h>

MFC1ParGrDlg::MFC1ParGrDlg()
{
}

MFC1ParGrDlg::~MFC1ParGrDlg()
{
}

BEGIN_MESSAGE_MAP(MFC1ParGrDlg, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MFC1ParGrDlg::OnPaint()
{
	CMFCApplication1Dlg* dlgMain = (CMFCApplication1Dlg*)AfxGetMainWnd();
	if (!dlgMain) return;
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CStatic::OnPaint() для сообщений рисования
	if (dlgMain->ANIMATEBOX_CHECK)//если отрисовка включена, идёт отрисовка осей и линии графика
	{
		POINT cs_p = dlgMain->Pnt.cs_p;
		cs_p.y *= 0.5;
		CRect rc;
		GetClientRect(&rc);
		CRgn rn;
		rn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
		dc.SelectClipRgn(&rn);
		dc.FillSolidRect(rc, RGB(240, 240, 240));
			CPen pen1;
			pen1.CreatePen(PS_SOLID, 1, RGB(250, 120, 250));
			CPen pen2;
			pen2.CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
			CPen pen3;
			pen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			dc.SelectObject(pen3);
			dc.MoveTo(0, cs_p.y);
			dc.LineTo(580, cs_p.y);
			dc.MoveTo(cs_p.x, 0);
			dc.LineTo(cs_p.x, 210);
			dc.SelectObject(pen1);
			vector<POINT> vec_f=dlgMain->Pnt.GetPointsF();
			if (vec_f.size())
			{
				if (dlgMain->M_CHECK_GR)
				{
					vector <double> def_ox= dlgMain->Pnt.GetFX(dlgMain->m_int_edit_k),
									def_oy= dlgMain->Pnt.GetFY(dlgMain->m_int_edit_k);
					dc.SelectObject(pen2);

					LOGFONT font;
					font.lfHeight = 14;// Устанавливает высоту шрифта или символа
					font.lfWidth = 0;// Устанавливает среднюю ширину символов в шрифте
					font.lfEscapement = 0;// Устанавливает угол, между вектором наклона и осью X устройства
					font.lfOrientation = 0;// Устанавливает угол, между основной линией каждого символа и осью X устройства
					font.lfWeight = 100;// Устанавливает толщину шрифта в диапазоне от 0 до 1000
					font.lfItalic = 0;// Устанавливает курсивный шрифт
					font.lfUnderline = 0;// Устанавливает подчеркнутый шрифт
					font.lfStrikeOut = 0;// Устанавливает зачеркнутый шрифт
					font.lfOutPrecision = 0;// Устанавливает точность вывода
					font.lfClipPrecision = 0;// Устанавливает точность отсечения
					font.lfQuality = 0;// Устанавливает качество вывода
					font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта

					HFONT hfont;
					hfont = ::CreateFontIndirect(&font);

					dc.SelectObject(hfont);
					CString str = _T("OX : с*10^-7");
					dc.TextOut(cs_p.x+5, 0, str);
					str = _T("OY : В");
					dc.TextOut(cs_p.x + 5, 15, str);
					for (size_t t = 1; (t <= dlgMain->m_int_edit_k) && (t < vec_f.size()); t++)
					{
						dc.MoveTo(vec_f[t].x, cs_p.y + 2);
						dc.LineTo(vec_f[t].x, cs_p.y - 2);
						CString str;
						str.Format(_T("%f"), (def_ox[t]));
						if (t % 2 == 0)
							dc.TextOut(vec_f[t].x - 22, cs_p.y - 15, str);
						else
							dc.TextOut(vec_f[t].x - 22, cs_p.y + 5, str);
					}
					LONG tylw=18,tyhr=28;
					for (size_t t = 1; ((t <= dlgMain->m_int_edit_k) && (t < def_oy.size()) && (t < vec_f.size())); t++)
					{
						dc.MoveTo(cs_p.x + 2, vec_f[t].y);
						dc.LineTo(cs_p.x - 2, vec_f[t].y);
						CString str;
						str.Format(_T("%f"), (def_oy[t]));
						if (def_oy[t] < -0.)
							if (def_oy[t] > def_oy[t - 1])
							{
								dc.TextOut(vec_f[t].x - 22, vec_f[t].y + 32, str);
								tylw = 32;
							}
							else if (def_oy[t] < def_oy[t - 1])
							{
								dc.TextOut(vec_f[t].x - 22, vec_f[t].y + 18, str);
								tylw = 18;
							}
							else
							{
								dc.TextOut(vec_f[t].x - 22, vec_f[t].y + tylw, str);
							}
						else if (def_oy[t] >= -0.)
							if (def_oy[t] < def_oy[t - 1])
							{
								dc.TextOut(vec_f[t].x - 22, vec_f[t].y - 42, str);
								tyhr = 42;
							}
							else if (def_oy[t] > def_oy[t - 1])
							{
								dc.TextOut(vec_f[t].x - 22, vec_f[t].y - 28, str);
								tyhr = 28;
							}
							else
							{
								dc.TextOut(vec_f[t].x - 22, vec_f[t].y - tyhr, str);
							}
					}
				}
				dc.SelectObject(pen1);
				for (size_t t = 0; (t < vec_f.size()); t++)
				{
					if (!t) dc.MoveTo(vec_f[t]);
					else dc.LineTo(vec_f[t]);
				}
				dlgMain->dr_p_1++;
			}
	}
	else if (dlgMain->ANIMATE_ERASE)//иначе если нажата кнопка стереть, то идет заливка поля
	{
		CRect rc;
		GetClientRect(&rc);
		CRgn rn;
		rn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
		dc.SelectClipRgn(&rn);
		dc.FillSolidRect(rc, RGB(240, 240, 240));
	}
}
