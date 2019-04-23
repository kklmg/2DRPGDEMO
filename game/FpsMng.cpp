#include "FpsMng.h"

#define dTIMEGETTIME timeGetTime()* 0.001

CFpsMng::CFpsMng()
{
	m_dwFps = 0;
	SetFPS(0);
}

CFpsMng::~CFpsMng()
{
}

void CFpsMng::SetFPS(DWORD dwFPS)
{
	///// �����ð� ����
	if (dwFPS == 0)
	{
		m_dMPF = 0.0;
	}
	else ///// �Ϲ�
	{
		m_dMPF = 1.000 / dwFPS;
		m_dLastTime = dTIMEGETTIME;
	}

}

void CFpsMng::UpdateDeltaTime() 
{
	


}

DWORD CFpsMng::GetFPS()
{
	m_dOneSecDeltaTime = dTIMEGETTIME - m_dOneSecLastTime;

	m_dwFramesRendered++;

	if (m_dOneSecDeltaTime > 1.000)
	{
		m_dwFps = m_dwFramesRendered;
		m_dwFramesRendered = 0;
		m_dOneSecLastTime = dTIMEGETTIME;
	}

	return m_dwFps;
}

void CFpsMng::FrameWaiting()
{
	///// 1 frame ó���ð� ( ������, ���, ��Ÿ )		
	//m_dProcTime = dTIMEGETTIME - m_dLastTime;		

	/////
	while (dTIMEGETTIME - m_dLastTime < m_dMPF);

	/////
	m_dLastTime = dTIMEGETTIME;
}

//void CFpsMng::FrameWaitingEx()
//{
//	// ::Sleep();	
//}
