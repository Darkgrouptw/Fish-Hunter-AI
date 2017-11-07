#include "FeatureObserved.h"

FeatureObserved::FeatureObserved()
{
	ReferenceNumber = new Mat[10];

	// �]�Q�ӼƦr�A��Ҧ����ѦҹϤ��[�i��
	for (int i = 0; i < 10; i++)
	{
		QString filePath = "../../Map/" + QString::number(i) + ".png";
		//QString filePath = "../Map/" + QString::number(i) + ".png";
		ReferenceNumber[i] = imread(filePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

		// �P�_�S��Ū�쪺���p
		if (!ReferenceNumber[i].data)
		{
			cout << "Ū����ѦҹϤ�!!" << endl;
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
// �@�Ǧ]���n���� Feature �A�Ҧb OpenCV �W�n�����ާ@
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
	#pragma region ������
	int PosX = PlayerScorePointX[n];
	int PosY = PlayerScorePointY[n];
	while (true)
	{
		capturePartOfImage = gray(Rect(PosX, PosY, PlayerScoreWidth, PlayerScoreHeight));
		int tempNumber = CheckReferenceNumber(capturePartOfImage, false);

		//imshow("TestNumber", captureScoreImage);
		//cout << tempNumber << endl;
		//waitKey(0);

		// �P�_���쪺�O���O���Ϊ����
		if (tempNumber == -1)
			break;
		ResultScore += QString::number(tempNumber);

		// ��U�@�Ӷ��Z
		PosX += PlayerScoreWidth;
	}
#pragma endregion
	#pragma region �P�_�O�_�}�� �άO ���s�b
	if (ResultScore == "0" || ResultScore == "")
		IsPlayable = false;
	ResultIsPlayable = (IsPlayable ? "True" : "False");
	#pragma endregion
	#pragma region ���p�ۼƥ�
	PosX = PlayerScorePointX[n];
	PosY = PlayerScorePointY[n] + DiamondYOffset[n];
	while (true)
	{
		capturePartOfImage = gray(Rect(PosX, PosY, PlayerScoreWidth, PlayerScoreHeight));
		int tempNumber = CheckReferenceNumber(capturePartOfImage, false);

		//imshow("TestNumber", captureScoreImage);
		//cout << tempNumber << endl;
		//waitKey(0);

		// �P�_���쪺�O���O���Ϊ����
		if (tempNumber == -1)
			break;
		ResultDiamond += QString::number(tempNumber);

		// ��U�@�Ӷ��Z
		PosX += PlayerScoreWidth;
	}
	#pragma endregion
	#pragma region �����x����
	//////////////////////////////////////////////////////////////////////////
	// �o�̤���·�
	// �Ʀr�������i��|���� ���O 100�B�� 1000
	// �]�����m����䪺���Y
	// �ҥH�� Find Contour �ӸѨM
	// �B�n���P�_�L�O���O "�}��"
	//////////////////////////////////////////////////////////////////////////
	if (IsPlayable)
	{
		PosX = PlayerGunPointX[n];
		PosY = PlayerGunPointY[n];

		vector<vector<Point>> contours;
		vector<Rect> boundingBox;
		capturePartOfImage = gray(Rect(PosX, PosY, PlayerGunMapWidth, PlayerGunMapHeight));

		// ��X Contours
		findContours(capturePartOfImage.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		// �ܦ��خ�
		for (int i = 0; i < contours.size(); i++)
		{
			Rect tempRect = boundingRect(contours[i]);
			tempRect = Rect(tempRect.x - 1, tempRect.y - 1, tempRect.width + 2, tempRect.height + 2);
			boundingBox.push_back(tempRect);
		}

		// ���s�Ƨ�
		for (int i = 0; i < boundingBox.size(); i++)
			for (int j = i + 1; j < boundingBox.size(); j++)
				if (boundingBox[i].x > boundingBox[j].x)
					Swap(boundingBox[i], boundingBox[j]);

		// �P�_�r��
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
	#pragma region ��l�ơA�òM��
	int BlankCheckTotal = 0;
	int CheckTable[10];
	memset(CheckTable, 0, 10 * sizeof(int));
	#pragma endregion
	#pragma region �]�C�Ӱj��
	// �]�C�Ӱj��A���]�L�O�Ū��ܡA�^�� -1�A��L�^�ǥ��`��
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < PlayerScoreHeight; y++)
		{
			for (int x = 0; x < PlayerScoreWidth; x++)
			{
				// Type �O 8U_C3
				uchar numberPart = number.at<uchar>(y, x);
				uchar referencePart = ReferenceNumber[i].at<uchar>(y, x);
				if (numberPart == referencePart)
					CheckTable[i]++;

				if (i == 0 && numberPart == 0)
				{
					// �P�_���X�Ӫť�
					BlankCheckTotal++;
				}
			}
		}

		// ���ťմN���X��
		if (i == 0 && BlankCheckTotal * 100 / PlayerScoreWidth / PlayerScoreHeight > BlankThreshold)
			return -1;
	}
	#pragma endregion
	#pragma region �ݭ��@�ӷǽT�v�����
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
	#pragma region �p��Y�ӷǽT�v�N�^�� -1
	int CurrentRate = MaxCurrentNumber * 100 / PlayerScoreWidth / PlayerScoreHeight;
	// Print �ǽT�v
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
