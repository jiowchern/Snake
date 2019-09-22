#ifndef DefJCMUSIC
#define DefJCMUSIC
#pragma once
#include <dshow.h> //Play MP3 用
#include "..\\Base\JCString.h" //JC萬用字串檔
#define DefSafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}
#pragma comment (lib, "strmiids.lib")
class JCMusic
{
public:
	JCMusic(void);
	~JCMusic(void);
	bool mbInitOK;
protected:
	// 處裡後的訊息欄
	IGraphBuilder* pGBuilder;
	IMediaControl* pMControl;
	IMediaPosition* pMPos;

	JCString sProcMsg;
	
public:
	// 停止撥放
	int Stop(void);
	// 暫停
	int Pause(void);
	// 從檔案裡取得音樂~
	bool LoadFile(JCString sFileName);

	bool Init(void);

	int Play(void);
	// 解除
	void UnInit(void);
	// 撥放檔案... 參數為起始位置
	int Play(DWORD dwPos);
};
#endif