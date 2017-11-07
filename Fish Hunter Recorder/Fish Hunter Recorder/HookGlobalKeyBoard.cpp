#include "HookGlobalKeyBoard.h"

#pragma region Static �ܼư�
int HookGlobalKeyBoard::Width;
int HookGlobalKeyBoard::Height;
HHOOK HookGlobalKeyBoard::hook;
CaptureChrome HookGlobalKeyBoard::chrome;
FeatureObserved HookGlobalKeyBoard::featureOP;
QTimer *HookGlobalKeyBoard::screenshotTimer;
#pragma endregion

HookGlobalKeyBoard::HookGlobalKeyBoard()
{
	// �u�ݭn���� KeyDown ���ƥ�
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalEvent,NULL, NULL);
}
HookGlobalKeyBoard::~HookGlobalKeyBoard()
{
	UnhookWindowsHookEx(hook);
}

//////////////////////////////////////////////////////////////////////////
// ���������
// Esc	=> ����
// S	=> �I��
// Q	=> �Ȱ� / �~��
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK HookGlobalKeyBoard::GlobalEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
	//cout << (char)nCode << endl;
	// �P�_ Key Down ���ɭԡA�n�������
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
		int keyCode = ((KBDLLHOOKSTRUCT *)lParam)->vkCode;
		switch (keyCode)
		{
		case 27:
			// Esc
			exit(0);
			break;
		case 'S':
		{
			// �I��
			QPixmap screen = chrome.TakeScreenShot();
			screen.save("D:/FishHunter_Full.png");

			QPixmap gamePlay = chrome.TakeImportantPart(screen);
			gamePlay.save("D:/FishHunter_Imp.png");

			featureOP.SetScreenShotImage(gamePlay);
			imwrite("D:/FishHunter_Imp_Gray.png", featureOP.ToBinarization(107));
			cout << "�s�X�I��" << endl;
			break;
		}
		case 'Q':
			if (screenshotTimer != NULL)
			{
				if (screenshotTimer->isActive())
					screenshotTimer->stop();
				else
					screenshotTimer->start(100);
			}
			break;
		default:
			cout << "KeyCode " << keyCode << endl;
			break;
		}
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
