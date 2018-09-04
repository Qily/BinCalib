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

	Mat R, T, E, F;						//R旋转矢量， T平移矢量, E本征矢量， F基础矢量		
	Mat Rl, Rr, Pl, Pr, Q;			//校正旋转矩阵R, 投影矩阵P， 重投影矩阵Q
	Mat mapLx, mapLy, mapRx, mapRy;		//映射表
	Rect validROIL, validROIR;			// 图片校正之后。会对图像进行裁剪，这是裁剪之后的区域

	Mat rectifyImageL;
	Mat rectifyImageR;
private:
	void DoubCalib::PrintInfo();
	cv::Mat Remap(cv::Mat &image, Mat cameraMatrix, Mat distCoeffs, Mat map1, Mat map2);
};


#endif