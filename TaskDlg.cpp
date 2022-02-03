// TaskDlg.cpp: файл реализации
//

#include "pch.h"
#include "TaskDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// Диалоговое окно TaskDlg

IMPLEMENT_DYNAMIC(TaskDlg, CDialogEx)

TaskDlg::TaskDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASK_DLG, pParent)
{

}

TaskDlg::~TaskDlg()
{
}

void TaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TaskDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений TaskDlg
