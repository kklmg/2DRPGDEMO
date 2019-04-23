#pragma once
#include <windows.h>
#include <mmsystem.h>
#include "DxMng.h"
#pragma comment( lib,"winmm.lib" )
#ifndef __FPSMNG_H__
#define __FPSMNG_H__          

class CFpsMng
{
public:
	CFpsMng();						// ����Ʈ�� �����ð� ����
	virtual ~CFpsMng();

	void UpdateDeltaTime();

	void  SetFPS(DWORD dwFPS = 0);	// dwFPS == 0, �����ð� ����
	DWORD GetFPS(void);				// ���� FPS�� ��´�

	void  FrameWaiting(void);		// ������ �����Ӽ��� ���� ( Polling  )
	void  FrameWaitingEx(void);		// ������ �����Ӽ��� ���� ( Blocking )

private:
	DWORD m_dwFramesRendered;
	DWORD m_dwFps;

	double m_dOneSecLastTime;		// 1 second
	double m_dOneSecDeltaTime;		// 1 second
	double m_dMPF;					// Millisecond Per Frame
	double m_dLastTime;				// Timer

	double m_dProcTime;				// 1 Frame ó���ð�
};

#endif