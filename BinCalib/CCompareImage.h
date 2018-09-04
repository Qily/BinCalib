#ifndef _COMPARE_IMAGE_H
#define _COMPARE_IMAGE_H

class CCompareImage
{
public:
	CCompareImage();
	~CCompareImage();

	void showDiff(Mat p_LImage, Mat p_RImage);

private:
	Mat m_GridImage;//添加网格线后的图像
	Mat m_MergedImage;//合并获得的两张图像

private:
	Mat mergedImages(Mat p_LImage, Mat p_RImage);//合并两张图像
};

#endif