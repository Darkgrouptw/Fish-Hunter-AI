#include "FeatureObserved.h"

FeatureObserved::FeatureObserved()
{
	ReferenceNumber = new Mat[10];

	// 跑十個數字，把所有的參考圖片加進來
	for (int i = 0; i < 10; i++)
	{
		QString filePath = "../../Map/" + QString::number(i) + ".png";
		ReferenceNumber[i] = imread(filePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

		// 判斷沒有讀到的狀況
		if (!ReferenceNumber[i].data)
		{
			cout << "讀不到參考圖片!!" << endl;
			exit(0);
		}
	}
}
FeatureObserved::~FeatureObserved()
{
	delete[] ReferenceNumber;
}

//////////////////////////////////////////////////////////////////////////
// 一些因為要拿到 Feature ，所在 OpenCV 上要做的操作
//////////////////////////////////////////////////////////////////////////
void FeatureObserved::SetScreenShotImage(QPixmap pixmap)
{
	img = QPixmap2CVMat(pixmap);
}
QString FeatureObserved::GetPlayerScore(int n)
{
	Mat gray = ToBinarization(ThreadToGray);

	int PosX = PlayerScorePointX[n];
	int PosY = PlayerScorePointY[n];
	Mat captureScoreImage;
	QString ResultNumber = "";
	while (true)
	{
		captureScoreImage = gray(Rect(PosX, PosY, PlayerScoreWidth, PlayerScoreHeight));
		int tempNumber = CheckReferenceNumber(captureScoreImage);
		
		// 判斷拿到的是不是有用的資料
		if (tempNumber == -1)
			break;
		ResultNumber += QString::number(tempNumber);

		//imshow("TestNumber", captureScoreImage);
		//cout << tempNumber << endl;
		//waitKey(0);

		// 抓下一個間距
		PosX += PlayerScoreWidth;
	}
	cout << ResultNumber.toStdString() << endl;
	return ResultNumber;
}

Mat FeatureObserved::QPixmap2CVMat(QPixmap pixmap)
{
	QImage img = pixmap.toImage();
	Mat result(img.height(), img.width(), CV_8UC4, (uchar*)img.bits(), img.bytesPerLine());
	return result.clone();
}
Mat FeatureObserved::ToBinarization(int t)
{
	Mat gray;
	cvtColor(img, gray, CV_BGRA2GRAY);
	threshold(gray, gray, t, 255, THRESH_BINARY);
	return gray;
}
int FeatureObserved::CheckReferenceNumber(Mat number)
{
	#pragma region 初始化，並清空
	int BlankCheckTotal = 0;
	int CheckTable[10];
	memset(CheckTable, 0, 10 * sizeof(int));
	#pragma endregion
	#pragma region 跑每個迴圈
	// 跑每個迴圈，假設他是空的話，回傳 -1，其他回傳正常值
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < PlayerScoreHeight; y++)
		{
			for (int x = 0; x < PlayerScoreWidth; x++)
			{
				// Type 是 8U_C3
				uchar numberPart = number.at<uchar>(y, x);
				uchar referencePart = ReferenceNumber[i].at<uchar>(y, x);
				if (numberPart == referencePart)
					CheckTable[i]++;

				if (i == 0 && numberPart == 0)
				{
					// 判斷有幾個空白
					BlankCheckTotal++;
				}
			}
		}

		// 抓到空白就跳出來
		if (i == 0 && BlankCheckTotal * 100 / PlayerScoreWidth / PlayerScoreHeight > CompareThreshold)
			return -1;
	}
	#pragma endregion
	#pragma region 看哪一個準確率比較高
	int MaxCurrentNumber = 0;
	int MaxIndex = 0;
	for (int i = 0; i < 10; i++)
	{
		if (MaxCurrentNumber < CheckTable[i])
		{
			MaxCurrentNumber = CheckTable[i];
			MaxIndex = i;
		}
	}
	#pragma endregion
	#pragma region 小於某個準確率就回傳 -1
	int CurrentRate = MaxCurrentNumber * 100 / PlayerScoreWidth / PlayerScoreHeight;
	if (CurrentRate < CompareThreshold)
		return -1;
	#pragma endregion
	return MaxIndex;
}
