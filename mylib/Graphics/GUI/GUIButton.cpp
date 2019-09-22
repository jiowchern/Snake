// GUIButton.cpp: implementation of the CGUIButton class.
//
//////////////////////////////////////////////////////////////////////

#include "GUIButton.h"
#include ".\guibutton.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIButton::CGUIButton()
{
	iText=0;
	iBG[0]=0;
	iBG[1]=0;
	iBG[2]=0;
	pCFontM=NULL;
	pCTexM=NULL;
	iCurrentBG=0;
	
}

CGUIButton::~CGUIButton()
{

}

bool CGUIButton::Init
				(JCGraphics *Grp //JCGrapgics指標
				,CFontManager *FM//文字管理器
				,CTexManager *TM//材質管理器
				,JCString Text//內文
				,JCString BGNormal//背景圖檔名1
				,JCString BGOnMouse//背景圖檔名2
				,JCString BGOnClick//背景圖檔名3
				,int ix
				,int iy
				,int iWidth
				,int iHeight
				,DWORD dwColorKey
				)
{
	if(CGUIBase::Init (Grp,dwColorKey))
	{
		x=ix;
		y=iy;
		Width=iWidth;
		Height=iHeight;

		if(FM==NULL)
		{
			sErrMsg="文字管理器 指標錯誤\0";
			return false;
		}
		if(TM==NULL)
		{
			sErrMsg="材質管理器 指標錯誤\0";
			return false;
		}
		pCFontM=FM;
		pCTexM=TM;
		
		if((iText=pCFontM->Add ())==0)
		{
			sErrMsg="文字管理器緩衝已滿，或是其他的錯誤。\0";
			return false;
		}
		
		SetText(Text,Height);		
		if(!BGNormal.IsEmpty () )
			if((iBG[0]=pCTexM->Add (BGNormal.GetBuffer(),ColorKey ))==0)
			{
				sErrMsg="材質管理器緩衝已滿，或是其他的錯誤所以無法載入BGNormal。\0";
				return false;
			}
		

		if(!BGOnMouse.IsEmpty () )
		{
			if((iBG[1]=pCTexM->Add (BGOnMouse.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="材質管理器緩衝已滿，或是其他的錯誤所以無法載入BGOnMouse。\0";
				return false;
			}
		}
		else
			iBG[1]=iBG[0];

		if(!BGOnClick.IsEmpty () )
		{
			if((iBG[2]=pCTexM->Add (BGOnClick.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="材質管理器緩衝已滿，或是其他的錯誤所以無法載入BGOnClick。\0";
				return false;
			}
		}
		else
			iBG[2]=iBG[0];
				
		return true;
	}
	sErrMsg="JCGraphics 指標錯誤\0";
	return false;
}

bool CGUIButton::SetText(JCString text,int iSize, int color)
{
	//顯示繪圖位置
	if(!IsInit())
	{
		sErrMsg="初始化尚未完成\0";
		return false;
	}
	SFontFmt *pFFmt= pCFontM->GetFontFmt (iText);
	if(iSize>Height)
	{
		pFFmt->iFontSize=Height; 
		iSize=Height;
	}
	else
		pFFmt->iFontSize=iSize;
	
	

	pFFmt->dwFontColor =color;
	pFFmt->iShowTextPosX =x;
	pFFmt->iShowTextPosY =y;
	pFFmt->sText =text;
	//pCFontM->SetText (iText,text,,0+y,color);
	return true;
}



inline bool CGUIButton::IsInit()
{
	if(CGUIBase::IsInit ()&&pCTexM!=NULL)
		return true;
	return false;
}

bool CGUIButton::Display()
{
	if(!IsInit())
	{
		sErrMsg="初始化尚未完成\0";
		return false;
	}
	//先話背景
	//在話文字
	if(!bIsShow)
		return true ;
	SD8TextureData *pTmp=pCTexM->GetTextureData (iBG[iCurrentBG]);
	if(!pGrp->Draw(x,y,pTmp->pTex,Width,Height))
	{
		sErrMsg="JCGraphics背景繪製失敗\0";
		return false;
	}
//+(Width/2)-(pFFmt->iFontSize/2)*(text.Length ()/2)
	SFontFmt *pFFmt=pCFontM->GetFontFmt(iText);
	//int iWOffset=(Width/2)-(pFFmt->iFontSize/2)*(pFFmt->sText.Length ()/2);
	//int iHOffset=(Height/2)-(pFFmt->iFontSize);
	//if(iWOffset<0)
	//	iWOffset=0;
	//if(iHOffset<0)
	//	iHOffset=0;
	RECT rt;
	rt.top =pFFmt->iShowTextPosY ;//+iHOffset;
	rt.left =pFFmt->iShowTextPosX;//+iWOffset;
	rt.right =Width+pFFmt->iShowTextPosX ;
	rt.bottom =Height+pFFmt->iShowTextPosY ;//減掉一行字
	if(!pCFontM->Draw (iText,rt,DT_CENTER |DT_SINGLELINE   ))
	{
		sErrMsg="文字顯示失敗\0";
		return false;
	}

	return true;
}
/*bool CGUIButton::GetWinMessage(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp)
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
			}
	
		return true;
	}
	return false;
}*/
/*
#define DefONMOUSENORMAL 0
#define DefONMOUSEMOVE 1
#define DefONMOUSEDOWN 2
*/
LONG CGUIButton::OnMOUSEMOVE(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//檢查是否在區域內
	
		
	if(IsRange(LOWORD(lparam),HIWORD(lparam)))
		iCurrentBG=DefONMOUSEMOVE;//滑鼠在上面
	else
		iCurrentBG=DefONMOUSENORMAL;//滑鼠移開時的圖形
	return 0;
}

LONG CGUIButton::OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//檢查是否在區域內				
	if(IsRange(LOWORD(lparam),HIWORD(lparam)))
	{										
		iCurrentBG=DefONMOUSEMOVE;	
	}
	return 0;
}

LONG CGUIButton::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//檢查是否在區域內
	

	if(IsRange(LOWORD(lparam),HIWORD(lparam)))
		iCurrentBG=DefONMOUSEDOWN;//滑鼠按下

	return 0;
}



void CGUIButton::Release()
{
	//移除在TextureManager上的材質
	for(int i=0;i<3;i++)
	{
		if(iBG[i])
			pCTexM->Del (iBG[i]);
		iBG[i]=0;
	}

	//移除在FontManager的資源

	if(iText)
		pCFontM->Delete (iText);
	iText=0;	
	CGUIBase::Release ();
}



void CGUIButton::Resize(int iWidth, int iHeight)
{
	Width=iWidth;
	Height=iHeight;

	ResetText();
}

void CGUIButton::ResetText()
{
	SFontFmt *pFFmt= pCFontM->GetFontFmt (iText);
	SetText(pFFmt->sText ,pFFmt->iFontSize ,pFFmt->dwFontColor );
}

void CGUIButton::Location(int ix, int iy)
{
	x=ix;
	y=iy;

	ResetText();
}

// 取得按鍵狀態
int CGUIButton::GetState(void)
{
	return iCurrentBG;
}
