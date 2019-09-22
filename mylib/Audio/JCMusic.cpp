
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
	CoInitialize(NULL); //��l��COM
	//�ЫئU�Ӫ���
	
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

	//�ѦҸ��
	/*CHAR strSoundPath[MAX_PATH]; //�s�x���֩Ҧb���|
	WCHAR wstrSoundPath[MAX_PATH]; //�s�xUNICODE�Φ������|
	GetCurrentDirectory(MAX_PATH, strSoundPath);
	strcat(strSoundPath, "\\Sounds\\");
	strcat(strSoundPath, "a.mp3"); //���]�n���񪺬OSounds�l�ؿ��U��a.mp3
	MultiByteToWideChar(CP_ACP, 0, strSoundPath, -1,wstrSoundPath, MAX_PATH);
	pGBuilder->RenderFile(wstrSoundPath, NULL); //�դJ���*/

	return mbInitOK;
}

int JCMusic::Play(void)
{
	if(!mbInitOK)
	{
		sProcMsg="��l�ƥ����\";
		return false;
	}
	
	pMControl->Run(); //����
	return 0;
}

// �����
int JCMusic::Stop(void)
{
	if(!mbInitOK)
	{
		sProcMsg="��l�ƥ����\";
		return false;
	}
	pMControl->Stop();
	pMPos->put_CurrentPosition(0); //���ʨ����Y
	return 0;
}

// �Ȱ�
int JCMusic::Pause(void)
{
	if(!mbInitOK)
	{
		sProcMsg="��l�ƥ����\";
		return false;
	}
	pMControl->Pause ();
	
	return 0;
}

// �q�ɮ׸̨��o����~
bool JCMusic::LoadFile(JCString sFileName)
{
	if(!mbInitOK)
	{
		sProcMsg="��l�ƥ����\";
		return false;
	}
	WCHAR wstrSoundPath[MAX_PATH]; //�s�xUNICODE�Φ������|
	MultiByteToWideChar(CP_ACP, 0, sFileName.GetBuffer (), -1,wstrSoundPath, MAX_PATH );
	pGBuilder->RenderFile(wstrSoundPath , NULL); //�դJ���
	pMPos->put_CurrentPosition(0); //���ʨ����Y	
	
	return true;
}

// �Ѱ�
void JCMusic::UnInit(void)
{
	DefSafeRelease(pMControl);
	DefSafeRelease(pMPos);
	DefSafeRelease(pGBuilder);
	CoUninitialize(); //����COM
}

// �����ɮ�... �ѼƬ��_�l��m
int JCMusic::Play(DWORD dwPos)
{
	if(!mbInitOK)
	{
		sProcMsg="��l�ƥ����\";
		return false;
	}
	pMPos->put_CurrentPosition(dwPos); //���ʨ����Y	
	
	Play();
	return 0;
}
