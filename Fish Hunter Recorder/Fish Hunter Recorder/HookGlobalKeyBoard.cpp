#include "HookGlobalKeyBoard.h"
int HookGlobalKeyBoard::Width;
int HookGlobalKeyBoard::Height;
CaptureChrome HookGlobalKeyBoard::chrome;
HHOOK HookGlobalKeyBoard::hook;

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
// S	=> 存檔
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
			chrome.TakeScreenShot(1920, 1080).save("D:/FishHunter.png");
			cout << "存出暫存檔 >> D:/FishHunter.png" << endl;
			break;
		default:
			cout << "KeyCode " << keyCode << endl;
			break;
		}
	}
	//cout << "Press" << endl;
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
