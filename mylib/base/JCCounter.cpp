#include "JCCounter.h"

JCCounter::JCCounter(void)
{


	LintEnd.QuadPart=0;
	bBegin=false;
	QueryPerformanceFrequency(&LintTC);//���o�C���W�v	
	iTimer=0;
}

JCCounter::~JCCounter(void)
{
}
// �ǤJĲ�o�ɶ�,��쬰 1ms
int JCCounter::SetTimer(int iTime)
{
	iTimer=iTime;
	bBegin=false;	
	return 0;
}
// �}�l�p��
int JCCounter::Begin(void)
{
	QueryPerformanceCounter(&LintBegin);//�X�l�ƶ}�l�ɶ�
	bBegin=true;
	return 0;
}

// �ˬd�ɶ�,�ɶ���۰ʰ���p�� out:�u�N��ɶ��� in:�W�L�h�֮ɶ�
bool JCCounter::IsTimeUp(int* piOverTime)
{
	if(bBegin)
	{
		QueryPerformanceCounter(&LintEnd);
		if((LintEnd.QuadPart-LintBegin.QuadPart) >(LintTC.QuadPart *(float)iTimer/DefTIMESCALE))
		{
			/*
			//�D�Ѿl�ɶ�
			piOverTime=(LintEnd.QuadPart-LintBegin.QuadPart)-(LintTC.QuadPart *(float)(iTimer/DefTIMESCALE));
			*/
			bBegin=false;
			return true;
		}	
	}
	return false;
}
