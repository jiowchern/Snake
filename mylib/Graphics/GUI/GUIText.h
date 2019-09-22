// GUIText.h: interface for the CGUIText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUITEXT_H__9BFC8623_2814_44C8_BC81_2E51696FE26F__INCLUDED_)
#define AFX_GUITEXT_H__9BFC8623_2814_44C8_BC81_2E51696FE26F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "..\\..\\Base\JCString.h"
//#include "..\\2DLIB\\TexManager.h"
//#include "..\\2DLIB\\FontManager.h"

#include "GUIButton.h"
#include "GUIVRoller.h"

class CGUIText : public CGUIButton
{
private:
	int miRim;//邊界寬度
	int miBG;//背景圖
	int miText;//文字內容
	bool mbReadOnly;
	//CFontManager *pCFontM;//文字管理器指標
	//CTexManager *pCTexM;//材質管理器指標
	bool mbShowVRoller;
	bool mbShowHRoller;
	CGUIVRoller *mpVRoller;//垂直捲軸
public:
	void HideVRoller(void);
	void ShowVRoller(void);
	bool GetVRoller(CGUIVRoller *pVR );

	void SetReadOnly(bool bOnOff);
	virtual LONG OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual LONG OnCHAR(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual LONG OnKEYDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam);
	virtual bool Display(void);
	//Init
	CGUIText();
	virtual ~CGUIText();
	virtual bool Init
				(JCGraphics *Grp //JCGrapgics指標
				,CFontManager *FM//文字管理器
				,CTexManager *TM//材質管理器
				,JCString Text//內文
				,JCString BG//背景圖檔名1
				,int x
				,int y
				,int Width
				,int Height
				,int iRim //邊界寬度
				,DWORD dwColorKey=0xffff00ff
				);
	

	virtual bool SetText(JCString text,int iSize,int color=0xffffffff);
	void Release(void);
};

#endif // !defined(AFX_GUITEXT_H__9BFC8623_2814_44C8_BC81_2E51696FE26F__INCLUDED_)
