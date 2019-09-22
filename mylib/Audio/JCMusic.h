#ifndef DefJCMUSIC
#define DefJCMUSIC
#pragma once
#include <dshow.h> //Play MP3 ��
#include "..\\Base\JCString.h" //JC�U�Φr����
#define DefSafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}
#pragma comment (lib, "strmiids.lib")
class JCMusic
{
public:
	JCMusic(void);
	~JCMusic(void);
	bool mbInitOK;
protected:
	// �B�̫᪺�T����
	IGraphBuilder* pGBuilder;
	IMediaControl* pMControl;
	IMediaPosition* pMPos;

	JCString sProcMsg;
	
public:
	// �����
	int Stop(void);
	// �Ȱ�
	int Pause(void);
	// �q�ɮ׸̨��o����~
	bool LoadFile(JCString sFileName);

	bool Init(void);

	int Play(void);
	// �Ѱ�
	void UnInit(void);
	// �����ɮ�... �ѼƬ��_�l��m
	int Play(DWORD dwPos);
};
#endif