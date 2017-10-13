#include "CaptureChrome.h"


//////////////////////////////////////////////////////////////////////////
// ���������
//////////////////////////////////////////////////////////////////////////
void CaptureChrome::GetChrome()
{
	while (true)
	{
		// �i�H�z�L Spy++ ���o�W��
		hwnd = FindWindowEx(0, hwnd, L"Chrome_WidgetWin_1", 0);
		if (!hwnd)
		{
			cout << "�S��� Chrome ����!!" << endl;
			QThread::sleep(1);
		}

		// ��ܦb�̤j��
		if (IsWindowVisible(hwnd))
		{
			cout << "��� Chrome ����!!" << endl;
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
	cout << "�N�����̤j��!!" << endl;
}

//////////////////////////////////////////////////////////////////////////
// �^����������
//////////////////////////////////////////////////////////////////////////
bool CaptureChrome::IsReadyToCapture()
{
	if (!hwnd)
		return false;
	return true;
}
QPixmap CaptureChrome::TakeScreenShot(int w, int h)
{
	QScreen *screen = QGuiApplication::primaryScreen();
	QPixmap screenshot = screen->grabWindow(0);
	screenshot = screenshot.scaled(w, h, Qt::KeepAspectRatio);
	return screenshot;
}
