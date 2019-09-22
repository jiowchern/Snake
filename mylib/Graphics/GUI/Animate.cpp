
#include ".\animate.h"
void CAnimate::Release(void)
{
	//�R���ʵe	
	int i;
	for(i=0;i<iAmount;i++)
		Del(i);
	mpSAnimate=NULL;
	iAmount=0;
	iCurrent=0;
	CGUIBase::Release ();
}
bool CAnimate::Display ()
{
	//��X�ثe�n��ܪ��ʵe
	if(!IsInit())
	{
		sErrMsg="��l�Ʃ|������\0";
		return false;
	}
	//���ܭI��
	//�b�ܤ�r
	if(!bIsShow)
		return true ;
	
	if(mpSAnimate[iCurrent].bUse )
	{
		
		pGrp->Draw (x
				,y
				,pCTexM->GetTextureData ( mpSAnimate[iCurrent].piImg[mpSAnimate[iCurrent].iCurrentImg])
				,Width
				,Height
				);
		
		if(CTimer.IsTimeUp (NULL))
		{		
			mpSAnimate[iCurrent].iCurrentImg++;
			if(mpSAnimate[iCurrent].iCurrentImg>=mpSAnimate[iCurrent].iImgAmount )
				mpSAnimate[iCurrent].iCurrentImg=0;

			this->Width =mpSAnimate[iCurrent].iWidth ;
			Height=mpSAnimate[iCurrent].iHeight ;
			CTimer.SetTimer ( mpSAnimate[iCurrent].piTimeLength[mpSAnimate[iCurrent].iCurrentImg]  );
			
			CTimer.Begin ();
		}
		return true;
	}
}
CAnimate::CAnimate(void)
{
	mpSAnimate=NULL;
	iAmount=0;
	iCurrent=0;
	CTimer.SetTimer (1);
	CTimer.Begin ();

}

CAnimate::~CAnimate(void)
{
}

bool CAnimate::Init(
				JCGraphics *Grp
				,CTexManager *TM	//����޲z��		
				,int Amount
			 )
{
	if(!this->IsInit ())
	{
		if(Grp==NULL)
		{
			CGUIBase::sErrMsg ="JCGraphics is NULL\0";
			return false;
		}
		if(TM==NULL)
		{
			CGUIBase::sErrMsg ="CFontManager is NULL\0";
			return false;
		}
		

		pGrp=Grp;
		pCTexM =TM;
		mpSAnimate=new SAnimate[Amount];
		for (int i=0;i<Amount;i++)
			memset(&mpSAnimate[i],0,sizeof(SAnimate) );
		this->iAmount =Amount;
		return true;

	}
	return false;
}

bool CAnimate::IsInit()
{
	if(CGUIBase::IsInit ()&&pCTexM!=NULL)
	{
		return true;
	}
	return false;
}
//��J1:�ɮצW�� ��J2:�z���� ��X:�p�G�Ǧ^0�N����,�_�h�O�Ǧ^�s��
int CAnimate::Add (char *sFN,DWORD dwColorKey)
{
	if(this->IsInit ())
	{
		//�ˬd�S�Ψ쪺�Ŷ�
		int i;
		for(i=0;i<this->iAmount ;i++)
		{
			if(mpSAnimate[i].bUse==false )
			{
				//�S�Q�ϥ�
				//�إ�
				//Ū�J�ɮ�
				
				CFileAccress CF;
				if(CF.Open (sFN,false))
				{	
					JCString sTmp;
					sTmp=sFN;
					JCString sPath="";
					int iSIdx=1;
					int iEIdx=1;
					while(iEIdx=sTmp.GetPosToChar ('/',iSIdx ))
					{
						sPath+=sTmp.GetString(iSIdx,iEIdx-iSIdx).GetBuffer()   ;
						iSIdx=iEIdx;
					}
					
					mpSAnimate[i].dwColorKey=dwColorKey;
					//�ɮפw�}��
					
					//Ū�J�Ĥ@����Ƴ]�wWidth
					//��M,
					//����e
					
					
					sTmp=CF.GetStringToChar(',') ;
					
					mpSAnimate[i].iWidth =sTmp.ToInt ();
										
					//�����
			
					sTmp=CF.GetStringToChar(',') ;
					
					mpSAnimate[i].iHeight=sTmp.ToInt ();
	

					//�ϧμƶq
					sTmp=CF.GetStringToChar(',');
					mpSAnimate[i].iImgAmount =sTmp.ToInt ();
					

					//������ɨåB�إ�
					mpSAnimate[i].piImg=new int[mpSAnimate->iImgAmount];
					mpSAnimate[i].piTimeLength =new int[mpSAnimate->iImgAmount];
					int i2;
					for(i2=0;i2<mpSAnimate[i].iImgAmount;i2++ )
					{
						sTmp=sPath.GetBuffer ();
						sTmp+=CF.GetStringToChar (',').GetBuffer() ;
						sTmp.DelLength ();
						
						
						mpSAnimate[i].piImg[i2]=pCTexM->Add (sTmp.GetBuffer (),dwColorKey );

						sTmp=CF.GetStringToChar (',');
						sTmp.DelLength ();
						mpSAnimate[i].piTimeLength[i2]=sTmp.ToInt ();
					}
					
					//�����ɦW
					mpSAnimate[i].psFileName =new JCString ();
					(*mpSAnimate[i].psFileName)=sFN;
					mpSAnimate[i].psFileName->ToLower ();
					//����
					mpSAnimate[i].bUse =true;
					return i+1;
				}
				else
				{
					
					sErrMsg="�䤣���ɮצW��\0" ;
					return 0;
				}
				
			}
		}

		sErrMsg="�S���Ŷ�\0" ;
		return 0;
	}
	sErrMsg="�S����l��\0" ;
	return 0;
}

bool CAnimate::Del (int iNumber)
{
	if(iNumber<=0)
		return false;//��J�����X���~
	
	iNumber-=1;
	if(this->mpSAnimate [iNumber].bUse  )
	{
		this->mpSAnimate[iNumber].psFileName ->ClearBuf ();
		delete this->mpSAnimate[iNumber].psFileName;
		delete [] this->mpSAnimate[iNumber].piTimeLength ;
		delete [] this->mpSAnimate[iNumber].piImg ;
		memset(&mpSAnimate[iNumber],0,sizeof(SAnimate));
		return true;
	}
	return false;
}

int CAnimate::NameToNum(char *sFileName)
{
	int iIdx;
	JCString sTmp;
	sTmp=sFileName;
	sTmp.ToLower ();
	for(iIdx=0;iIdx<iAmount;iIdx++)
	{
		if(mpSAnimate[iIdx].bUse&&mpSAnimate[iIdx].psFileName->FullCompared(sTmp.GetBuffer ()))
		{			
			return iIdx+1;
		}
	}
	return 0;
}

//�ˬd��J�Ӹ��X�O�_�����T���d��
bool CAnimate::ChkNumber(int iNum)

{
	iNum-=1;
	if(iNum<iAmount&&iNum>=0)
		return true;
	return false;
}