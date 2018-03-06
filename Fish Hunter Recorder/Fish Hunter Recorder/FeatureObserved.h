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
	QString		GetPlayerState(int);								// ���X�� n ���a�����A {0 => ���a�B1 => �k�U�B2 => �k�W�B3 => ���W}

	Mat			ToBinarization(int);								// �N�Ϥ��̷� Thresold ���G�Ȥ�

	void		DoHistogramBackground();							// ���ե����� Background �� Histogram
	Mat			ComputeBackground();								// �P�_�O�_�W�L
private:
	Mat			img;												// �n��{���Ϥ�
	Mat			*ReferenceNumber;									// �ѦҹϤ�

	Mat			QPixmap2CVMat(QPixmap);								// �N�@�ӹϤ��ন CV_8UC3 
	int			CheckReferenceNumber(Mat, bool);					// ��ϥ�i�h�j�M�A�ݤ��������@�� & �O�_�n Print �X Debug �T��
	void		Swap(Rect &, Rect&);								// �]�� FindContour �����ǥi��O�Ϫ��A�ҥH�n���s�Ƨ�
	bool		IsInfoPart(int, int);								// �ǤJ rows & cols �P�_�O�B�O�b�̭�

	//////////////////////////////////////////////////////////////////////////
	// �C���������@�ǰѼƦ�m
	// ***** �`�N!! *****
	// ������Ʀr Map 
	// ���O�H ThreadToGay �� 76 ����
	// �ҥH�b���� 107 ����
	// �|���@�ǨǷL���t�O
	// ���L�j�P�W�٬O ok ��
	//////////////////////////////////////////////////////////////////////////
	int	ThreadToGray = 107;											// �n�G�Ȥƪ��Ѽ�

	// ���� & �p�۬���
	int	PlayerScorePointX[4] = { 116, 1008, 1008, 118 };			// ���Ʈy�Ъ���m X
	int	PlayerScorePointY[4] = { 652, 652, 14, 15 };				// ���Ʈy�Ъ���m Y 
	int	PlayerScoreWidth = 12;										// ���ƪ���
	int	PlayerScoreHeight = 16;										// ���ƪ��e
	int DiamondYOffset[4] = { 35, 35, 36, 35 };						// �p�۪�Y �b�� YOffset

	// ���x
	int PlayerGunPointX[4] = { 288, 843, 843, 288 };				// ���x����m X 
	int PlayerGunPointY[4] = { 691, 691, 6, 6 };					// ���x���y�� Y
	int PlayerGunMapWidth = 70;
	int PlayerGunMapHeight = 25;

	int BlankThreshold = 90;										// ���ժ������A����W�L 90%
	int	CompareThreshold = 50;										// �n�W�L 50% �~�|�ǽT (���Ƥj�� 90% �H�W�A �p�ۤj�� 88% ���k�A���x�j�� 60% ���k)

	//////////////////////////////////////////////////////////////////////////
	// �o�q�O�n���Ӯ����I��
	//////////////////////////////////////////////////////////////////////////
	Mat InfoMask;
	int ****HistogramMap;											// Y(rows), X(cols), RGB, �����h�֭�

};

