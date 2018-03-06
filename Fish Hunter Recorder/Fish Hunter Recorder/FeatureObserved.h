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
	QString		GetPlayerState(int);								// 拿出第 n 玩家的狀態 {0 => 玩家、1 => 右下、2 => 右上、3 => 左上}

	Mat			ToBinarization(int);								// 將圖片依照 Thresold 做二值化

	void		DoHistogramBackground();							// 嘗試先做對 Background 做 Histogram
	Mat			ComputeBackground();								// 判斷是否超過
private:
	Mat			img;												// 要辨認的圖片
	Mat			*ReferenceNumber;									// 參考圖片

	Mat			QPixmap2CVMat(QPixmap);								// 將一個圖片轉成 CV_8UC3 
	int			CheckReferenceNumber(Mat, bool);					// 把圖丟進去搜尋，看比較接近哪一個 & 是否要 Print 出 Debug 訊息
	void		Swap(Rect &, Rect&);								// 因為 FindContour 的順序可能是反的，所以要重新排序
	bool		IsInfoPart(int, int);								// 傳入 rows & cols 判斷是步是在裡面

	//////////////////////////////////////////////////////////////////////////
	// 遊戲內部的一些參數位置
	// ***** 注意!! *****
	// 原先的數字 Map 
	// 都是以 ThreadToGay 為 76 做的
	// 所以在換成 107 之後
	// 會有一些些微的差別
	// 不過大致上還是 ok 的
	//////////////////////////////////////////////////////////////////////////
	int	ThreadToGray = 107;											// 要二值化的參數

	// 分數 & 鑽石相關
	int	PlayerScorePointX[4] = { 116, 1008, 1008, 118 };			// 分數座標的位置 X
	int	PlayerScorePointY[4] = { 652, 652, 14, 15 };				// 分數座標的位置 Y 
	int	PlayerScoreWidth = 12;										// 分數的長
	int	PlayerScoreHeight = 16;										// 分數的寬
	int DiamondYOffset[4] = { 35, 35, 36, 35 };						// 鑽石的Y 軸的 YOffset

	// 砲台
	int PlayerGunPointX[4] = { 288, 843, 843, 288 };				// 砲台的位置 X 
	int PlayerGunPointY[4] = { 691, 691, 6, 6 };					// 砲台的座標 Y
	int PlayerGunMapWidth = 70;
	int PlayerGunMapHeight = 25;

	int BlankThreshold = 90;										// 全白的部分，不能超過 90%
	int	CompareThreshold = 50;										// 要超過 50% 才會準確 (分數大概 90% 以上， 鑽石大概 88% 左右，砲台大概 60% 左右)

	//////////////////////////////////////////////////////////////////////////
	// 這段是要接來拿取背景
	//////////////////////////////////////////////////////////////////////////
	Mat InfoMask;
	int ****HistogramMap;											// Y(rows), X(cols), RGB, 佔有多少值

};

