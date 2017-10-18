#include "FeatureObserved.h"

FeatureObserved::FeatureObserved()
{
	ReferenceNumber = new Mat[10];

	// �]�Q�ӼƦr�A��Ҧ����ѦҹϤ��[�i��
	for (int i = 0; i < 10; i++)
	{
		QString filePath = "../../Map/" + QString::number(i) + ".png";
		ReferenceNumber[i] = imread(filePath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

		// �P�_�S��Ū�쪺���p
		if (!ReferenceNumber[i].data)
		{
			cout << "Ū����ѦҹϤ�!!" << endl;
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
		
		// �P�_���쪺�O���O���Ϊ����
		if (tempNumber == -1)
			break;
		ResultNumber += QString::number(tempNumber);

		//imshow("TestNumber", captureScoreImage);
		//cout << tempNumber << endl;
		//waitKey(0);

		// ��U�@�Ӷ��Z
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
		if (i == 0 && BlankCheckTotal * 100 / PlayerScoreWidth / PlayerScoreHeight > CompareThreshold)
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
	if (CurrentRate < CompareThreshold)
		return -1;
	#pragma endregion
	return MaxIndex;
}
