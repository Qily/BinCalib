#include "stdafx.h"
#include "string.h"
#include "CSingleCalib.h"

CSingleCalib::CSingleCalib()
{

}
CSingleCalib::CSingleCalib(String *strImageName,int _flag, bool _isLeft)
{
	flag = 0;
	mustInitUndistort = true;
	
	if (_flag == 0)
		m_strImageName = strImageName;
	else
	{
		if (_isLeft)
		{
			strImageName = new String[NImage]();
			m_strImageName = strImageName;
			for (int i = 0; i < NImage;)
			{
				stringstream ii;
				++i;
				ii << i;
				*strImageName = ".\\CalibImageL\\" + ii.str() + ".jpg";
				++strImageName;
			}

		}
		else
		{
			strImageName = new String[NImage]();
			m_strImageName = strImageName;
			for (int i = 0; i < NImage;)
			{
				stringstream ii;
				++i;
				ii << i;
				*strImageName = ".\\CalibImageR\\" + ii.str() + ".jpg";
				++strImageName;
			}

		}
	}
}

CSingleCalib::~CSingleCalib()
{
	delete m_strImageName;
}

bool CSingleCalib::ExSingleCalib()
{
	string *strImageName1 = m_strImageName;
	string *strImageName2 = m_strImageName;
	string *strImageName3 = m_strImageName;
	bool bRet = false;
	do{
		cout << "ExSingleCalib !" << endl;
		/****************************************************************
		 *                          test
		 ****************************************************************/
		//			vector<Point2f> imageCorners;
		//			Size boardSize(ChessBoardSize_w, ChessBoardSize_h);
		//			Mat img = imread(*m_strImageName);
		//			if (!img.data)
		//			{
		//				cout << "no img" << endl;
		//				break;
		//			}
		//			bool found = findChessboardCorners(img, boardSize, imageCorners);
		//			drawChessboardCorners(img, boardSize, imageCorners, found);
		//			namedWindow("test");
		//			imshow("test", img);

		//			waitKey();
		/*		vector<Point3f> imgPoint;
				for (int rowIndex = 0; rowIndex < ChessBoardSize_h; ++rowIndex)
				{
				for (int colIndex = 0; colIndex < ChessBoardSize_w; ++colIndex)
				{
				imgPoint.push_back(Point3f(rowIndex * SquareWidth, colIndex * SquareWidth, 0));
				}
				}
				for (int imgIndex = 0; imgIndex < NImage; ++imgIndex)
				{
				objRealPoints.push_back(imgPoint);
				}
				*/
		//从棋盘格添加角点
		if (!addChessBoardPoints(strImageName2))
		{
			cout << "add chessBoard Points failed! " << endl;
		}
		//标定相机
//		setCalibrationFlag(true, true);
//		calibrate(Size(CAMERA_WIDTH, CAMERA_HEIGHT));
		calibrateCamera(objectPoints, imagePoints, Size(CAMERA_WIDTH, CAMERA_HEIGHT), 
			cameraMatrix, distCoeffs, rvecs, tvecs, flag);
		//////////////////////////////////////////////////////////
		////// 这里可以矫正图片
		/////////////////////////////////////////////////////////
		

//		Mat image = cv::imread(*(strImageName3 + 8));
//		cv::Mat uImage = remap(image);

//		imshow("Orginal Image", image);
//		imshow("Undistored Image", uImage);
		bRet = true;
	} while (false);
	return bRet;
}
//导入标定图片，提取角点
bool CSingleCalib::addChessBoardPoints(String *strImageName)
{
	cout << "CSingleCalib::addChessBoardPoints !" << endl;
	bool bRet = false;
	do
	{
		vector<Point2f> imageCorners;
		vector<Point3f> objectCorners;
		

		for (int i = 0; i < ChessBoardSize_h; ++i)
		{
			for (int j = 0; j < ChessBoardSize_w; ++j)
			{
				objectCorners.push_back(Point3f(i*SquareWidth, j*SquareWidth, 0));
			}
		}
		cv::Mat image;
		
		for (int i = 1; i <= NImage; ++i)
		{
			image = imread(*strImageName);
			
			cvtColor(image, grayImage, CV_BGR2GRAY);
			
			bool found = findChessboardCorners(image, ChessBoardSize, imageCorners);
			cornerSubPix(grayImage, imageCorners, Size(5, 5), cv::Size(-1, -1),
						cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 0.1));
			cout << i << endl;
			if (imageCorners.size() != ChessBoardSize.area())
			{
				cout << "检测的角点数和棋盘格本身的数目不等" << endl;
				break; 
			}
			
			addPoints(imageCorners, objectCorners);
			
			cv::drawChessboardCorners(image, ChessBoardSize, imageCorners, found);
			cv::imshow("BoardCorner", image);
			cv::waitKey(10);
			++strImageName;
		}
//		cvDestroyWindow("image");
		cvDestroyWindow("BoardCorner");
		bRet = true;
	} while (false);
	return bRet;
}
//添加场景点与对应点的图像点
bool CSingleCalib::addPoints(const vector<Point2f>& imageCorners, const vector<Point3f>& objectCorners)
{
	bool bRet = false;
	do{
		imagePoints.push_back(imageCorners);
		objectPoints.push_back(objectCorners);
		bRet = true;
	} while (false);
	return bRet;
	
}


cv::Mat CSingleCalib::remap(cv::Mat &image)
{
	cv::Mat undistorted;
	if (mustInitUndistort)
	{
		cv::initUndistortRectifyMap(
			cameraMatrix,
			distCoeffs,
			cv::Mat(),
			cv::Mat(),
			cv::Size(CAMERA_WIDTH, CAMERA_HEIGHT),
			CV_32FC1,
			map1, map2);
		mustInitUndistort = false;
	}
	cv::remap(image, undistorted, map1, map2, cv::INTER_LINEAR );
	return undistorted;
}

bool CSingleCalib::setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled)
{
	bool bRet = false;
	do{
		flag = 0;
		if (!tangentialParamEnabled) flag += CV_CALIB_ZERO_TANGENT_DIST;
		if (radial8CoeffEnabled) flag += CV_CALIB_RATIONAL_MODEL;
		bRet = true;
	} while (false);
	return bRet;
}