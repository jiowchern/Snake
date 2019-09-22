// GUIButton.h: interface for the CGUIButton class.
//
//////////////////////////////////////////////////////////////////////
/*
	�������s
*/
#if !defined(AFX_GUIBUTTON_H__9DBA9552_0104_4CC7_A345_E1B87747D46A__INCLUDED_)
#define AFX_GUIBUTTON_H__9DBA9552_0104_4CC7_A345_E1B87747D46A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUIBase.h"

//�ƹ����A
#define DefONMOUSENORMAL 0
#define DefONMOUSEMOVE 1
#define DefONMOUSEDOWN 2
class CGUIButton : public CGUIBase  
{
private:
	

	int iText;//��r���e...�s��
	
	int iBG[3];//�I����...���`�ɭ�,�ƹ��b�W���ɭ�,��ƹ����U�ɭ�
	int iCurrentBG;//�ثe��ܪ��ϧ�

	
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
	//��k
	virtual bool Display(void);
	
	

	//�@����

	//��l��
	virtual bool Init
				(JCGraphics *Grp //JCGrapgics����
				,CFontManager *FM//��r�޲z��
				,CTexManager *TM//����޲z��
				,JCString Text//����
				,JCString BGNormal//�I�����ɦW1
				,JCString BGOnMouse//�I�����ɦW2
				,JCString BGOnClick//�I�����ɦW3
				,int x
				,int y
				,int Width
				,int Height
				,DWORD dwColorKey=0xffff00ff
				);
	// ���o���䪬�A
	int GetState(void);
};

#endif // !defined(AFX_GUIBUTTON_H__9DBA9552_0104_4CC7_A345_E1B87747D46A__INCLUDED_)
