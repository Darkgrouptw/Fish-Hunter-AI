#include "HookGlobalKeyBoard.h"

#pragma region Static 變數區
int HookGlobalKeyBoard::Width;
int HookGlobalKeyBoard::Height;
HHOOK HookGlobalKeyBoard::hook;
CaptureChrome HookGlobalKeyBoard::chrome;
FeatureObserved HookGlobalKeyBoard::featureOP;
QTimer *HookGlobalKeyBoard::screenshotTimer;
#pragma endregion

HookGlobalKeyBoard::HookGlobalKeyBoard()
{
	// 只需要接收 KeyDown 的事件
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalEvent,NULL, NULL);
}
HookGlobalKeyBoard::~HookGlobalKeyBoard()
{
	UnhookWindowsHookEx(hook);
}

//////////////////////////////////////////////////////////////////////////
// 按鍵對應表
// Esc	=> 結束
// S	=> 截圖
// Q	=> 暫停 / 繼續
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK HookGlobalKeyBoard::GlobalEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
	//cout << (char)nCode << endl;
	// 判斷 Key Down 的時候，要做什麼事
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
			// 截圖
			QPixmap screen = chrome.TakeScreenShot();
			screen.save("D:/FishHunter_Full.png");

			QPixmap gamePlay = chrome.TakeImportantPart(screen);
			gamePlay.save("D:/FishHunter_Imp.png");

			featureOP.SetScreenShotImage(gamePlay);
			imwrite("D:/FishHunter_Imp_Gray.png", featureOP.ToBinarization(107));
			cout << "存出截圖" << endl;
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
