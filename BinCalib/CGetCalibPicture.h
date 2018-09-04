#ifndef _GET_CALIB_PICTURE_H
#define _GET_CALIB_PICTURE_H
class CGetCalibPicture
{
public:

	CGetCalibPicture();
	~CGetCalibPicture();
	bool	SavePicture();
	String *GetFirstImageNameL();
	String *GetFirstImageNameR();
	
	
private:
	String *strFirstImageNameL;
	String *strFirstImageNameR;
	static void onMouse(int event, int x, int y, int flag, void *param);
	bool isOver;
	bool isWriteImg;
	bool isStart;

};
#endif