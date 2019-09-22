// TexManager.h: interface for the CTexManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXMANAGER_H__E8E9B6E3_ED14_4F29_87B5_0017A99DA811__INCLUDED_)
#define AFX_TEXMANAGER_H__E8E9B6E3_ED14_4F29_87B5_0017A99DA811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	類別名稱:材質管理器~
	管理材質新增刪除合一些使用狀況的控制
*/

#pragma comment (lib, "d3dx8.lib")
#include <D3dx8tex.h>

#include "..\..\Base\JCString.h"
#define DefMAXSTRINGLEN 255
/*
變數定義說明
S=Struct
D8=Direct3D8

*/
typedef struct _SD8TextureData
{
	DWORD dwColorKey;
	JCString sName;//存放檔名用
	D3DXIMAGE_INFO info;//材質資訊
	LPDIRECT3DTEXTURE8 pTex;//材質資料
	bool IsUsed;//是否被使用
} SD8TextureData;
typedef SD8TextureData* pSD8TextureData;

class CTexManager  
{
private:
	LPDIRECT3DDEVICE8 pD3D8Dev;
	int iAmount;//材質總數
	SD8TextureData* pSTexData;
public:
	void Release(void);
	bool Init(LPDIRECT3DDEVICE8 pDev,int Amount);
	CTexManager();
	virtual ~CTexManager();
public:
	bool ChkNumber(int iNum);
	SD8TextureData* GetTextureData(char* sFileName);
	SD8TextureData* GetTextureData(int iNum);
	bool Del(char *sFileName);
	int NameToNum(char *sFileName);
	bool Del(int iNumber);
	int Add(char *sFileName,DWORD dwColorKey=0xffff00ff);
	
};

#endif // !defined(AFX_TEXMANAGER_H__E8E9B6E3_ED14_4F29_87B5_0017A99DA811__INCLUDED_)
