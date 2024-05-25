#pragma once
#include"stdafx.h"
#include<timeapi.h>
//�� ģ���� �ִϸ��̼� ó���� ������ ����Ʈ�� ����Ѵ�. Ÿ�̸� ���� Ŭ����
const ULONG MAX_SAMPLE_COUNT = 50; //50ȸ�� ������ ó���ð��� ������ ����Ѵ�.
class CGameTimer
{
public:
	CGameTimer();
	virtual ~CGameTimer();
	void Start() {};
	void Stop() {};
	void Reset();
	void Tick(float fLockFPS = 0.0f);//Ÿ�̸��� �ð� ����
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0);//FPS RETURN
	float GetTimeElapsed();//�������� ��� ��� �ð��� ��ȯ
private:
	bool m_bHardwareHasPerformanceCounter;//��ǻ�Ͱ� performanceCounter�� ���� �ִ°�?
	float m_fTimeScale;//SCALE COUNTER�� ��
	float m_fTimeElapsed;// ������ ������ ���� ���� �ð�
	__int64 m_nCurrentTime;//������ �ð�
	__int64 m_nLastTime;// ������ �������� �ð�
	__int64 m_nPerformanceFrequency;//��ǻ���� Performance Frequency
	float m_fFrameTime[MAX_SAMPLE_COUNT];//������ �ð��� �����ϱ� ���� �迭
	ULONG m_nSampleCount;//������ ������ Ƚ��
	unsigned long m_nCurrentFrameRate;//������ �����ӷ���Ʈ
	unsigned long m_nFramesPerSecond;//�ʴ� ������ ��
	float m_fFPSTimeElapsed;//�����ӷ���Ʈ ��� �ҿ� �ð�

	bool m_bStopped;

};

