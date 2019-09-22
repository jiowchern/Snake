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
				(JCGraphics *Grp //JCGrapgics����
				,CFontManager *FM//��r�޲z��
				,CTexManager *TM//����޲z��
				,JCString Text//����
				,JCString BGNormal//�I�����ɦW1
				,JCString BGOnMouse//�I�����ɦW2
				,JCString BGOnClick//�I�����ɦW3
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
			sErrMsg="��r�޲z�� ���п��~\0";
			return false;
		}
		if(TM==NULL)
		{
			sErrMsg="����޲z�� ���п��~\0";
			return false;
		}
		pCFontM=FM;
		pCTexM=TM;
		
		if((iText=pCFontM->Add ())==0)
		{
			sErrMsg="��r�޲z���w�Ĥw���A�άO��L�����~�C\0";
			return false;
		}
		
		SetText(Text,Height);		
		if(!BGNormal.IsEmpty () )
			if((iBG[0]=pCTexM->Add (BGNormal.GetBuffer(),ColorKey ))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JBGNormal�C\0";
				return false;
			}
		

		if(!BGOnMouse.IsEmpty () )
		{
			if((iBG[1]=pCTexM->Add (BGOnMouse.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JBGOnMouse�C\0";
				return false;
			}
		}
		else
			iBG[1]=iBG[0];

		if(!BGOnClick.IsEmpty () )
		{
			if((iBG[2]=pCTexM->Add (BGOnClick.GetBuffer(),ColorKey))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JBGOnClick�C\0";
				return false;
			}
		}
		else
			iBG[2]=iBG[0];
				
		return true;
	}
	sErrMsg="JCGraphics ���п��~\0";
	return false;
}

bool CGUIButton::SetText(JCString text,int iSize, int color)
{
	//���ø�Ϧ�m
	if(!IsInit())
	{
		sErrMsg="��l�Ʃ|������\0";
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
		sErrMsg="��l�Ʃ|������\0";
		return false;
	}
	//���ܭI��
	//�b�ܤ�r
	if(!bIsShow)
		return true ;
	SD8TextureData *pTmp=pCTexM->GetTextureData (iBG[iCurrentBG]);
	if(!pGrp->Draw(x,y,pTmp->pTex,Width,Height))
	{
		sErrMsg="JCGraphics�I��ø�s����\0";
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
	rt.bottom =Height+pFFmt->iShowTextPosY ;//��@��r
	if(!pCFontM->Draw (iText,rt,DT_CENTER |DT_SINGLELINE   ))
	{
		sErrMsg="��r��ܥ���\0";
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
	//�ˬd�O�_�b�ϰ줺
	
		
	if(IsRange(LOWORD(lparam),HIWORD(lparam)))
		iCurrentBG=DefONMOUSEMOVE;//�ƹ��b�W��
	else
		iCurrentBG=DefONMOUSENORMAL;//�ƹ����}�ɪ��ϧ�
	return 0;
}

LONG CGUIButton::OnLBUTTONUP(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//�ˬd�O�_�b�ϰ줺				
	if(IsRange(LOWORD(lparam),HIWORD(lparam)))
	{										
		iCurrentBG=DefONMOUSEMOVE;	
	}
	return 0;
}

LONG CGUIButton::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//�ˬd�O�_�b�ϰ줺
	

	if(IsRange(LOWORD(lparam),HIWORD(lparam)))
		iCurrentBG=DefONMOUSEDOWN;//�ƹ����U

	return 0;
}



void CGUIButton::Release()
{
	//�����bTextureManager�W������
	for(int i=0;i<3;i++)
	{
		if(iBG[i])
			pCTexM->Del (iBG[i]);
		iBG[i]=0;
	}

	//�����bFontManager���귽

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

// ���o���䪬�A
int CGUIButton::GetState(void)
{
	return iCurrentBG;
}
