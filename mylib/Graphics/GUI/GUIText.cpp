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
				(JCGraphics *Grp //JCGrapgics����
				,CFontManager *FM//��r�޲z��
				,CTexManager *TM//����޲z��
				,JCString Text//����
				,JCString BG//�I�����ɦW
				
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
		
		if((miText=pCFontM->Add ())==0)
		{
			sErrMsg="��r�޲z���w�Ĥw���A�άO��L�����~�C\0";
			return false;
		}
		
		SetText(Text,Height);		
		if(!BG.IsEmpty () )
			if((miBG=pCTexM->Add (BG.GetBuffer(),ColorKey ))==0)
			{
				sErrMsg="����޲z���w�Ĥw���A�άO��L�����~�ҥH�L�k���JBG�C\0";
				return false;
			}
		miRim=iRim;
		return true;
	}
	sErrMsg="JCGraphics ���п��~\0";
	return false;
	
	
	
}

bool CGUIText::Display()
{
	if(!CGUIButton::IsInit())
	{
		sErrMsg="��l�Ʃ|������\0";
		return false;
	}
	//���ܭI��
	//�b�ܤ�r
	if(!bIsShow)
		return true ;
	SD8TextureData *pTmp=pCTexM->GetTextureData (miBG);
	if(!pGrp->Draw(x,y,pTmp->pTex,Width,Height))
	{
		sErrMsg="JCGraphics�I��ø�s����\0";
		return false;
	}
	SFontFmt *pFFmt=pCFontM->GetFontFmt(miText);
	RECT rt;
	int iYOffset=0;
	
	//�e���b
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
		sErrMsg="��r��ܥ���\0";
		return false;
	}
	
	return true;
}

bool CGUIText::SetText(JCString text,int iSize, int color)
{
	//���ø�Ϧ�m
	if(!IsInit())
	{
		sErrMsg="��l�Ʃ|������\0";
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
	//�ˬd��r�O�_�W�X�d�� 
	//y : ���Φr��
	
	
	//pFFmt->dwFontColor =color;
	//�m��
	//pFFmt->iShowTextPosX =x+(Width/2)-(pFFmt->iFontSize/2)*(text.Length ()/2);
	//�m��
	//pFFmt->iShowTextPosX =x;
	//pFFmt->iShowTextPosY =y;
	//pFFmt->sText =text.GetBuffer () ;
	//pCFontM->SetText (iText,text,,0+y,color);
	pCFontM->SetText (miText,text,x,y,color);
	return true;
}

LONG CGUIText::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//��ƹ����U��
	//�ˬd�O�_�b�ϰ줺
	//���m�O���w�d�򤺨åB���i����r���A�åB�`�׬�0��
	if(IsRange(LOWORD(lparam),HIWORD(lparam) )&&mbReadOnly==false&&Depth==0)
	{
		mbActive=true;//���i��窱�A
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
			pFFmt->sText.DelChar ();//��@�r�� 
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

		//�]�wVRoller
		SFontFmt *pFFmt= pCFontM->GetFontFmt (miText);
		
		//���o�������
		
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
	//�n�R�����F��
	pCFontM->Delete (miText);
	pCTexM->Del (miBG);
	CGUIButton::Release ();
}
