#include "FishHunterRecorder.h"

FishHunterRecorder::FishHunterRecorder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	#pragma region 監錄的設定
	//system("cls");
	chrome.GetChrome();
	HookGlobalKeyBoard::chrome = chrome;
	HookGlobalKeyBoard::featureOP = featureOP;
	HookGlobalKeyBoard::Width = ui.GameView->width();
	HookGlobalKeyBoard::Height = ui.GameView->height();
	#pragma endregion
	#pragma region 將視窗移動過去
	move(1920, -600);
	#pragma endregion
	#pragma region Timer 設定
	// 每隔 1 秒執行一次
	screenshotTimer = new QTimer();
	connect(screenshotTimer, SIGNAL(timeout()), this, SLOT(ScreenShotAtChrome()));						// 連接事件
	screenshotTimer->start(100);
	HookGlobalKeyBoard::screenshotTimer = screenshotTimer;
	#pragma endregion
}

void FishHunterRecorder::ScreenShotAtChrome()
{
	int w = ui.GameView->width();
	int h = ui.GameView->height();
	QPixmap screenShot = chrome.TakeScreenShot();														// 截圖
	QPixmap GamePlayScreen = CaptureChrome::TakeImportantPart(screenShot);								// 抓遊戲部分
	featureOP.SetScreenShotImage(GamePlayScreen);														// 設定 Feature 觀察的圖片

	system("cls");
	featureOP.GetPlayerState(0);
	featureOP.GetPlayerState(1);
	featureOP.GetPlayerState(2);
	featureOP.GetPlayerState(3);

	ui.GameView->setPixmap(CaptureChrome::scaleTo(GamePlayScreen, w, h));
}
