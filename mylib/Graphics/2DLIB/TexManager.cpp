// TexManager.cpp: implementation of the CTexManager class.
//
//////////////////////////////////////////////////////////////////////

#include "TexManager.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//本類別會建立一個SD8Texture的陣列指標，提供相關材質資訊給JCGraphics使用
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

//初始化 請填入D3D8的裝置指標和要建立的材質數量
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

//移除...其實可以當作Reset使用
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

//建立新材質 請輸入材質完整檔名與透明色 if為最大則代表沒找到此時為全部位置皆被使用之狀態
int CTexManager::Add(char *sFileName,DWORD dwColorKey)
{
	
	if(pD3D8Dev!=NULL)
	{
		JCString sTmp=sFileName;
		sTmp.ToLower ();
		//int iReUseTexNum=iAmount;//沒有使用到的材質 if為最大則代表沒找到此時為全部位置皆被使用之狀態
		int iIdx;
		/*
			檢查是否有重複使用的狀況
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
			找出未建立的空間建立之
		*/
		for(iIdx=0;iIdx<iAmount;iIdx++)
		{
			//如果材質未被使用
			if(!pSTexData[iIdx].IsUsed)
			{
				//D3DXIMAGE_INFO srcinfo;
				if( FAILED(D3DXCreateTextureFromFileEx(pD3D8Dev, sFileName, 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
                            D3DX_DEFAULT , dwColorKey,&pSTexData[iIdx].info , NULL, &pSTexData[iIdx].pTex  )) )
				{
					//sErrMsg="材質載入失敗\0";
					return 0;
				}
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!字串複製
				pSTexData[iIdx].sName="";
				pSTexData[iIdx].sName=sTmp.GetBuffer ();
				//pSTexData[iIdx].sName.ToLower ();
				//memset(pSTexData[iIdx].sName ,0,DefMAXSTRINGLEN);//先清除字串 避免比較字串時失誤
				//memcpy(pSTexData[iIdx].sName,sFileName,DefMAXSTRINGLEN);
				pSTexData[iIdx].dwColorKey =dwColorKey;
				pSTexData[iIdx].IsUsed=true;
				return iIdx+1;	
			}

		}

		
	}
	return 0;
}

//刪除一個材質資料
bool CTexManager::Del(int iNumber)
{
	if(iNumber==0)
		return false;//輸入的號碼有誤
	
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

//讀入材質檔名他會傳給他的編號 if他傳出的編號是0則代表沒找到
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

//刪除一個材質資料
bool CTexManager::Del(char *sFileName)
{
	int iResult=NameToNum(sFileName);
	if(iAmount>iResult)
	{
		return Del(iResult);
	}
	return false;
}


//取得一個材質資料指標
SD8TextureData* CTexManager::GetTextureData(int iNum)
{
	if(iNum==0)
		return NULL;//輸入的號碼有誤
	iNum-=1;
	if(pSTexData[iNum].IsUsed)
	{
		return (pSTexData+iNum);
	}
	return NULL;
}

//取得一個材質資料指標
SD8TextureData* CTexManager::GetTextureData(char *sFileName)
{
	int iResult=NameToNum(sFileName);
	if(iAmount>iResult)
		return GetTextureData(iResult);
	return NULL;
}


//檢查輸入個號碼是否為正確的範圍
bool CTexManager::ChkNumber(int iNum)

{
	iNum-=1;
	if(iNum<iAmount&&iNum>=0)
		return true;
	return false;
}
