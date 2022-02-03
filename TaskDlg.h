#pragma once


// Диалоговое окно TaskDlg

class TaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TaskDlg)

public:
	TaskDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~TaskDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
