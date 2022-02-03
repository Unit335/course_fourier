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
					   // TODO: �������� ���� ��� ����������� ���������
					   // �� �������� CStatic::OnPaint() ��� ��������� ���������
	if (dlgMain->ANIMATEBOX_CHECK)//���� ��������� ��������, ��� ��������� ���� � ����� �������
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
					font.lfHeight = 14;// ������������� ������ ������ ��� �������
					font.lfWidth = 0;// ������������� ������� ������ �������� � ������
					font.lfEscapement = 0;// ������������� ����, ����� �������� ������� � ���� X ����������
					font.lfOrientation = 0;// ������������� ����, ����� �������� ������ ������� ������� � ���� X ����������
					font.lfWeight = 100;// ������������� ������� ������ � ��������� �� 0 �� 1000
					font.lfItalic = 0;// ������������� ��������� �����
					font.lfUnderline = 0;// ������������� ������������ �����
					font.lfStrikeOut = 0;// ������������� ����������� �����
					font.lfOutPrecision = 0;// ������������� �������� ������
					font.lfClipPrecision = 0;// ������������� �������� ���������
					font.lfQuality = 0;// ������������� �������� ������
					font.lfPitchAndFamily = 0;// ������������� ������ �������� � ��������� ������

					HFONT hfont;
					hfont = ::CreateFontIndirect(&font);

					dc.SelectObject(hfont);
					CString str = _T("OX : �*10^-7");
					dc.TextOut(cs_p.x+5, 0, str);
					str = _T("OY : �");
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
	else if (dlgMain->ANIMATE_ERASE)//����� ���� ������ ������ �������, �� ���� ������� ����
	{
		CRect rc;
		GetClientRect(&rc);
		CRgn rn;
		rn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
		dc.SelectClipRgn(&rn);
		dc.FillSolidRect(rc, RGB(240, 240, 240));
	}
}
