#include "pch.h"
#include "MFCApplication1Dlg.h"

MFC1SpecGrDlg::MFC1SpecGrDlg()
{
}

MFC1SpecGrDlg::~MFC1SpecGrDlg()
{
}
BEGIN_MESSAGE_MAP(MFC1SpecGrDlg, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MFC1SpecGrDlg::OnPaint()
{
	CMFCApplication1Dlg* dlgMain = (CMFCApplication1Dlg*)AfxGetMainWnd();
	if (!dlgMain) return;
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CStatic::OnPaint() для сообщений рисования
	if (dlgMain->ANIMATEBOX_CHECK)//если отрисовка включена, идёт отрисовка осей и линии графика
	{
		POINT cs_p = dlgMain->Pnt.cs_p;
		CRect rc;
		GetClientRect(&rc);
		CRgn rn;
		rn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(22, 120, 255));
		dc.SelectClipRgn(&rn);
		dc.FillSolidRect(rc, RGB(240, 240, 240));
		dc.MoveTo(0, cs_p.y);
		dc.LineTo(580, cs_p.y);
		dc.MoveTo(cs_p.x, 0);
		dc.LineTo(cs_p.x, 210);
		vector<POINT> vec_s = dlgMain->Pnt.GetPointsS();
		if (vec_s.size())
		{
			dc.SelectObject(pen);
			for (size_t t = 0; (t < vec_s.size()); t++)
			{
				dc.MoveTo(vec_s[t].x,cs_p.y);
				dc.LineTo(vec_s[t]);
			}
			dlgMain->dr_p_2++;
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
		dlgMain->ANIMATE_ERASE = !(dlgMain->ANIMATE_ERASE);
	}
}
