#include "CaptureChrome.h"


//////////////////////////////////////////////////////////////////////////
// 抓視窗相關
//////////////////////////////////////////////////////////////////////////
void CaptureChrome::GetChrome()
{
	while (true)
	{
		// 可以透過 Spy++ 取得名稱
		hwnd = FindWindowEx(0, hwnd, L"Chrome_WidgetWin_1", 0);
		if (!hwnd)
		{
			cout << "沒抓到 Chrome 視窗!!" << endl;
			QThread::sleep(1);
		}

		// 顯示在最大化
		if (IsWindowVisible(hwnd))
		{
			cout << "抓到 Chrome 視窗!!" << endl;
			ShowChrome();
			return;
		}
	}
}
void CaptureChrome::ShowChrome()
{
	WINDOWPLACEMENT place;
	memset(&place, 0, sizeof(WINDOWPLACEMENT));
	place.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(hwnd, &place);

	switch (place.showCmd)
	{
	case SW_SHOWMAXIMIZED:
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	case SW_SHOWMINIMIZED:
		ShowWindow(hwnd, SW_RESTORE);
		break;
	default:

		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	}
	SetForegroundWindow(hwnd);
	cout << "將視窗最大化!!" << endl;
}

//////////////////////////////////////////////////////////////////////////
// 擷取視窗相關
//////////////////////////////////////////////////////////////////////////
bool CaptureChrome::IsReadyToCapture()
{
	if (!hwnd)
		return false;
	return true;
}
QPixmap CaptureChrome::TakeScreenShot()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	QPixmap screenshot = screen->grabWindow(0);
	return screenshot;
}

//////////////////////////////////////////////////////////////////////////
// Static 圖片操作相關
//////////////////////////////////////////////////////////////////////////
QPixmap CaptureChrome::TakeImportantPart(QPixmap screen)
{
	// 遊戲部分
	// 從 ( 212, 114) ，大小 W = 1200, H = 861
	return screen.copy(212, 114, 1200, 720);
}
QPixmap CaptureChrome::scaleTo(QPixmap img, int w, int h)
{
	return img.scaled(w, h, Qt::KeepAspectRatio);
}