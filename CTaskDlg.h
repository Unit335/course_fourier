#pragma once

#include "MFCApplication1Dlg.h"

class CTaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskDlg)

public:
	CTaskDlg(CWnd* pParent = nullptr);
	virtual ~CTaskDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public:
	BOOL CHECK;
	CStatic ctrl_task1;
	virtual BOOL OnInitDialog();
	void StopTimer();
	afx_msg void	OnPaint(),
					OnTimer(UINT_PTR nIDEvent),
					OnBnClickedOk();
};