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
	int miRim;//��ɼe��
	int miBG;//�I����
	int miText;//��r���e
	bool mbReadOnly;
	//CFontManager *pCFontM;//��r�޲z������
	//CTexManager *pCTexM;//����޲z������
	bool mbShowVRoller;
	bool mbShowHRoller;
	CGUIVRoller *mpVRoller;//�������b
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
				(JCGraphics *Grp //JCGrapgics����
				,CFontManager *FM//��r�޲z��
				,CTexManager *TM//����޲z��
				,JCString Text//����
				,JCString BG//�I�����ɦW1
				,int x
				,int y
				,int Width
				,int Height
				,int iRim //��ɼe��
				,DWORD dwColorKey=0xffff00ff
				);
	

	virtual bool SetText(JCString text,int iSize,int color=0xffffffff);
	void Release(void);
};

#endif // !defined(AFX_GUITEXT_H__9BFC8623_2814_44C8_BC81_2E51696FE26F__INCLUDED_)
