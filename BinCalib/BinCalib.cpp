// BinCalib.cpp : 定义控制台应用程序的入口点。
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
		pGetCalibPicture->SavePicture();				//先不开启，后面记得开启
		CSingleCalib *pSingleCalib = new CSingleCalib(pGetCalibPicture->GetFirstImageNameL(), 0, true);
	}
	CSingleCalib *pSingleCalibL = new CSingleCalib(nullptr, 1, true);	//处理左边
	pSingleCalibL->ExSingleCalib();															//左相机单目标定
	PrintInfo(pSingleCalibL);
	CSingleCalib *pSingleCalibR = new CSingleCalib(nullptr, 1, false);  //处理右边
	pSingleCalibR->ExSingleCalib();																//右相机单目标定
	PrintInfo(pSingleCalibR);
	DoubCalib *pDoubleCalib = new DoubCalib(pSingleCalibL->getCameraMatrix(), pSingleCalibL->getDistCoeffs(),
		pSingleCalibR->getCameraMatrix(), pSingleCalibR->getDistCoeffs(), pSingleCalibL->getObjectPoint(),
		pSingleCalibL->getImagePoints(),pSingleCalibR->getImagePoints());			//初始化变量
	pDoubleCalib->ExDoubCalib();																//双目标定
	
	

//	delete pGetCalibPicture;								//为了避免调试时注释麻烦的问题，不释放指针
																				//在后面要注意指针的释放
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

	std::cout << "畸变系数矩阵 ：" << distCoeff.rows << "x" << distCoeff.cols << std::endl;
	for (int i = 0; i < distCoeff.rows; ++i)
	{
		for (int j = 0; j < distCoeff.cols; ++j)
			cout << distCoeff.at<double>(i, j) << "\t";
		cout << "" << endl;
	}
		
//	waitKey();
}