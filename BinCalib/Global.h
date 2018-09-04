#ifndef _GLOBAL_H_
#define _GLOBAL_H_


const int CAMERA_WIDTH = 1080;
const int CAMERA_HEIGHT = 720;
const int NImage = 15;
const int ChessBoardSize_w = 8;
const int ChessBoardSize_h = 9;
//const CvSize ChessBoardSize = cvSize(ChessBoardSize_w, ChessBoardSize_h);
const int NPoints = ChessBoardSize_w * ChessBoardSize_h;
const float SquareWidth = 25;		//单目情况下不具有深度信息，所以不影响结果， 双目的情况下会有影响

#endif