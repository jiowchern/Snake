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
		//�e�X�������b
		SD8TextureData *pTmp;
		//�ܩ�
		pTmp=pCTexM->GetTextureData (miBody);
		
		pGrp->Draw(x,y,pTmp->pTex,miRimWidth,miLength); 
		//�e�Y
		pTmp=pCTexM->GetTextureData (miBack);
	
		pGrp->Draw(x,y,pTmp->pTex,miRimWidth,miRimWidth); 

		//�e��
		pTmp=pCTexM->GetTextureData (miNext);
		pGrp->Draw(x,y+miLength-miRimWidth,pTmp->pTex,miRimWidth,miRimWidth); 

		//�e�u�b
		pTmp=pCTexM->GetTextureData (miRoller);
		
		float fPercent=(float)miPos/miMax;
		float fRollerLen=(float)miRegion/miMax;
		fRollerLen*=(miLength-miRimWidth*2);
		int iSPos=(miLength-miRimWidth*2/*�Y�e�e��*/-fRollerLen/*�϶��e��*/)*fPercent;

		pGrp->Draw(x,y+miRimWidth/*back���e��*/+(iSPos),pTmp->pTex,miRimWidth,fRollerLen); 
			
		
		return true;
	}
	return false;
}

LONG CGUIVRoller::OnLBUTTONDOWN(HWND hWnd, UINT Msg, WPARAM wparam, LPARAM lparam)
{
	//��ƹ����U�Q�P�_�O�_���b�d��??

	

	//no:�������X
	int xPos=LOWORD(lparam);
	int yPos=HIWORD(lparam);

	if(IsRange(xPos,yPos) )
	{//yes:�~��P�q�Үצ�m
	
		//�O�_�b�϶�???
		float fPercent=(float)miPos/miMax;
		float fRollerLen=(float)miRegion/miMax*(miLength-miRimWidth*2);
		
		int iSPos=(miLength-miRimWidth*2/*�Y�e�e��*/-fRollerLen/*�϶��e��*/)*fPercent;

		if(xPos>=x && x+miRimWidth>=xPos && yPos>=y+iSPos && y+iSPos+fRollerLen>=yPos)
		{
			//���b
			mbRollerPress=true;
			miNowPosY=yPos;

		}else if(xPos>=x && x+miRimWidth>=xPos && yPos>=y && y+miRimWidth>=yPos )
		{
			//�bBack��
			//��׸��n
		}
		else if(xPos>=x && x+miRimWidth>=xPos && yPos>=y+miLength-miRimWidth-miRimWidth && y+miLength-miRimWidth>=yPos)//Next
		{
			//Next
			//��׸��n
		}else
		{
			//����
			
			//���洫���ʧ@
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
		//�N��ڦ�m�ন��
		float fRollerLen=(float)miRegion/miMax*(miLength-miRimWidth*2);
//		fRollerLen*=;
		//�w���̥���pos  ... pos=0����m
		int ifYPos=y+miRimWidth;
		//�w�q�̫᪺pos ... pos=miMax
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
