#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "CGetCalibPicture.h"



CGetCalibPicture::CGetCalibPicture()
{
	isOver = false;
	isWriteImg = false;

}

CGetCalibPicture::~CGetCalibPicture()
{
	

}
bool CGetCalibPicture::SavePicture()			//保存图片
{
	bool bRet = false;
	do{
		cout << "SavePicture !" << endl;

		PylonInitialize();
		CBaslerGigEInstantCamera camera(CTlFactory::GetInstance().CreateDevice("Basler acA1600-60gc#0030531A818E#192.168.1.9:3956"));
		CBaslerGigEInstantCamera camera1(CTlFactory::GetInstance().CreateDevice("Basler acA1600-60gc#0030531A2E3F#192.168.1.3:3956"));

		cout << "Dispositivo usado:" << camera.GetDeviceInfo().GetModelName() << endl;
		cout << "Dispositivo usado:" << camera1.GetDeviceInfo().GetModelName() << endl;
		camera.Open();
		camera.Width.SetValue(CAMERA_WIDTH);
		camera.Height.SetValue(CAMERA_HEIGHT);
		camera.CenterX.SetValue(true);
		camera.CenterY.SetValue(true);
		camera.PixelFormat.SetValue(PixelFormat_BayerRG8);

		camera1.Open();
		camera1.Width.SetValue(CAMERA_WIDTH);
		camera1.Height.SetValue(CAMERA_HEIGHT);
		camera1.CenterX.SetValue(true);
		camera1.CenterY.SetValue(true);
		camera1.PixelFormat.SetValue(PixelFormat_BayerRG8);

		camera.MaxNumBuffer = 1;
		camera1.MaxNumBuffer = 1;

		camera.StartGrabbing(10000);
		camera1.StartGrabbing(10000);

		CGrabResultPtr ptrGrabResult;
		CGrabResultPtr ptrGrabResult1;

		int step = 1;
		int iImageCount = 0;
		String *strImageNameL = new String[NImage]();
		String *strImageNameR = new String[NImage]();
		strFirstImageNameL = strImageNameL;					//获得第一个文件路径及文件名
		strFirstImageNameR = strImageNameR;
		namedWindow("Captura", WINDOW_AUTOSIZE);
		namedWindow("Captura1", WINDOW_AUTOSIZE);
		while ((camera.IsGrabbing() && (camera1.IsGrabbing()) ) &&( iImageCount != NImage))
		{
			cout << step << endl;
			step++;
			camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
			camera1.RetrieveResult(5000, ptrGrabResult1, TimeoutHandling_ThrowException);
			CImageFormatConverter fc;
			fc.OutputPixelFormat = PixelType_BGR8packed;
			CPylonImage image;
			CPylonImage image1;

			if (ptrGrabResult->GrabSucceeded() && ptrGrabResult1->GrabSucceeded()){
				CPylonImage target;
				CPylonImage target1;
				CImageFormatConverter converter;
				converter.OutputPixelFormat = PixelType_BGR8packed;
				converter.OutputBitAlignment = OutputBitAlignment_MsbAligned;
				converter.Convert(target, ptrGrabResult);
				converter.Convert(target1, ptrGrabResult1);


				Mat image(target.GetHeight(), target.GetWidth(), CV_8UC3);
				memcpy(image.ptr(), target.GetBuffer(), 3 * target.GetWidth()*target.GetHeight());

				Mat image1(target1.GetHeight(), target1.GetWidth(), CV_8UC3);
				memcpy(image1.ptr(), target1.GetBuffer(), 3 * target1.GetWidth()*target1.GetHeight());

				imshow("Captura", image);
				imshow("Captura1", image1);

				setMouseCallback("Captura", onMouse, this);
				if (true == isWriteImg)
				{
					stringstream ii;
					++iImageCount;
					ii << iImageCount;
					*strImageNameL = ".\\CalibImageL\\" + ii.str() + ".jpg";
					*strImageNameR = ".\\CalibImageR\\" + ii.str() + ".jpg";
					IplImage *SaveImageL;
					IplImage *SaveImageR;
					SaveImageL = &IplImage(image);
					SaveImageR = &IplImage(image1);

					cvSaveImage(strImageNameL->data(), SaveImageL);
					cout << ii.str() + ".jpg" + "左摄像头获取成功" << endl;
					cvSaveImage(strImageNameR->data(), SaveImageR);
					cout << ii.str() + ".jpg" + "右摄像头获取成功" << endl;
					
					++strImageNameL;
					++strImageNameR;
					isWriteImg = false;
				}
				
				if (true == isOver)
				{
					break;
				}
				waitKey(20);

			}
		}
		camera.StopGrabbing();
		camera.Close();
		camera1.Close();
		camera1.StopGrabbing();

		cvDestroyWindow("Captura");
		cvDestroyWindow("Captura1");

		bRet = true;
	} while (false);
	return bRet;
	
/*
	bool bRet = false;
	do
	{
		String *strImageNameL = new String[NImage]();
		String *strImageNameR = new String[NImage]();
		strFirstImageNameL = strImageNameL;					//获得第一个文件路径及文件名
		strFirstImageNameR = strImageNameR;

		int iImageCount = 0;
		Mat ImageL;
		Mat ImageR;
		VideoCapture capL(0);
		VideoCapture capR(1);
		while (1)
		{
			capL >> ImageL;
			capR >> ImageR;
			imshow("Captura", ImageL);
			imshow("Captura1", ImageR);

			setMouseCallback("Captura", onMouse, this);
			if (true == isWriteImg)
			{
				stringstream ii;
				++iImageCount;
				ii << iImageCount;
				*strImageNameL = ".\\CalibImageL\\" + ii.str() + ".jpg";
				*strImageNameR = ".\\CalibImageR\\" + ii.str() + ".jpg";
				IplImage *SaveImageL;
				IplImage *SaveImageR;
				SaveImageL = &IplImage(ImageL);
				SaveImageR = &IplImage(ImageR);

				cvSaveImage(strImageNameL->data(), SaveImageL);
				cout << ii.str() + ".jpg" + "左摄像头获取成功" << endl;
				cvSaveImage(strImageNameR->data(), SaveImageR);
				cout << ii.str() + ".jpg" + "右摄像头获取成功" << endl;

				++strImageNameL;
				++strImageNameR;
				isWriteImg = false;
			}

			if (true == isOver)
			{
				break;
			}
			waitKey(100);
		}

		cvDestroyWindow("Captura");
		cvDestroyWindow("Captura1");
		bRet = true;
	} while (false);
	return bRet;*/

}


String *CGetCalibPicture::GetFirstImageNameL()
{
	return strFirstImageNameL;
}


String *CGetCalibPicture::GetFirstImageNameR()
{
	return strFirstImageNameR;
}
void CGetCalibPicture::onMouse(int event, int x, int y, int flag, void *param)
{
	CGetCalibPicture *getCalibPicture = (CGetCalibPicture *)param;
	if (event == EVENT_LBUTTONDOWN)
		getCalibPicture->isWriteImg = true;
	else if (event == EVENT_LBUTTONDBLCLK)
		getCalibPicture->isOver = true;
}