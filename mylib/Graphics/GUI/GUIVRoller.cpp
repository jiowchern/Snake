// GUIVRoller.cpp: implementation of the CGUIVRoller class.
//
//////////////////////////////////////////////////////////////////////


#include "GUIVRoller.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIVRoller::CGUIVRoller()
{
	miNowPosY=0;

}

CGUIVRoller::~CGUIVRoller()
{

}

bool CGUIVRoller::Display()
{
	if(CGUIRoller::IsInit ()&&bIsShow )
	{
		//畫出垂直捲軸
		SD8TextureData *pTmp;
		//話底
		pTmp=pCTexM->GetTextureData (miBody);
		
		pGrp->Draw(x,y,pTmp->pTex,miRimWidth,miLength); 
		//畫頭
		pTmp=pCTexM->GetTextureData (miBack);
	
		pGrp->Draw(x,y,pTmp->pTex,miRimWidth,miRimWidth); 

		//畫底
		pTmp=pCTexM->GetTextureData (miNext);
		pGrp->Draw(x,y+miLength-miRimWidth,pTmp->pTex,miRimWidth,miRimWidth); 

		//畫滾軸
		pTmp=pCTexM->GetTextureData (miRoller);
		
		float fPercent=(float)miPos/miMax;
		float fRollerLen=(float)miRegion/miMax;
		fRollerLen*=(miLength-miRimWidth*2);
		int iSPos=(miLength-miRimWidth*2/*頭委寬度*/-fRollerLen/*區間寬度*/)*fPercent;

		pGrp->Draw(x,y+miRimWidth/*back的寬度*/+(iSPos),pTmp->pTex,miRimWidth,fRollerLen); 
			
		
		return true;
	}
	return false;
}

LONG CGUIVRoller::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//當滑鼠按下十判斷是否有在範圍內??

	

	//no:直接跳出
	int xPos=LOWORD(lparam);
	int yPos=HIWORD(lparam);

	if(IsRange(xPos,yPos) )
	{//yes:繼續判段所案位置
	
		//是否在區間???
		float fPercent=(float)miPos/miMax;
		float fRollerLen=(float)miRegion/miMax*(miLength-miRimWidth*2);
		
		int iSPos=(miLength-miRimWidth*2/*頭委寬度*/-fRollerLen/*區間寬度*/)*fPercent;

		if(xPos>=x && x+miRimWidth>=xPos && yPos>=y+iSPos && y+iSPos+fRollerLen>=yPos)
		{
			//捲軸
			mbRollerPress=true;
			miNowPosY=yPos;

		}else if(xPos>=x && x+miRimWidth>=xPos && yPos>=y && y+miRimWidth>=yPos )
		{
			//在Back李
			//刻度跳要
		}
		else if(xPos>=x && x+miRimWidth>=xPos && yPos>=y+miLength-miRimWidth-miRimWidth && y+miLength-miRimWidth>=yPos)//Next
		{
			//Next
			//刻度跳要
		}else
		{
			//底限
			
			//執行換頁動作
		}
		
		
	}
	
	return 0;
}

LONG CGUIVRoller::OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	mbRollerPress=false;
	return 0;
}

LONG CGUIVRoller::OnMOUSEMOVE(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	if(mbRollerPress)
	{
		//將實際位置轉成值
		float fRollerLen=(float)miRegion/miMax*(miLength-miRimWidth*2);
//		fRollerLen*=;
		//定為最先的pos  ... pos=0的位置
		int ifYPos=y+miRimWidth;
		//定義最後的pos ... pos=miMax
		int ilYPos=(miLength-miRimWidth*2-fRollerLen);
		int yPos=HIWORD(lparam)-ifYPos;
		miPos=((float)yPos/ilYPos)*miMax;
		
		miNowPosY=HIWORD(lparam);

		if(miPos<miMin)
			miPos=miMin;
		if(miPos>miMax)
			miPos=miMax;
	}
	return 0;
}
