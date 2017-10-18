#pragma once
#include <iostream>
#include <QString>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QPixmap>

using namespace cv;
using namespace std;

class FeatureObserved
{
public:
	FeatureObserved();												// 在初始化的時候，要拿所有的照片
	~FeatureObserved();												// 把垃圾都清光光

	void		SetScreenShotImage(QPixmap);						// 從 ScreenShot 拿出圖片來辨認
	QString		GetPlayerScore(int);								// 拿出第 n 玩家的分數 {0 => 玩家、1 => 右下、2 => 右上、3 => 左上}

private:
	Mat			img;												// 要辨認的圖片
	Mat			*ReferenceNumber;									// 參考圖片

	Mat			QPixmap2CVMat(QPixmap);								// 將一個圖片轉成 CV_8UC3 
	Mat			ToBinarization(int);								// 將圖片依照 Thresold 做二值化
	int			CheckReferenceNumber(Mat);							// 把圖丟進去搜尋，看比較接近哪一個

	//////////////////////////////////////////////////////////////////////////
	// 遊戲內部的一些參數位置
	//////////////////////////////////////////////////////////////////////////
	const int	ThreadToGray = 76;									// 要二值化的參數
	const int	PlayerScorePointX[1] = { 116 };						// 分數座標的位置 X
	const int	PlayerScorePointY[1] = { 652 };						// 分數座標的位置 Y
	const int	PlayerScoreWidth = 12;								// 分數的長
	const int	PlayerScoreHeight = 16;								// 分數的寬

	const int	CompareThreshold = 90;								// 要超過 90% 才會準確

};

