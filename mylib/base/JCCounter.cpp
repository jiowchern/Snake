#include "JCCounter.h"

JCCounter::JCCounter(void)
{


	LintEnd.QuadPart=0;
	bBegin=false;
	QueryPerformanceFrequency(&LintTC);//取得每秒頻率	
	iTimer=0;
}

JCCounter::~JCCounter(void)
{
}
// 傳入觸發時間,單位為 1ms
int JCCounter::SetTimer(int iTime)
{
	iTimer=iTime;
	bBegin=false;	
	return 0;
}
// 開始計時
int JCCounter::Begin(void)
{
	QueryPerformanceCounter(&LintBegin);//出始化開始時間
	bBegin=true;
	return 0;
}

// 檢查時間,時間到自動停止計時 out:真代表時間到 in:超過多少時間
bool JCCounter::IsTimeUp(int* piOverTime)
{
	if(bBegin)
	{
		QueryPerformanceCounter(&LintEnd);
		if((LintEnd.QuadPart-LintBegin.QuadPart) >(LintTC.QuadPart *(float)iTimer/DefTIMESCALE))
		{
			/*
			//求剩餘時間
			piOverTime=(LintEnd.QuadPart-LintBegin.QuadPart)-(LintTC.QuadPart *(float)(iTimer/DefTIMESCALE));
			*/
			bBegin=false;
			return true;
		}	
	}
	return false;
}
