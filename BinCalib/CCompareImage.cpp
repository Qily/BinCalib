#include "stdafx.h"
#include "CCompareImage.h"
CCompareImage::CCompareImage()
{
}



CCompareImage::~CCompareImage()
{
}

Mat CCompareImage::mergedImages(Mat p_LImage, Mat p_RImage){
	Mat LImage;
	Mat RImage;

	//截取有效区域（去边框）
	LImage = p_LImage;//(Range(120, 1080), Range(160, 1440));
	RImage = p_RImage;// (Range(120, 1080), Range(160, 1440));

	if (LImage.cols == RImage.cols&&LImage.rows == RImage.rows){
		//图片过大，先将图片缩小为原来的1/2
		Mat _LImage(LImage.cols / 2, LImage.rows / 2, CV_8UC3);
		Mat _RImage(RImage.cols / 2, RImage.rows / 2, CV_8UC3);

		resize(LImage, _LImage, cv::Size(), 0.5, 0.5);
		resize(RImage, _RImage, cv::Size(), 0.5, 0.5);

		Size size(_LImage.cols * 2, _LImage.rows);

		Mat out_LImage, out_RImage;

		m_MergedImage.create(size, CV_MAKETYPE(_LImage.depth(), 3));
		m_MergedImage = Scalar::all(0);
		out_LImage = m_MergedImage(Rect(0, 0, _LImage.cols, _LImage.rows));
		out_RImage = m_MergedImage(Rect(_LImage.cols, 0, _RImage.cols, _RImage.rows));

		_LImage.copyTo(out_LImage);
		_RImage.copyTo(out_RImage);

		for (int i = 0; i<m_MergedImage.rows; i++)
			for (int j = 0; j<m_MergedImage.cols; j++)
			{
			if ((i % (m_MergedImage.rows / 15)) == 0)
				m_MergedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
			}
	}

	//imwrite("./CorrectImage/compareImage.jpg", m_MergedImage);

	return m_MergedImage;
}

void CCompareImage::showDiff(Mat p_LImage, Mat p_RImage){

	mergedImages(p_LImage, p_RImage);
	namedWindow("ImageCompare", CV_WINDOW_AUTOSIZE);
	imshow("ImageCompare", m_MergedImage);

	waitKey(0);
}