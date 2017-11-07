#include "FishHunterRecorder.h"

FishHunterRecorder::FishHunterRecorder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	#pragma region �ʿ����]�w
	//system("cls");
	chrome.GetChrome();
	HookGlobalKeyBoard::chrome = chrome;
	HookGlobalKeyBoard::featureOP = featureOP;
	HookGlobalKeyBoard::Width = ui.GameView->width();
	HookGlobalKeyBoard::Height = ui.GameView->height();
	#pragma endregion
	#pragma region �N�������ʹL�h
	move(1920, -600);
	#pragma endregion
	#pragma region Timer �]�w
	// �C�j 1 �����@��
	screenshotTimer = new QTimer();
	connect(screenshotTimer, SIGNAL(timeout()), this, SLOT(ScreenShotAtChrome()));						// �s���ƥ�
	screenshotTimer->start(100);
	HookGlobalKeyBoard::screenshotTimer = screenshotTimer;
	#pragma endregion
}

void FishHunterRecorder::ScreenShotAtChrome()
{
	int w = ui.GameView->width();
	int h = ui.GameView->height();
	QPixmap screenShot = chrome.TakeScreenShot();														// �I��
	QPixmap GamePlayScreen = CaptureChrome::TakeImportantPart(screenShot);								// ��C������
	featureOP.SetScreenShotImage(GamePlayScreen);														// �]�w Feature �[��Ϥ�

	system("cls");
	featureOP.GetPlayerState(0);
	featureOP.GetPlayerState(1);
	featureOP.GetPlayerState(2);
	featureOP.GetPlayerState(3);

	ui.GameView->setPixmap(CaptureChrome::scaleTo(GamePlayScreen, w, h));
}
