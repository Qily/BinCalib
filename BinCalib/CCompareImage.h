#ifndef _COMPARE_IMAGE_H
#define _COMPARE_IMAGE_H

class CCompareImage
{
public:
	CCompareImage();
	~CCompareImage();

	void showDiff(Mat p_LImage, Mat p_RImage);

private:
	Mat m_GridImage;//��������ߺ��ͼ��
	Mat m_MergedImage;//�ϲ���õ�����ͼ��

private:
	Mat mergedImages(Mat p_LImage, Mat p_RImage);//�ϲ�����ͼ��
};

#endif