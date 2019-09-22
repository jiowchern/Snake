// GUIRoller.cpp: implementation of the CGUIRoller class.
//
//////////////////////////////////////////////////////////////////////


#include "GUIRoller.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIRoller::CGUIRoller()
{
	 miBack=0;//
	 miNext=0;//
	 miBody=0;//
	 miRoller=0;//
	
	 
	 miMin=0;//�̩��U����
	 miMax=0;//�̰���
	 miPos=0;//�ثe����m
	 mbRollerPress=false;
	
	 miRimWidth=0;//�e��
}

CGUIRoller::~CGUIRoller()
{

}
bool CGUIRoller::Init(JCGraphics *Grp,CTexManager *TM,JCString sHead,JCString sUnder,JCString sBody,JCString sRoller,DWORD dwColorKey)
{
	if(CGUIBase::Init (Grp,dwColorKey))
	{
		x=0;
		y=0;
		Width=0;
		Height=0;

		
		if(TM==NULL)
		{
			sErrMsg="����޲z�� ���п��~\0";
			return false;
		}
		
		pCTexM=TM;
		
		
		if(!sHead.IsEmpty () )
			if((miBack=pCTexM->Add (sHead.GetBuffer(),ColorKey ))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JsHead�C\0";
				return false;
			}
		

		if(!sUnder.IsEmpty () )
		{
			if((miNext=pCTexM->Add (sUnder.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JsUnder�C\0";
				return false;
			}
		}
		

		if(!sBody.IsEmpty () )
		{
			if((miBody=pCTexM->Add (sBody.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JsBody�C\0";
				return false;
			}
		}
		if(!sRoller.IsEmpty () )
		{
			if((miRoller=pCTexM->Add (sRoller.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JsRoller�C\0";
				return false;
			}
		}
				
		return true;
	}
	sErrMsg="JCGraphics ���п��~\0";
	return false;
}


//�]�w��l��� 
bool CGUIRoller::Set(int X, int Y, int RimWidth,int Length, int Max, int Min,int Region)
{
	if(!IsInit())
	{
	
		sErrMsg="Roller��l�ƥ���\0";	
			
		return false;
	}
	x=X;
	y=Y;
	miRimWidth=RimWidth;
	
	miPos=Min;
	miMin=Min;
	miLength=Length;
	if(Region>Max)
		miRegion=Max;
	else
		miRegion=Region;
	Width=RimWidth;
	Height=Length;
	miMax=Max;
	return true;
}

bool CGUIRoller::IsInit()
{
	if(CGUIBase::IsInit ())
		if(pCTexM!=NULL&&miBack&&miNext&&miBody&&miRoller)
			return true;
	return false;
}

bool CGUIRoller::Display()
{
	if(!IsInit())
	{
		sErrMsg="Roller��l�Ʃ|������\0";
		return false;
	}
	
	if(bIsShow )
	{
		/*SD8TextureData *pTmp;
		
		int iW,iH;
		int iRim;
		if(miDirect==0)//�e����
		{
			iW=miRimWidth;
			iH=miLength;
			
		}
		else
		{
			iW=miLength;
			iH=miRimWidth;
			
		}
		iRim=miRimWidth;
		//�ܩ�
		pTmp=pCTexM->GetTextureData (miBody);
		if(miDirect==0)
			pGrp->Draw(x,y,pTmp->pTex,iW,iH); 
		//�e�Y
		pTmp=pCTexM->GetTextureData (miBack);
		if(miDirect==0)
			pGrp->Draw(x,y,pTmp->pTex,iRim,iRim); 

		//�e��
		pTmp=pCTexM->GetTextureData (miNext);
		if(miDirect==0)
			pGrp->Draw(x,y+miLength-iRim,pTmp->pTex,iRim,iRim); 

		//�e�u�b
		pTmp=pCTexM->GetTextureData (miRoller);
		if(miDirect==0)
		{
			float fPercent=(float)miPos/miMax;
			float fRollerLen=(float)miRegion/miMax;
			fRollerLen*=(miLength-iRim*2);
			int iSPos=(miLength-iRim*2-fRollerLen)*fPercent;
			pGrp->Draw(x,y+iRim+(iSPos),pTmp->pTex,iW,fRollerLen); 
			
		}*/
		
		return true;	
	}
	return false;
}

LONG CGUIRoller::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//��X�ثe�����b�ϰ�~
	/*float fPercent=(float)miPos/miMax;
	float fRollerLen=(float)miRegion/miMax;
	fRollerLen*=(miLength-miRimWidth*2);
	int iSPos=(miLength-miRimWidth*2-fRollerLen)*fPercent;
	
	int iPosX,iPosY;

	RECT rtRoller;
	rtRoller.top =y+iSPos;
	rtRoller.left =x;
	rtRoller.right =x+miRimWidth;
	rtRoller.bottom =rtRoller.top+fRollerLen;
	
	iPosX=LOWORD(lparam);
	iPosY=HIWORD(lparam);
	pGrp->DrawRect (rtRoller.left,rtRoller.top,miRimWidth,fRollerLen,0xffff00ff);
	if(iPosX >= rtRoller.left && rtRoller.right >= iPosX
	&&
	   iPosY >= rtRoller.top  && rtRoller.bottom>= iPosY
		)
	{
		//�b�ϰ��
		mbRollerPress=true;
		miNowMouseY=iPosY;
	}
	*/
	return 0;
}

LONG CGUIRoller::OnMOUSEMOVE(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	/*if(mbRollerPress)
	{
		SetPos(HIWORD(lparam)-miNowMouseY);
	}*/
	return 0;
}

bool CGUIRoller::SetPos(int iVal)
{
	miPos+=iVal;
	if(miPos<miMin)
		miPos=miMin;
	if(miPos>miMax)
		miPos=miMax;
	return true;
}

LONG CGUIRoller::OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//mbRollerPress=false;
	return 0;
}

int CGUIRoller::GetPos()
{
	return miPos;
}
