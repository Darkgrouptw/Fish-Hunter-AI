#include "FishHunterRecorder.h"

FishHunterRecorder::FishHunterRecorder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	chrome.GetChrome();
	move(1920, -300);

	// �C�j 1 �����@��
	screenshotTimer = new QTimer();
	connect(screenshotTimer, SIGNAL(timeout()), this, SLOT(ScreenShotAtChrome()));		// �s���ƥ�
	screenshotTimer->start(100);
}

void FishHunterRecorder::ScreenShotAtChrome()
{
	int w = ui.GameView->width();
	int h = ui.GameView->height();
	ui.GameView->setPixmap(chrome.TakeScreenShot(w, h));
}
