// GUIText.cpp: implementation of the CGUIText class.
//
//////////////////////////////////////////////////////////////////////


#include "GUIText.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIText::CGUIText()
{
	mbReadOnly=false;
	miRim=0;
	Depth=0;
	mbShowVRoller=false;
	mbShowHRoller=false;
	mpVRoller=NULL;
}	

CGUIText::~CGUIText()
{

}
bool CGUIText::Init
				(JCGraphics *Grp //JCGrapgics指標
				,CFontManager *FM//文字管理器
				,CTexManager *TM//材質管理器
				,JCString Text//內文
				,JCString BG//背景圖檔名
				
				,int ix
				,int iy
				,int iWidth
				,int iHeight
				,int iRim
				
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
		
		if((miText=pCFontM->Add ())==0)
		{
			sErrMsg="文字管理器緩衝已滿，或是其他的錯誤。\0";
			return false;
		}
		
		SetText(Text,Height);		
		if(!BG.IsEmpty () )
			if((miBG=pCTexM->Add (BG.GetBuffer(),ColorKey ))==0)
			{
				sErrMsg="材質管理器緩衝已滿，或是其他的錯誤所以無法載入BG。\0";
				return false;
			}
		miRim=iRim;
		return true;
	}
	sErrMsg="JCGraphics 指標錯誤\0";
	return false;
	
	
	
}

bool CGUIText::Display()
{
	if(!CGUIButton::IsInit())
	{
		sErrMsg="初始化尚未完成\0";
		return false;
	}
	//先話背景
	//在話文字
	if(!bIsShow)
		return true ;
	SD8TextureData *pTmp=pCTexM->GetTextureData (miBG);
	if(!pGrp->Draw(x,y,pTmp->pTex,Width,Height))
	{
		sErrMsg="JCGraphics背景繪製失敗\0";
		return false;
	}
	SFontFmt *pFFmt=pCFontM->GetFontFmt(miText);
	RECT rt;
	int iYOffset=0;
	
	//畫捲軸
	if(mbShowVRoller&&mpVRoller!=NULL)
	{
		mpVRoller->Display();
		iYOffset=mpVRoller->GetPos();
	}
	rt.top =pFFmt->iShowTextPosY+miRim ;
	rt.left =pFFmt->iShowTextPosX+miRim ;
	rt.right =Width+pFFmt->iShowTextPosX -miRim;
	rt.bottom =Height+pFFmt->iShowTextPosY -miRim;
	if(pCFontM->Draw (miText,rt,DT_EXTERNALLEADING ))
	{
		sErrMsg="文字顯示失敗\0";
		return false;
	}
	
	return true;
}

bool CGUIText::SetText(JCString text,int iSize, int color)
{
	//顯示繪圖位置
	if(!IsInit())
	{
		sErrMsg="初始化尚未完成\0";
		return false;
	}
	//pCFontM->GetFontFmt (miText);
	
	/*if(iSize>Height)
	{
		pFFmt->iFontSize=Height; 
		iSize=Height;
	}
	else
		pFFmt->iFontSize=iSize;*/
	//檢查文字是否超出範圍 
	//y : 切割字串
	
	
	//pFFmt->dwFontColor =color;
	//置中
	//pFFmt->iShowTextPosX =x+(Width/2)-(pFFmt->iFontSize/2)*(text.Length ()/2);
	//置左
	//pFFmt->iShowTextPosX =x;
	//pFFmt->iShowTextPosY =y;
	//pFFmt->sText =text.GetBuffer () ;
	//pCFontM->SetText (iText,text,,0+y,color);
	pCFontM->SetText (miText,text,x,y,color);
	return true;
}

LONG CGUIText::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//當滑鼠按下時
	//檢查是否在區域內
	//當位置是指定範圍內並且為可更改文字狀態並且深度為0時
	if(IsRange(LOWORD(lparam),HIWORD(lparam) )&&mbReadOnly==false&&Depth==0)
	{
		mbActive=true;//為可更改狀態
		return 0;
	}
	mbActive=false;
	return 0;
}
LONG CGUIText::OnKEYDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	if(mbActive)
	{
		if(wparam==VK_BACK)
		{
			SFontFmt *pFFmt= pCFontM->GetFontFmt (miText);
			pFFmt->sText.DelChar ();//減掉一字元 
			if(mpVRoller!=NULL)
				mpVRoller->Set (x+Width-miRim,y,miRim , Height-miRim,((pFFmt->sText.GetCharAmount(13)+1)*pFFmt->iFontSize),1, Height-miRim*3  );
			
		}
	}
	return 0;
}
LONG CGUIText::OnCHAR(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	if(mbActive)
	{
		//char *sChar;
		//sChar=(char*)&wparam;
		if(wparam==VK_BACK)
			return 0;
		SFontFmt *pFFmt= pCFontM->GetFontFmt (miText);
		pFFmt->sText+=(char*)&wparam;
		if(VK_RETURN&&mpVRoller!=NULL)
		{
			mpVRoller->Set (x+Width-miRim,y,miRim , Height-miRim,((pFFmt->sText.GetCharAmount(13)+1)*pFFmt->iFontSize),1, Height-miRim*3  );
			
		}
			
	}
	return 0;
}

void CGUIText::SetReadOnly(bool bOnOff)
{
	mbReadOnly=bOnOff;
}



bool CGUIText::GetVRoller(CGUIVRoller *pVR)
{
	if(pVR)
	{
		mpVRoller=pVR;

		//設定VRoller
		SFontFmt *pFFmt= pCFontM->GetFontFmt (miText);
		
		//取得完整長度
		
		mpVRoller->Set (x+Width-miRim,y,miRim , Height-miRim,((pFFmt->sText.GetCharAmount(13)+1)*pFFmt->iFontSize),1, Height-miRim*3  );
		return true;
	}
	return false;
}

void CGUIText::ShowVRoller()
{
	mbShowVRoller=true;
}

void CGUIText::HideVRoller()
{
	mbShowVRoller=false;
}
void CGUIText::Release ()
{
	//要刪除的東西
	pCFontM->Delete (miText);
	pCTexM->Del (miBG);
	CGUIButton::Release ();
}
