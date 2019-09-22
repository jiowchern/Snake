// GUIRooler.h: interface for the CGUIRooler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIROOLER_H__40BD56D4_D7FB_421B_925A_8344B1FB16EE__INCLUDED_)
#define AFX_GUIROOLER_H__40BD56D4_D7FB_421B_925A_8344B1FB16EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUIBase.h"

class CGUIRoller : public CGUIBase  
{
protected:
	int miBack;//
	int miNext;//
	int miBody;//
	int miRoller;//
	
	
	int miMin;//最底下的值
	int miMax;//最高值
	int miPos;//目前的位置
	int miRimWidth;//寬度
	int miLength;//長度
	int miRegion;//區間
	bool mbRollerPress;
	
public:
	int GetPos(void);
	virtual LONG OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	bool SetPos(int iVal);
	virtual LONG OnMOUSEMOVE(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual LONG OnLBUTTONDOWN(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	virtual bool Display(void);
	virtual bool IsInit(void);
	bool Set(int X,int Y,int RimWidth,int Length,int Max,int Min,int Region);
	CGUIRoller();
	virtual ~CGUIRoller();
	virtual bool Init(JCGraphics *Grp,CTexManager *TM,JCString sHead,JCString sUnder,JCString sBody,JCString sRooler,DWORD dwColorKey=0xffff00ff);

};

#endif // !defined(AFX_GUIROOLER_H__40BD56D4_D7FB_421B_925A_8344B1FB16EE__INCLUDED_)
