
#ifndef DefJCCOUNTER 
#define DefJCCOUNTER 001
#define DefTIMESCALE	1000 //每秒時間刻度
#include <windows.h>
class JCCounter
{
private:
	//設定計時
	LARGE_INTEGER LintTC;	//每秒計數次數
	LARGE_INTEGER LintBegin;//開始累積次數
	LARGE_INTEGER LintEnd;	//結束累積次數
	bool bBegin;
	int iTimer;
public:

	JCCounter(void);
	~JCCounter(void);

	// 傳入觸發時間,單位為 1ms//設定觸發時間
	int SetTimer(int iTime);

	//計時開始
	// 開始計時
	int Begin(void);
	//檢查
	// 檢查時間,時間到自動停止計時 out:真代表時間到 in:超過多少時間
	bool IsTimeUp(int* piOverTime);
};
#endif