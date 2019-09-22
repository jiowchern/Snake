
#include "jcmusic.h"

JCMusic::JCMusic(void)
{
	pGBuilder=NULL;
	pMControl=NULL;
	pMPos=NULL;

	sProcMsg="";
	mbInitOK=false;
}

JCMusic::~JCMusic(void)
{
	
	UnInit();	

}

bool JCMusic::Init(void)
{
	if(mbInitOK)
		return mbInitOK;
	CoInitialize(NULL); //初始化COM
	//創建各個物件
	
	CoCreateInstance(CLSID_FilterGraph, NULL,
	CLSCTX_INPROC, IID_IGraphBuilder, (void**)&pGBuilder);
	if(pGBuilder!=NULL)
	{
		pGBuilder->QueryInterface(IID_IMediaControl, (void**)&pMControl);
		pGBuilder->QueryInterface(IID_IMediaPosition, (void**)&pMPos);
		if(pMControl!=NULL && pMPos!=NULL)
		{
			mbInitOK=true;;
		}
		else
			sProcMsg="QueryInterfaceFail.";
	}
	else
		sProcMsg="pGBuilder Create Fail.";

	//參考資料
	/*CHAR strSoundPath[MAX_PATH]; //存儲音樂所在路徑
	WCHAR wstrSoundPath[MAX_PATH]; //存儲UNICODE形式的路徑
	GetCurrentDirectory(MAX_PATH, strSoundPath);
	strcat(strSoundPath, "\\Sounds\\");
	strcat(strSoundPath, "a.mp3"); //假設要播放的是Sounds子目錄下的a.mp3
	MultiByteToWideChar(CP_ACP, 0, strSoundPath, -1,wstrSoundPath, MAX_PATH);
	pGBuilder->RenderFile(wstrSoundPath, NULL); //調入文件*/

	return mbInitOK;
}

int JCMusic::Play(void)
{
	if(!mbInitOK)
	{
		sProcMsg="初始化未成功";
		return false;
	}
	
	pMControl->Run(); //播放
	return 0;
}

// 停止撥放
int JCMusic::Stop(void)
{
	if(!mbInitOK)
	{
		sProcMsg="初始化未成功";
		return false;
	}
	pMControl->Stop();
	pMPos->put_CurrentPosition(0); //移動到文件頭
	return 0;
}

// 暫停
int JCMusic::Pause(void)
{
	if(!mbInitOK)
	{
		sProcMsg="初始化未成功";
		return false;
	}
	pMControl->Pause ();
	
	return 0;
}

// 從檔案裡取得音樂~
bool JCMusic::LoadFile(JCString sFileName)
{
	if(!mbInitOK)
	{
		sProcMsg="初始化未成功";
		return false;
	}
	WCHAR wstrSoundPath[MAX_PATH]; //存儲UNICODE形式的路徑
	MultiByteToWideChar(CP_ACP, 0, sFileName.GetBuffer (), -1,wstrSoundPath, MAX_PATH );
	pGBuilder->RenderFile(wstrSoundPath , NULL); //調入文件
	pMPos->put_CurrentPosition(0); //移動到文件頭	
	
	return true;
}

// 解除
void JCMusic::UnInit(void)
{
	DefSafeRelease(pMControl);
	DefSafeRelease(pMPos);
	DefSafeRelease(pGBuilder);
	CoUninitialize(); //釋放COM
}

// 撥放檔案... 參數為起始位置
int JCMusic::Play(DWORD dwPos)
{
	if(!mbInitOK)
	{
		sProcMsg="初始化未成功";
		return false;
	}
	pMPos->put_CurrentPosition(dwPos); //移動到文件頭	
	
	Play();
	return 0;
}
