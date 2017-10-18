#include "HookGlobalKeyBoard.h"

#pragma region Static �ܼư�
int HookGlobalKeyBoard::Width;
int HookGlobalKeyBoard::Height;
HHOOK HookGlobalKeyBoard::hook;
CaptureChrome HookGlobalKeyBoard::chrome;
FeatureObserved HookGlobalKeyBoard::featureOP;
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
// Z	=> ���եΪ����s
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
			// �I��
			chrome.TakeScreenShot().save("D:/FishHunter.png");
			cout << "�s�X�I�� >> D:/FishHunter.png" << endl;
			break;
		default:
			cout << "KeyCode " << keyCode << endl;
			break;
		}
	}
	//cout << "Press" << endl;
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
