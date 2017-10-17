#include "FishHunterRecorder.h"

FishHunterRecorder::FishHunterRecorder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	#pragma region �ʿ����]�w
	system("cls");
	chrome.GetChrome();
	HookGlobalKeyBoard::chrome = chrome;
	HookGlobalKeyBoard::Width = ui.GameView->width();
	HookGlobalKeyBoard::Height = ui.GameView->height();
	#pragma endregion
	#pragma region �N�������ʹL�h
	move(1920, -300);
	#pragma endregion
	#pragma region Timer �]�w
	// �C�j 1 �����@��
	screenshotTimer = new QTimer();
	connect(screenshotTimer, SIGNAL(timeout()), this, SLOT(ScreenShotAtChrome()));		// �s���ƥ�
	screenshotTimer->start(100);
	#pragma endregion
}

void FishHunterRecorder::ScreenShotAtChrome()
{
	int w = ui.GameView->width();
	int h = ui.GameView->height();
	ui.GameView->setPixmap(chrome.TakeScreenShot(w, h));
}
