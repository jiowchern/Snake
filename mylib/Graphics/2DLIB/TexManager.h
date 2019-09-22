// TexManager.h: interface for the CTexManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXMANAGER_H__E8E9B6E3_ED14_4F29_87B5_0017A99DA811__INCLUDED_)
#define AFX_TEXMANAGER_H__E8E9B6E3_ED14_4F29_87B5_0017A99DA811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	���O�W��:����޲z��~
	�޲z����s�W�R���X�@�ǨϥΪ��p������
*/

#pragma comment (lib, "d3dx8.lib")
#include <D3dx8tex.h>

#include "..\..\Base\JCString.h"
#define DefMAXSTRINGLEN 255
/*
�ܼƩw�q����
S=Struct
D8=Direct3D8

*/
typedef struct _SD8TextureData
{
	DWORD dwColorKey;
	JCString sName;//�s���ɦW��
	D3DXIMAGE_INFO info;//�����T
	LPDIRECT3DTEXTURE8 pTex;//������
	bool IsUsed;//�O�_�Q�ϥ�
} SD8TextureData;
typedef SD8TextureData* pSD8TextureData;

class CTexManager  
{
private:
	LPDIRECT3DDEVICE8 pD3D8Dev;
	int iAmount;//�����`��
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
