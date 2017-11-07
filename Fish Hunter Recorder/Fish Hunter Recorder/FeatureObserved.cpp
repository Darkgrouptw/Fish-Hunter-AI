#include "FeatureObserved.h"

FeatureObserved::FeatureObserved()
{
	ReferenceNumber = new Mat[10];

	// 跑十個數字，把所有的參考圖片加進來
	for (int i = 0; i < 10; i++)
	{
		QString filePath = "../../Map/" + QString::number(i) + ".png";
		//QString filePath = "../Map/" + QString::number(i) + ".png";
		ReferenceNumber[i] = imread(filePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

		// 判斷沒有讀到的狀況
		if (!ReferenceNumber[i].data)
		{
			cout << "讀不到參考圖片!!" << endl;
			system("PAUSE");
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
QString FeatureObserved::GetPlayerState(int n)
{
	Mat gray = ToBinarization(ThreadToGray);

	Mat capturePartOfImage;
	QString OutputInfo = "";
	QString ResultIsPlayable = "";
	QString ResultScore = "";
	QString ResultDiamond = "";
	QString ResultGunLevel = "";
	bool IsPlayable = true;
	#pragma region 拿分數
	int PosX = PlayerScorePointX[n];
	int PosY = PlayerScorePointY[n];
	while (true)
	{
		capturePartOfImage = gray(Rect(PosX, PosY, PlayerScoreWidth, PlayerScoreHeight));
		int tempNumber = CheckReferenceNumber(capturePartOfImage, false);

		//imshow("TestNumber", captureScoreImage);
		//cout << tempNumber << endl;
		//waitKey(0);

		// 判斷拿到的是不是有用的資料
		if (tempNumber == -1)
			break;
		ResultScore += QString::number(tempNumber);

		// 抓下一個間距
		PosX += PlayerScoreWidth;
	}
#pragma endregion
	#pragma region 判斷是否破產 或是 不存在
	if (ResultScore == "0" || ResultScore == "")
		IsPlayable = false;
	ResultIsPlayable = (IsPlayable ? "True" : "False");
	#pragma endregion
	#pragma region 拿鑽石數目
	PosX = PlayerScorePointX[n];
	PosY = PlayerScorePointY[n] + DiamondYOffset[n];
	while (true)
	{
		capturePartOfImage = gray(Rect(PosX, PosY, PlayerScoreWidth, PlayerScoreHeight));
		int tempNumber = CheckReferenceNumber(capturePartOfImage, false);

		//imshow("TestNumber", captureScoreImage);
		//cout << tempNumber << endl;
		//waitKey(0);

		// 判斷拿到的是不是有用的資料
		if (tempNumber == -1)
			break;
		ResultDiamond += QString::number(tempNumber);

		// 抓下一個間距
		PosX += PlayerScoreWidth;
	}
	#pragma endregion
	#pragma region 拿砲台等級
	//////////////////////////////////////////////////////////////////////////
	// 這裡比較麻煩
	// 數字的部分可能會移動 像是 100、跟 1000
	// 因為式置中對其的關係
	// 所以用 Find Contour 來解決
	// 且要先判斷他是不是 "破產"
	//////////////////////////////////////////////////////////////////////////
	if (IsPlayable)
	{
		PosX = PlayerGunPointX[n];
		PosY = PlayerGunPointY[n];

		vector<vector<Point>> contours;
		vector<Rect> boundingBox;
		capturePartOfImage = gray(Rect(PosX, PosY, PlayerGunMapWidth, PlayerGunMapHeight));

		// 找出 Contours
		findContours(capturePartOfImage.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		// 變成框框
		for (int i = 0; i < contours.size(); i++)
		{
			Rect tempRect = boundingRect(contours[i]);
			tempRect = Rect(tempRect.x - 1, tempRect.y - 1, tempRect.width + 2, tempRect.height + 2);
			boundingBox.push_back(tempRect);
		}

		// 重新排序
		for (int i = 0; i < boundingBox.size(); i++)
			for (int j = i + 1; j < boundingBox.size(); j++)
				if (boundingBox[i].x > boundingBox[j].x)
					Swap(boundingBox[i], boundingBox[j]);

		// 判斷字形
		for (int i = 0; i < boundingBox.size(); i++)
		{
			Mat GetMap = capturePartOfImage(boundingBox[i]);
			resize(GetMap, GetMap, Size(PlayerScoreWidth, PlayerScoreHeight));
			ResultGunLevel += QString::number(CheckReferenceNumber(GetMap, false));
		}
	}
	#pragma endregion
	cout << "Player " << n << endl;
	cout << "IsPlayable: " << ResultIsPlayable.toStdString() << endl;
	cout << "Gun Level: " << ResultGunLevel.toStdString() << endl;
	cout << "Score: " << ResultScore.toStdString() << endl;
	cout << "Diamond: " << ResultDiamond.toStdString() << endl;
	cout << endl;
	return ResultIsPlayable + "," +
		ResultGunLevel + "," +
		ResultScore + "," +
		ResultDiamond;
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
int FeatureObserved::CheckReferenceNumber(Mat number, bool IsPrintAccuracy)
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
		if (i == 0 && BlankCheckTotal * 100 / PlayerScoreWidth / PlayerScoreHeight > BlankThreshold)
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
	// Print 準確率
	if (IsPrintAccuracy)
		cout << "Acc => " << CurrentRate << "\t";
	if (CurrentRate < CompareThreshold)
		return -1;
	#pragma endregion
	return MaxIndex;
}
void FeatureObserved::Swap(Rect &a, Rect &b)
{
	Rect temp = a;
	a = b;
	b = temp;
}
