#pragma once
#include <afxwin.h>
#include "framework.h"

class MFC1ParGrDlg : //����� ��������� ������� ������� �������
	public CStatic //��������-�����
{
public:
	MFC1ParGrDlg();//�����������
	~MFC1ParGrDlg();//����������
	afx_msg void OnPaint();//������� ��������� ����
	DECLARE_MESSAGE_MAP() //������� ���������� ��������
};