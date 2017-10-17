#include "FishHunterRecorder.h"

FishHunterRecorder::FishHunterRecorder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	#pragma region 監錄的設定
	system("cls");
	chrome.GetChrome();
	HookGlobalKeyBoard::chrome = chrome;
	HookGlobalKeyBoard::Width = ui.GameView->width();
	HookGlobalKeyBoard::Height = ui.GameView->height();
	#pragma endregion
	#pragma region 將視窗移動過去
	move(1920, -300);
	#pragma endregion
	#pragma region Timer 設定
	// 每隔 1 秒執行一次
	screenshotTimer = new QTimer();
	connect(screenshotTimer, SIGNAL(timeout()), this, SLOT(ScreenShotAtChrome()));		// 連接事件
	screenshotTimer->start(100);
	#pragma endregion
}

void FishHunterRecorder::ScreenShotAtChrome()
{
	int w = ui.GameView->width();
	int h = ui.GameView->height();
	ui.GameView->setPixmap(chrome.TakeScreenShot(w, h));
}
