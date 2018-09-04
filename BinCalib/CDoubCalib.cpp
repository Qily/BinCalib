#include "stdafx.h"
#include "CDoubCalib.h"
#include "CCompareImage.h"


DoubCalib::DoubCalib()
{

}
DoubCalib::DoubCalib(Mat CamMatrixL, Mat distCoeffL, Mat CamMatrixR, Mat distCoeffR,
	std::vector<std::vector<cv::Point3f>> _objRealPoint, std::vector<std::vector<cv::Point2f>> _imagePointL, 
	std::vector<std::vector<cv::Point2f>> _imagePointR)
{
	m_CamMatrixL = CamMatrixL;
/*	m_CamMatrixL.at<double>(0, 0) = 1848.36;	m_CamMatrixL.at<double>(0, 1) = 0;	m_CamMatrixL.at<double>(0, 2) = 799.48;
	m_CamMatrixL.at<double>(1, 0) = 0;	m_CamMatrixL.at<double>(1, 1) = 1851.59;	m_CamMatrixL.at<double>(1, 2) = 598.266;
	m_CamMatrixL.at<double>(2, 0) = 0;	m_CamMatrixL.at<double>(2, 1) = 0;	m_CamMatrixL.at<double>(2, 2) = 1;*/
	m_CamMatrixR = CamMatrixR;
	m_distCoeffL = distCoeffL;
/*	m_distCoeffL.at<double>(0, 0) = -0.0895154;
	m_distCoeffL.at<double>(0, 1) = 0.818616;
	m_distCoeffL.at<double>(0, 2) = 0.0024453;
	m_distCoeffL.at<double>(0, 3) = 0.00130842;*/
//	m_distCoeffL.at<double>(0, 4) = 0;
	m_distCoeffR = distCoeffR;
//	m_distCoeffR.at<double>(0, 4) = 0;

	m_objRealPoint = _objRealPoint;
	m_imagePointL = _imagePointL;
	m_imagePointR = _imagePointR;
}
DoubCalib::~DoubCalib()
{

}
bool DoubCalib::ExDoubCalib()
{
	rectifyImageL = imread(".\\1L.jpg");
	rectifyImageR = imread(".\\1R.jpg");
	stereoCalibrate(m_objRealPoint, m_imagePointL, m_imagePointR,
		m_CamMatrixL, m_distCoeffL, m_CamMatrixR, m_distCoeffR,
		Size(CAMERA_WIDTH, CAMERA_HEIGHT), R, T, E, F,
		TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 20, 0.01));
	stereoRectify(m_CamMatrixL, m_distCoeffL, m_CamMatrixR, m_distCoeffR, ImageSize, R, T, Rl, Rr, Pl, Pr, Q,
		CALIB_ZERO_DISPARITY, 0, Size(CAMERA_WIDTH, CAMERA_HEIGHT), &validROIL, &validROIR);

	//		initUndistortRectifyMap(m_CamMatrixL, m_distCoeffL, Rl, Pl, cv::Size(CAMERA_WIDTH, CAMERA_HEIGHT),
	//		CV_32FC1, mapLx, mapLy);
	//initUndistortRectifyMap(m_CamMatrixR, m_distCoeffR, Rr, Pr, cv::Size(CAMERA_WIDTH, CAMERA_HEIGHT), 
	//CV_32FC1, mapRx, mapRy);

	//	remap(rectifyImageL, rectifyImageL, mapLx, mapLy, INTER_LINEAR);
	//remap(rectifyImageR, rectifyImageR, mapRx, mapRy, INTER_LINEAR);
	Mat LImage = Remap(rectifyImageL, m_CamMatrixL, m_distCoeffL, mapLx, mapLy);
	Mat RImage = Remap(rectifyImageR, m_CamMatrixR, m_distCoeffR, mapRx, mapRy);
	imwrite(".\\1LImage.jpg", LImage);
	imwrite(".\\1RImage.jpg", RImage);
	PrintInfo();


//	imshow("1", LImage);
//	imshow("2", RImage);
	//imwrite("./CorrectImage/left.jpg", LImage);
	//imwrite("./CorrectImage/right.jpg", RImage);
//	waitKey(20);
	CCompareImage pCompareImage;
	pCompareImage.showDiff(LImage, RImage);

	//
	//	cvDestroyWindow("rectify beforeL");
	//	cvDestroyWindow("rectify beforeR");
	return true;
}

void DoubCalib::PrintInfo()
{
	


	FileStorage fs("intrinsics.yml", FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "cameraMatrixL" << m_CamMatrixL << "cameraDistcoeffL" << m_distCoeffL << "cameraMatrixR" <<m_CamMatrixR << "cameraDistcoeffR" << m_distCoeffR;
		fs.release();
		cout << "cameraMatrixL=:" << m_CamMatrixL << endl << "cameraDistcoeffL=:" << m_distCoeffL << endl << "cameraMatrixR=:" << m_CamMatrixR << endl << "cameraDistcoeffR=:" << m_distCoeffR << endl;
	}
	else
	{
		cout << "Error: can not save the intrinsics!!!!!" << endl;
	}

	fs.open("extrinsics.yml", FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "R" << R << "T" << T << "Rl" << Rl << "Rr" << Rr << "Pl" << Pl << "Pr" << Pr << "Q" << Q;
		cout << "R=" << R << endl << "T=" << T << endl << "Rl=" << Rl << endl << "Rr=" << Rr << endl << "Pl=" << Pl << endl << "Pr=" << Pr << endl << "Q=" << Q << endl;
		fs.release();
	}
	else
		cout << "Error: can not save the extrinsic parameters\n";
}

cv::Mat DoubCalib::Remap(cv::Mat &image,Mat cameraMatrix, Mat distCoeffs, Mat map1, Mat map2)
{
	cv::Mat undistorted;
	
		cv::initUndistortRectifyMap(
			cameraMatrix,
			distCoeffs,
			cv::Mat(),
			cv::Mat(),
			cv::Size(CAMERA_WIDTH,CAMERA_HEIGHT),
			CV_32FC1,
			map1, map2);
		
	
	cv::remap(image, undistorted, map1, map2, cv::INTER_LINEAR);
	return undistorted;
}