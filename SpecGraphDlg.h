#pragma once
#include <afxwin.h>
#include "framework.h"

class MFC1SpecGrDlg : //����� ��������� ������� ������� �������
	public CStatic //��������-�����
{
public:
	MFC1SpecGrDlg();//�����������
	~MFC1SpecGrDlg();//����������
	afx_msg void OnPaint();//������� ��������� ����
	DECLARE_MESSAGE_MAP() //������� ���������� ��������
};