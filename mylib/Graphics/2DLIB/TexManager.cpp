// TexManager.cpp: implementation of the CTexManager class.
//
//////////////////////////////////////////////////////////////////////

#include "TexManager.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//�����O�|�إߤ@��SD8Texture���}�C���СA���Ѭ��������T��JCGraphics�ϥ�
CTexManager::CTexManager()
{
	pSTexData=NULL;
	iAmount=0;
	pD3D8Dev=NULL;
}

CTexManager::~CTexManager()
{
	Release();
	iAmount=0;
	pD3D8Dev=NULL;
}

//��l�� �ж�JD3D8���˸m���ЩM�n�إߪ�����ƶq
bool CTexManager::Init(LPDIRECT3DDEVICE8 pDev,int Amount)
{
	if (pDev==NULL)	
		return false;
	pSTexData=new SD8TextureData[Amount];
	int iIdx;
	for(iIdx=0;iIdx<Amount;iIdx++)
	{
		pSTexData[iIdx].sName="";
		memset(&pSTexData[iIdx].info,0,sizeof(D3DXIMAGE_INFO));
		pSTexData[iIdx].IsUsed=false;
		pSTexData[iIdx].pTex=NULL;
		pSTexData[iIdx].dwColorKey=0;
	}
	iAmount=Amount;
	pD3D8Dev=pDev;
	return true;
}

//����...���i�H��@Reset�ϥ�
void CTexManager::Release()
{
	int iIdx;
	for(iIdx=0;iIdx<iAmount;iIdx++)
	{
		memset(&pSTexData[iIdx].info,0,sizeof(D3DXIMAGE_INFO));
		pSTexData[iIdx].sName="";
		pSTexData[iIdx].IsUsed=false;
		pSTexData[iIdx].dwColorKey=0;
		if(pSTexData[iIdx].pTex!=NULL)
		{
			pSTexData[iIdx].pTex->Release();
			pSTexData[iIdx].pTex=NULL;
		}
	}	
}

//�إ߷s���� �п�J���觹���ɦW�P�z���� if���̤j�h�N��S��즹�ɬ�������m�ҳQ�ϥΤ����A
int CTexManager::Add(char *sFileName,DWORD dwColorKey)
{
	
	if(pD3D8Dev!=NULL)
	{
		JCString sTmp=sFileName;
		sTmp.ToLower ();
		//int iReUseTexNum=iAmount;//�S���ϥΨ쪺���� if���̤j�h�N��S��즹�ɬ�������m�ҳQ�ϥΤ����A
		int iIdx;
		/*
			�ˬd�O�_�����ƨϥΪ����p
		*/
		for(iIdx=0;iIdx<iAmount;iIdx++)
		{
			if(pSTexData[iIdx].IsUsed&&pSTexData[iIdx].sName.FullCompared (sTmp.GetBuffer ()))
			{
				//iReUseTexNum=iIdx;
				pSTexData[iIdx].dwColorKey =dwColorKey;
				return iIdx+1;	
			}
		}

		/*
			��X���إߪ��Ŷ��إߤ�
		*/
		for(iIdx=0;iIdx<iAmount;iIdx++)
		{
			//�p�G���襼�Q�ϥ�
			if(!pSTexData[iIdx].IsUsed)
			{
				//D3DXIMAGE_INFO srcinfo;
				if( FAILED(D3DXCreateTextureFromFileEx(pD3D8Dev, sFileName, 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
                            D3DX_DEFAULT , dwColorKey,&pSTexData[iIdx].info , NULL, &pSTexData[iIdx].pTex  )) )
				{
					//sErrMsg="������J����\0";
					return 0;
				}
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�r��ƻs
				pSTexData[iIdx].sName="";
				pSTexData[iIdx].sName=sTmp.GetBuffer ();
				//pSTexData[iIdx].sName.ToLower ();
				//memset(pSTexData[iIdx].sName ,0,DefMAXSTRINGLEN);//���M���r�� �קK����r��ɥ��~
				//memcpy(pSTexData[iIdx].sName,sFileName,DefMAXSTRINGLEN);
				pSTexData[iIdx].dwColorKey =dwColorKey;
				pSTexData[iIdx].IsUsed=true;
				return iIdx+1;	
			}

		}

		
	}
	return 0;
}

//�R���@�ӧ�����
bool CTexManager::Del(int iNumber)
{
	if(iNumber==0)
		return false;//��J�����X���~
	
	iNumber-=1;
	if(pSTexData[iNumber].IsUsed )
	{
		memset(&pSTexData[iNumber].info,0,sizeof(D3DXIMAGE_INFO));
		//memset(pSTexData[iNumber].sName,0,DefMAXSTRINGLEN);
		pSTexData[iNumber].sName="";
		pSTexData[iNumber].IsUsed=false;
		pSTexData[iNumber].dwColorKey=0;
		if(pSTexData[iNumber].pTex!=NULL)
		{
			pSTexData[iNumber].pTex->Release();
			pSTexData[iNumber].pTex=NULL;
		}
		return true;
	}
	return false;
}

//Ū�J�����ɦW�L�|�ǵ��L���s�� if�L�ǥX���s���O0�h�N��S���
int CTexManager::NameToNum(char *sFileName)
{
	int iIdx;
	JCString sTmp;
	sTmp=sFileName;
	sTmp.ToLower ();
	for(iIdx=0;iIdx<iAmount;iIdx++)
	{
		if(pSTexData[iIdx].IsUsed&&pSTexData[iIdx].sName.FullCompared(sTmp.GetBuffer ()))
		{	
			
			return iIdx+1;
		}
	}
	return 0;
}

//�R���@�ӧ�����
bool CTexManager::Del(char *sFileName)
{
	int iResult=NameToNum(sFileName);
	if(iAmount>iResult)
	{
		return Del(iResult);
	}
	return false;
}


//���o�@�ӧ����ƫ���
SD8TextureData* CTexManager::GetTextureData(int iNum)
{
	if(iNum==0)
		return NULL;//��J�����X���~
	iNum-=1;
	if(pSTexData[iNum].IsUsed)
	{
		return (pSTexData+iNum);
	}
	return NULL;
}

//���o�@�ӧ����ƫ���
SD8TextureData* CTexManager::GetTextureData(char *sFileName)
{
	int iResult=NameToNum(sFileName);
	if(iAmount>iResult)
		return GetTextureData(iResult);
	return NULL;
}


//�ˬd��J�Ӹ��X�O�_�����T���d��
bool CTexManager::ChkNumber(int iNum)

{
	iNum-=1;
	if(iNum<iAmount&&iNum>=0)
		return true;
	return false;
}
