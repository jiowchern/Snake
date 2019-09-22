// GUIButton.h: interface for the CGUIButton class.
//
//////////////////////////////////////////////////////////////////////
/*
	模擬按鈕
*/
#if !defined(AFX_GUIBUTTON_H__9DBA9552_0104_4CC7_A345_E1B87747D46A__INCLUDED_)
#define AFX_GUIBUTTON_H__9DBA9552_0104_4CC7_A345_E1B87747D46A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUIBase.h"

//滑鼠狀態
#define DefONMOUSENORMAL 0
#define DefONMOUSEMOVE 1
#define DefONMOUSEDOWN 2
class CGUIButton : public CGUIBase  
{
private:
	

	int iText;//文字內容...編號
	
	int iBG[3];//背景圖...正常時候,滑鼠在上面時候,當滑鼠按下時候
	int iCurrentBG;//目前顯示的圖形

	
public:
	void Location(int ix,int iy);
	void ResetText(void);
	void Resize(int iWidth,int iHeight);
	
	virtual void Release (void);
	
	virtual LONG OnLBUTTONUP(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	virtual LONG OnMOUSEMOVE(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);

	inline bool IsInit(void);
	virtual bool SetText(JCString text,int iSize,int color=0xffffffff);
	CGUIButton();
	virtual ~CGUIButton();

	virtual LONG OnLBUTTONDOWN(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
//	virtual bool GetWinMessage(HWND hWnd,UINT Msg,WPARAM wp,LPARAM lp);
	//方法
	virtual bool Display(void);
	
	

	//一般函數

	//初始化
	virtual bool Init
				(JCGraphics *Grp //JCGrapgics指標
				,CFontManager *FM//文字管理器
				,CTexManager *TM//材質管理器
				,JCString Text//內文
				,JCString BGNormal//背景圖檔名1
				,JCString BGOnMouse//背景圖檔名2
				,JCString BGOnClick//背景圖檔名3
				,int x
				,int y
				,int Width
				,int Height
				,DWORD dwColorKey=0xffff00ff
				);
	// 取得按鍵狀態
	int GetState(void);
};

#endif // !defined(AFX_GUIBUTTON_H__9DBA9552_0104_4CC7_A345_E1B87747D46A__INCLUDED_)
