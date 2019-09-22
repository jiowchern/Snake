// GUIBase.cpp: implementation of the CGUIBase class.
//
//////////////////////////////////////////////////////////////////////

#include "GUIBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//訊息配置表


CGUIBase::CGUIBase()
{
	pGrp=NULL;
	Depth=0;//最底層,用來決定顯示的層次
	Height=100;
	Width=100;
	x=0;
	y=0;
	bIsShow=false;
	
	iColor=0xffffffff;
	
}

CGUIBase::~CGUIBase()
{
	
}

bool CGUIBase::Init(JCGraphics *Grp,DWORD dwColorKey)
{
	if(Grp==NULL)
	{
		sErrMsg="初始化失敗，JCGraphics為NULL\0";
		return false;
	}

	ColorKey=dwColorKey;
	pGrp=Grp;
	
	return true;
}

bool CGUIBase::Show()
{
	if(IsInit())
	{
		
		bIsShow=true;
		return true;
	}
	return false;
}

inline bool CGUIBase::IsInit()
{
	if(pGrp==NULL)
		return false;
	return true;
}

bool CGUIBase::Hide()
{
	if(IsInit())
	{
		bIsShow=false;
		return true;
	}
	return false;
}

bool CGUIBase::Display()
{
	if(IsInit()&&bIsShow)
		pGrp->DrawRect(x,y,Width,Height,iColor);
	return true;
}

bool CGUIBase::GetWinMessage(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp)
{
		
	if(IsInit()&&bIsShow)
	{
		switch  (Msg)
			{
			case WM_LBUTTONUP:
				OnLBUTTONUP(hWnd,Msg,wp,lp);
				break;
			case WM_LBUTTONDOWN:
				OnLBUTTONDOWN(hWnd,Msg,wp,lp);
				break;
			case WM_MOUSEMOVE:
				OnMOUSEMOVE(hWnd,Msg,wp,lp);
				break;
			case WM_CHAR:
				OnCHAR(hWnd,Msg,wp,lp);
				break;
			case WM_KEYDOWN:
				OnKEYDOWN(hWnd,Msg,wp,lp);
				break;
			}
	
		return true;
	}
	return false;
}
LONG CGUIBase::OnKEYDOWN(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam)
{
	return 0;
}
LONG CGUIBase::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	return 0;
}
LONG CGUIBase::OnMOUSEMOVE(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	return 0;
}
LONG CGUIBase::OnCHAR(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam)
{
	return 0;
}
LONG CGUIBase::OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//檢查是否在區域內
	int xPos = LOWORD(lparam);
	int yPos = HIWORD(lparam);

	if(x<xPos &&y<yPos  &&Width+x>xPos &&Height+y>yPos )
	{
		if(iColor==0xffffffff)
			iColor=0xff00ff00;
		else
			iColor=0xffffffff;
	}

	return 0;
}



bool CGUIBase::IsRange(int xPos,int yPos)
{
	//檢查是否在區域內
	//int xPos = LOWORD(lparam);
	//int yPos = HIWORD(lparam);
	
	if(x<xPos &&y<yPos  &&(Width+x)>xPos && (y+Height)>yPos )
	{
		//pGrp->Begin ();
		//pGrp->DrawRect (xPos,yPos,1,1,0xff000000);
		//pGrp->Render ();
		return true;
	}
	//pGrp->Begin ();
	//pGrp->DrawRect (x,y,Width,Height,0x7f000000);
	//pGrp->Render ();
	return false;
}

void CGUIBase::Release()
{
	pGrp=NULL;
}

void CGUIBase::Location(int ix, int iy)
{
	x=ix;
	y=iy;
	Display();
}

void CGUIBase::Resize(int iWidth, int iHeight)
{
	Width=iWidth;
	Height=iHeight;
	Display();
}
