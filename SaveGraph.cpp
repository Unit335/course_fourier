#include "pch.h"
#include "MFCApplication1Dlg.h"

DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatTIFF, 0xb96b3cb1, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);//Глобальные универсальные ид форматов

bool SaveGraph(LPCTSTR path, CWnd* GraphWnd, int as)
{
	ASSERT(GraphWnd);
	if (GraphWnd == NULL)
		return  FALSE;//проверка на наличие изображения

	CWindowDC winDC(GraphWnd);//получаем возможность работы с изображением
	CRect rect;
	GraphWnd->GetWindowRect(&rect);//получаем прямоугольник изображения
	CImage pic;

	int  nBPP = winDC.GetDeviceCaps(BITSPIXEL) * winDC.GetDeviceCaps(PLANES);
	if (nBPP != 24) nBPP = 24;//установка фиксированной битности изображения

	BOOL bStat = pic.Create(rect.Width(), rect.Height(), nBPP);
	ASSERT(bStat);
	if (!bStat)
		return  FALSE;//проверяем, чтобы изображение не было пустым

	CImageDC picDC(pic);//обрабатываем изображение, которое уже будем сохранять
	BitBlt(picDC, 0, 0, rect.Width(), rect.Height(), winDC, 0, 0, SRCCOPY);//копируем изображение
	string strFull = CT2A(path);//копируем путь и начинаем искать в нем расширение формата
	HRESULT ext;//переменная, хранящая расширенный результат операции
	if (as)//если путь взят из окна "Сохранить как", то начинаем поиск расширения в пути
	{
		if (((-1 != strFull.find((".JPG")))) && (-1 != strFull.find((".jpg"))))
		{
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatJPEG);
			AfxMessageBox(_T("Успешно !\nГрафик сохранен в формате JPG."), MB_ICONINFORMATION);
		}
		else if (((-1 != strFull.find((".PNG")))) && (-1 != strFull.find((".png"))))
		{
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatPNG);
			AfxMessageBox(_T("Успешно !\nГрафик сохранен в формате PNG."), MB_ICONINFORMATION);
		}
		else if (((-1 != strFull.find((".GIF")))) && (-1 != strFull.find((".gif"))))
		{
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatGIF);
			AfxMessageBox(_T("Успешно !\nГрафик сохранен в формате GIF."), MB_ICONINFORMATION);
		}
		else if (((-1 != strFull.find((".TIFF")))) && (-1 != strFull.find((".tiff"))))
		{
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatTIFF);
			AfxMessageBox(_T("Успешно !\nГрафик сохранен в формате TIFF."), MB_ICONINFORMATION);
		}
		else if (((-1 != strFull.find((".BMP")))) && (-1 != strFull.find((".bmp"))))
		{
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatBMP);
			AfxMessageBox(_T("Успешно !\nГрафик сохранен в формате BMP."), MB_ICONINFORMATION);
		}
		else //если  формат не найден, то сохраняем в формате по умолчанию
		{
			strFull += ".BmP";
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatBMP);
			AfxMessageBox(_T("Произошла ошибка !\nГрафик сохранен в формате по умолчанию - BMP."),MB_ICONHAND, MB_ICONINFORMATION);
		}

	}
	else//если из окна "Сохранить", то сразу сохраняем в формате BMP
	{
			CA2T wt(strFull.c_str());
			ext = pic.Save(wt, ImageFormatBMP);
			AfxMessageBox(_T("Успешно !\nГрафик сохранен в формате BMP."), MB_ICONINFORMATION);
	}
	if (FAILED(ext))//если сохранение не получилось, то выводим сообшение
	{
		CString strErr;
		strErr.Format(L" Не удалось сохранить файл : %s, %x ", strFull, ext);
		AfxMessageBox(strErr, MB_OK | MB_ICONERROR);
	}
	// TODO: добавьте свой код обработчика команд
return false;
}
