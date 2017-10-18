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
	FeatureObserved();												// �b��l�ƪ��ɭԡA�n���Ҧ����Ӥ�
	~FeatureObserved();												// ��U�����M����

	void		SetScreenShotImage(QPixmap);						// �q ScreenShot ���X�Ϥ��ӿ�{
	QString		GetPlayerScore(int);								// ���X�� n ���a������ {0 => ���a�B1 => �k�U�B2 => �k�W�B3 => ���W}

private:
	Mat			img;												// �n��{���Ϥ�
	Mat			*ReferenceNumber;									// �ѦҹϤ�

	Mat			QPixmap2CVMat(QPixmap);								// �N�@�ӹϤ��ন CV_8UC3 
	Mat			ToBinarization(int);								// �N�Ϥ��̷� Thresold ���G�Ȥ�
	int			CheckReferenceNumber(Mat);							// ��ϥ�i�h�j�M�A�ݤ��������@��

	//////////////////////////////////////////////////////////////////////////
	// �C���������@�ǰѼƦ�m
	//////////////////////////////////////////////////////////////////////////
	const int	ThreadToGray = 76;									// �n�G�Ȥƪ��Ѽ�
	const int	PlayerScorePointX[1] = { 116 };						// ���Ʈy�Ъ���m X
	const int	PlayerScorePointY[1] = { 652 };						// ���Ʈy�Ъ���m Y
	const int	PlayerScoreWidth = 12;								// ���ƪ���
	const int	PlayerScoreHeight = 16;								// ���ƪ��e

	const int	CompareThreshold = 90;								// �n�W�L 90% �~�|�ǽT

};

