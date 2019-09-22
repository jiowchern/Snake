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
	一個存放與控制平面文字的類別

	
*/
typedef struct _SFontFmt
{
	DWORD dwFontColor; //文字顏色ARGB
	int iFontSize;//字型大小 P.S 只自行高度
	int iFontWeight;//自行出系
	char* pcFontName;//自行
	int iShowTextPosX;//顯示位置
	int iShowTextPosY;
	JCString sText; //文字內容
	int bEnable; //使否已是使用狀態
	LPD3DXFONT pFont;//D3DXFONT指標
} SFontFmt;

class CFontManager  
{
private:
	LPDIRECT3DDEVICE8 pD3D8Dev;
	int iAmount;//文字數量
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
	int Add(int iFontSize=16,DWORD dwFontColor=0xFFFFFFFF,char * sFontName="新細明體\0",int iFontWeight=400);
	bool Init(LPDIRECT3DDEVICE8 pDev,int Amount);
	
	CFontManager();
	virtual ~CFontManager();
	
};

#endif // !defined(AFX_FONTMANAGER_H__5C1FD32B_70B8_4082_8860_E7D8E3B20C48__INCLUDED_)
