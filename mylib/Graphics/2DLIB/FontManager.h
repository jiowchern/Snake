// FontManager.h: interface for the CFontManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTMANAGER_H__5C1FD32B_70B8_4082_8860_E7D8E3B20C48__INCLUDED_)
#define AFX_FONTMANAGER_H__5C1FD32B_70B8_4082_8860_E7D8E3B20C48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\BASED3D\JC_D3D.h"
#include "..\..\Base\JCString.h"
/*
	�@�Ӧs��P�������r�����O

	
*/
typedef struct _SFontFmt
{
	DWORD dwFontColor; //��r�C��ARGB
	int iFontSize;//�r���j�p P.S �u�ۦ氪��
	int iFontWeight;//�ۦ�X�t
	char* pcFontName;//�ۦ�
	int iShowTextPosX;//��ܦ�m
	int iShowTextPosY;
	JCString sText; //��r���e
	int bEnable; //�ϧ_�w�O�ϥΪ��A
	LPD3DXFONT pFont;//D3DXFONT����
} SFontFmt;

class CFontManager  
{
private:
	LPDIRECT3DDEVICE8 pD3D8Dev;
	int iAmount;//��r�ƶq
	SFontFmt *pFont;
public:
	bool Draw(int iNum,RECT rt,DWORD dwFmt);
	bool Draw(int iNum,RECT rt);
	RECT GetTextRect(int iNum);
	SFontFmt* GetFontFmt(int iNum);
	void Release(void);
	int GetNumberByText(char * sText);
	bool Delete(int iNum);
	bool Draw(int iNum);
	bool SetText(int iNum,JCString sText,int iX,int iY,DWORD dwColor=0xFFFFFFFF);
	int Add(int iFontSize=16,DWORD dwFontColor=0xFFFFFFFF,char * sFontName="�s�ө���\0",int iFontWeight=400);
	bool Init(LPDIRECT3DDEVICE8 pDev,int Amount);
	
	CFontManager();
	virtual ~CFontManager();
	
};

#endif // !defined(AFX_FONTMANAGER_H__5C1FD32B_70B8_4082_8860_E7D8E3B20C48__INCLUDED_)
