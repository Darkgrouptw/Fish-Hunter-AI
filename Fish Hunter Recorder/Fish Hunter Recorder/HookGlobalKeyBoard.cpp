#include "HookGlobalKeyBoard.h"
int HookGlobalKeyBoard::Width;
int HookGlobalKeyBoard::Height;
CaptureChrome HookGlobalKeyBoard::chrome;
HHOOK HookGlobalKeyBoard::hook;

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
// S	=> �s��
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
			chrome.TakeScreenShot(1920, 1080).save("D:/FishHunter.png");
			cout << "�s�X�Ȧs�� >> D:/FishHunter.png" << endl;
			break;
		default:
			cout << "KeyCode " << keyCode << endl;
			break;
		}
	}
	//cout << "Press" << endl;
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
