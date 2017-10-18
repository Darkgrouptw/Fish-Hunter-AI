#pragma once
#include <iostream>
#include <Windows.h>

#include <QGuiApplication>
#include <QThread>
#include <QPixmap>
#include <QScreen>

using namespace std;

class CaptureChrome
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 抓視窗相關
	//////////////////////////////////////////////////////////////////////////
	void				GetChrome();										// 拿 Chrome 視窗的 HWND
	void				ShowChrome();										// 顯示最大化

	//////////////////////////////////////////////////////////////////////////
	// 擷取視窗
	//////////////////////////////////////////////////////////////////////////
	bool				IsReadyToCapture();									// 判斷 hwnd 是不是拿到東西，如果拿到東西代表可以開始擷取了
	QPixmap				TakeScreenShot();									// 節錄整個畫面，並依照大小去壓縮
	
	static QPixmap		TakeImportantPart(QPixmap);							// 只拿遊戲畫面
	static QPixmap		scaleTo(QPixmap, int, int);							// 做視窗縮放

private:
	HWND				hwnd;												// 抓到的 HWND
};

