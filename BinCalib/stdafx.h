// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "Global.h"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>

#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
using namespace Pylon;
using namespace Basler_GigECameraParams;

const Size ChessBoardSize = cvSize(ChessBoardSize_w, ChessBoardSize_h);
const Size ImageSize(CAMERA_WIDTH, CAMERA_HEIGHT);

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
