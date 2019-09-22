// GUIBase.h: interface for the CGUIBase class.
//
//////////////////////////////////////////////////////////////////////
/*

  基本的Gui類別


*/
#if !defined(AFX_GUIBASE_H__45D8981A_A9F5_4B1B_88D6_209B17B50CA0__INCLUDED_)
#define AFX_GUIBASE_H__45D8981A_A9F5_4B1B_88D6_209B17B50CA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\2dlib\jcgraphics.h"
#include "..\\..\\Base\JCString.h"
#include "..\\2DLIB\\TexManager.h"
#include "..\\2DLIB\\FontManager.h"
class CGUIBase ;
#define DefDim(x) (sizeof(x)/sizeof(x[0]))
//訊息對照表


class CGUIBase  
{
private:
	int iColor;
protected:
	inline bool IsInit(void);
	//屬性
	int x;int y;//絕對位置x,y
	int Width;int Height;//長 寬 
	
	DWORD ColorKey;
	JCGraphics *pGrp;
	char *sErrMsg;
	
	bool bIsShow;
	bool mbActive;
	CFontManager *pCFontM;//文字管理器指標
	CTexManager *pCTexM;//材質管理器指標
public:
	virtual void Resize(int iWidth,int iHeight);
	virtual void Location(int ix,int iy);
	virtual void Release(void);
	bool IsRange(int x,int y);
	virtual LONG OnLBUTTONDOWN(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	virtual LONG OnLBUTTONUP(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	virtual LONG OnMOUSEMOVE(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	virtual LONG OnCHAR(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	virtual LONG OnKEYDOWN(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	bool GetWinMessage(HWND hWnd,UINT Msg,WPARAM wp,LPARAM lp);
	//方法
	virtual bool Display(void);
	bool Hide(void);
	bool Show(void);
	

	//一般函數
	virtual bool Init(JCGraphics *Grp,DWORD dwColorKey);
	virtual char* GetErrMessage(void)
	{
		return sErrMsg;
	};
	CGUIBase();
	virtual ~CGUIBase();
	int Depth;//深度
	//int miRim;
};



	
	



#endif // !defined(AFX_GUIBASE_H__45D8981A_A9F5_4B1B_88D6_209B17B50CA0__INCLUDED_)
