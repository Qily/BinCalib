#ifndef _DOUB_CALIB_H_
#define _DOUB_CALIB_H_



class DoubCalib
{
public:

	DoubCalib::DoubCalib();
	DoubCalib(Mat CamMatrixL, Mat distCoeffL, Mat CamMatrixR, Mat distCoeffR,
		std::vector<std::vector<cv::Point3f>> _objRealPoint, std::vector<std::vector<cv::Point2f>> _imagePointL,
		std::vector<std::vector<cv::Point2f>> _imagePointR);
	~DoubCalib();
	bool ExDoubCalib();
private:
	Mat m_CamMatrixL;
	Mat m_distCoeffL;
	Mat m_CamMatrixR;
	Mat m_distCoeffR;
	std::vector<std::vector<cv::Point3f>> m_objRealPoint;
	std::vector<std::vector<cv::Point2f>> m_imagePointL;
	std::vector<std::vector<cv::Point2f>> m_imagePointR;

	Mat R, T, E, F;						//R��תʸ���� Tƽ��ʸ��, E����ʸ���� F����ʸ��		
	Mat Rl, Rr, Pl, Pr, Q;			//У����ת����R, ͶӰ����P�� ��ͶӰ����Q
	Mat mapLx, mapLy, mapRx, mapRy;		//ӳ���
	Rect validROIL, validROIR;			// ͼƬУ��֮�󡣻��ͼ����вü������ǲü�֮�������

	Mat rectifyImageL;
	Mat rectifyImageR;
private:
	void DoubCalib::PrintInfo();
	cv::Mat Remap(cv::Mat &image, Mat cameraMatrix, Mat distCoeffs, Mat map1, Mat map2);
};


#endif