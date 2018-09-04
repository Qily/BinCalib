#ifndef _SINGLE_CALIB_H_
#define _SINGLE_CALIB_H_
#include <vector>
class CSingleCalib
{
public:
	CSingleCalib();
	CSingleCalib(String *strImageName, int flag, bool _isLeft);
	~CSingleCalib();
	bool ExSingleCalib();
	cv::Mat getCameraMatrix() { return cameraMatrix; }
	cv::Mat getDistCoeffs() { return distCoeffs; }
	std::vector<std::vector<cv::Point2f>> getImagePoints() { return imagePoints;  }
//	std::vector<std::vector<cv::Point3f>> getObjRealPoints() { return objRealPoints;  }
	std::vector<std::vector<cv::Point3f>> getObjectPoint(){ return objectPoints;  }
private:
	String *m_strImageName;

	std::vector<std::vector<cv::Point2f>> imagePoints;
	std::vector<std::vector<cv::Point3f>> objectPoints;
//	std::vector<std::vector<cv::Point3f>> objRealPoints;

	bool mustInitUndistort;
	int flag;
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
	cv::Mat map1, map2;
	cv::Mat grayImage;
	std::vector<cv::Mat> rvecs, tvecs;



private:
	bool addChessBoardPoints(String *strImageName);
	bool addPoints(const vector<Point2f>& imageCorners, const vector<Point3f>& objectCorners);
	double calibrate(cv::Size &imageSize);
	cv::Mat remap(cv::Mat &image);
	bool setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled);
};

#endif