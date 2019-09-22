// GUIBase.h: interface for the CGUIBase class.
//
//////////////////////////////////////////////////////////////////////
/*

  �򥻪�Gui���O


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
//�T����Ӫ�


class CGUIBase  
{
private:
	int iColor;
protected:
	inline bool IsInit(void);
	//�ݩ�
	int x;int y;//�����mx,y
	int Width;int Height;//�� �e 
	
	DWORD ColorKey;
	JCGraphics *pGrp;
	char *sErrMsg;
	
	bool bIsShow;
	bool mbActive;
	CFontManager *pCFontM;//��r�޲z������
	CTexManager *pCTexM;//����޲z������
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
	//��k
	virtual bool Display(void);
	bool Hide(void);
	bool Show(void);
	

	//�@����
	virtual bool Init(JCGraphics *Grp,DWORD dwColorKey);
	virtual char* GetErrMessage(void)
	{
		return sErrMsg;
	};
	CGUIBase();
	virtual ~CGUIBase();
	int Depth;//�`��
	//int miRim;
};



	
	



#endif // !defined(AFX_GUIBASE_H__45D8981A_A9F5_4B1B_88D6_209B17B50CA0__INCLUDED_)
