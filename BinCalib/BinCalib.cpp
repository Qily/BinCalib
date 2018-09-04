// BinCalib.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "CGetCalibPicture.h"
#include "CSingleCalib.h"
#include "CDoubCalib.h"
using namespace std;

void PrintInfo(CSingleCalib *singleCalib);
int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 1;
	if (flag == 1){
		CGetCalibPicture *pGetCalibPicture = new CGetCalibPicture;
		pGetCalibPicture->SavePicture();				//�Ȳ�����������ǵÿ���
		CSingleCalib *pSingleCalib = new CSingleCalib(pGetCalibPicture->GetFirstImageNameL(), 0, true);
	}
	CSingleCalib *pSingleCalibL = new CSingleCalib(nullptr, 1, true);	//�������
	pSingleCalibL->ExSingleCalib();															//�������Ŀ�궨
	PrintInfo(pSingleCalibL);
	CSingleCalib *pSingleCalibR = new CSingleCalib(nullptr, 1, false);  //�����ұ�
	pSingleCalibR->ExSingleCalib();																//�������Ŀ�궨
	PrintInfo(pSingleCalibR);
	DoubCalib *pDoubleCalib = new DoubCalib(pSingleCalibL->getCameraMatrix(), pSingleCalibL->getDistCoeffs(),
		pSingleCalibR->getCameraMatrix(), pSingleCalibR->getDistCoeffs(), pSingleCalibL->getObjectPoint(),
		pSingleCalibL->getImagePoints(),pSingleCalibR->getImagePoints());			//��ʼ������
	pDoubleCalib->ExDoubCalib();																//˫Ŀ�궨
	
	

//	delete pGetCalibPicture;								//Ϊ�˱������ʱע���鷳�����⣬���ͷ�ָ��
																				//�ں���Ҫע��ָ����ͷ�
	system("pause");
	return 0;
}

void PrintInfo(CSingleCalib *singleCalib)
{
	cv::Mat cameraMatrix;
	cv::Mat distCoeff;
	cameraMatrix = singleCalib->getCameraMatrix();
	distCoeff = singleCalib->getDistCoeffs();
	std::cout << "Camera instrinsic:" << cameraMatrix.rows << "x" << cameraMatrix.cols << std::endl;
	std::cout << cameraMatrix.at<double>(0, 0) << "\t " << cameraMatrix.at<double>(0, 1) << "\t " << cameraMatrix.at<double>(0, 2) << std::endl;
	std::cout << cameraMatrix.at<double>(1, 0) << "\t " << cameraMatrix.at<double>(1, 1) << "\t " << cameraMatrix.at<double>(1, 2) << std::endl;
	std::cout << cameraMatrix.at<double>(2, 0) << "\t " << cameraMatrix.at<double>(2, 1) << "\t " << cameraMatrix.at<double>(2, 2) << std::endl;

	std::cout << "����ϵ������ ��" << distCoeff.rows << "x" << distCoeff.cols << std::endl;
	for (int i = 0; i < distCoeff.rows; ++i)
	{
		for (int j = 0; j < distCoeff.cols; ++j)
			cout << distCoeff.at<double>(i, j) << "\t";
		cout << "" << endl;
	}
		
//	waitKey();
}