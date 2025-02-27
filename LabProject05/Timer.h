#pragma once
#include"stdafx.h"
#include<timeapi.h>
//이 친구는 애니메이션 처리와 프레임 레이트를 계산한다. 타이머 관리 클래스
const ULONG MAX_SAMPLE_COUNT = 50; //50회의 프레임 처리시간을 누적해 평균한다.
class CGameTimer
{
public:
	CGameTimer();
	virtual ~CGameTimer();
	void Start() {};
	void Stop() {};
	void Reset();
	void Tick(float fLockFPS = 0.0f);//타이머의 시간 갱신
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0);//FPS RETURN
	float GetTimeElapsed();//프레임의 평균 경과 시간을 반환
private:
	bool m_bHardwareHasPerformanceCounter;//컴퓨터가 performanceCounter를 갖고 있는가?
	float m_fTimeScale;//SCALE COUNTER의 양
	float m_fTimeElapsed;// 마지막 프레임 이후 지난 시간
	__int64 m_nCurrentTime;//현재의 시간
	__int64 m_nLastTime;// 마지막 프레임의 시간
	__int64 m_nPerformanceFrequency;//컴퓨터의 Performance Frequency
	float m_fFrameTime[MAX_SAMPLE_COUNT];//프레임 시간을 누적하기 위한 배열
	ULONG m_nSampleCount;//누적된 프레임 횟수
	unsigned long m_nCurrentFrameRate;//현재의 프레임레이트
	unsigned long m_nFramesPerSecond;//초당 프레임 수
	float m_fFPSTimeElapsed;//프레임레이트 계산 소요 시간

	bool m_bStopped;

};

