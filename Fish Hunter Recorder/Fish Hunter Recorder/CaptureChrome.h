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
	// ���������
	//////////////////////////////////////////////////////////////////////////
	void				GetChrome();										// �� Chrome ������ HWND
	void				ShowChrome();										// ��̤ܳj��

	//////////////////////////////////////////////////////////////////////////
	// �^������
	//////////////////////////////////////////////////////////////////////////
	bool				IsReadyToCapture();									// �P�_ hwnd �O���O����F��A�p�G����F��N��i�H�}�l�^���F
	QPixmap				TakeScreenShot();									// �`����ӵe���A�è̷Ӥj�p�h���Y
	
	static QPixmap		TakeImportantPart(QPixmap);							// �u���C���e��
	static QPixmap		scaleTo(QPixmap, int, int);							// �������Y��

private:
	HWND				hwnd;												// ��쪺 HWND
};

