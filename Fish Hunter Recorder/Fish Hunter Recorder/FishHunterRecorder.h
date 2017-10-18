#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FishHunterRecorder.h"

#include "CaptureChrome.h"
#include "FeatureObserved.h"
#include "HookGlobalKeyBoard.h"

#include <QTimer>

using namespace std;

struct HWNDInfo
{
	HWND		WId;		// ID
	QString		name;		// 對應的名稱
};

class FishHunterRecorder : public QMainWindow
{
	Q_OBJECT

public:
	FishHunterRecorder(QWidget *parent = Q_NULLPTR);

private:
	Ui::FishHunterRecorderClass ui;

	QTimer					*screenshotTimer;
	CaptureChrome			chrome;
	FeatureObserved			featureOP;
	HookGlobalKeyBoard		keyboard;

private slots:
	void					ScreenShotAtChrome();
};
