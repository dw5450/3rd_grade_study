#pragma once
class DoubleBuffering {
	HANDLE hBuffer[2];
	int nScreenIndex;
	int size_x, size_y;
public:
	DoubleBuffering(int mapX, int mapY);
	~DoubleBuffering();
	void gotoxy(int x, int y, HANDLE g_hBuffer);
	void BufferWrite(int x, int y, char *string);
	void BufferFlipping();
	void ClearBuffer();
};
//[출처] [C++]콘솔창 지렁이 게임 - 콘솔창 더블 버퍼링 추가 | 작성자 KK1