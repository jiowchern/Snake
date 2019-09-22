
#include ".\animate.h"
void CAnimate::Release(void)
{
	//刪除動畫	
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
	//抓出目前要顯示的動畫
	if(!IsInit())
	{
		sErrMsg="初始化尚未完成\0";
		return false;
	}
	//先話背景
	//在話文字
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
				,CTexManager *TM	//材質管理器		
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
//輸入1:檔案名稱 輸入2:透明色 輸出:如果傳回0代表失敗,否則是傳回編號
int CAnimate::Add (char *sFN,DWORD dwColorKey)
{
	if(this->IsInit ())
	{
		//檢查沒用到的空間
		int i;
		for(i=0;i<this->iAmount ;i++)
		{
			if(mpSAnimate[i].bUse==false )
			{
				//沒被使用
				//建立
				//讀入檔案
				
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
					//檔案已開啟
					
					//讀入第一筆資料設定Width
					//找尋,
					//抓取寬
					
					
					sTmp=CF.GetStringToChar(',') ;
					
					mpSAnimate[i].iWidth =sTmp.ToInt ();
										
					//抓取長
			
					sTmp=CF.GetStringToChar(',') ;
					
					mpSAnimate[i].iHeight=sTmp.ToInt ();
	

					//圖形數量
					sTmp=CF.GetStringToChar(',');
					mpSAnimate[i].iImgAmount =sTmp.ToInt ();
					

					//抓取圖檔並且建立
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
					
					//紀錄檔名
					mpSAnimate[i].psFileName =new JCString ();
					(*mpSAnimate[i].psFileName)=sFN;
					mpSAnimate[i].psFileName->ToLower ();
					//完成
					mpSAnimate[i].bUse =true;
					return i+1;
				}
				else
				{
					
					sErrMsg="找不到檔案名稱\0" ;
					return 0;
				}
				
			}
		}

		sErrMsg="沒有空間\0" ;
		return 0;
	}
	sErrMsg="沒有初始化\0" ;
	return 0;
}

bool CAnimate::Del (int iNumber)
{
	if(iNumber<=0)
		return false;//輸入的號碼有誤
	
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

//檢查輸入個號碼是否為正確的範圍
bool CAnimate::ChkNumber(int iNum)

{
	iNum-=1;
	if(iNum<iAmount&&iNum>=0)
		return true;
	return false;
}