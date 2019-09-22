#include "StdAfx.h"
#include ".\gsnake.h"

GSnake::GSnake(void)
: menDirection(No)
, menTmpDirection(No)
, iLength(0)
, iSpeed(0)
, ptsBody(NULL)
, ptsTail(NULL)
, iMark(0)
, iHunger(1)
, bSurvive(false)
, pCMap(NULL)
, miMapWidth(0)
, miMapHeight(0)
, enID(Nothing)
, pCCount(NULL)
{
}

GSnake::~GSnake(void)
{
}

// 出生...初始化,out:成功 in:id編號 in1:長度,最小為2,in2:速度,in3:出生位置,in4:世界指標
bool GSnake::Born(enObjectType enid,int ilen, int ispeed, int ilocation,GSWorld* pcmap)
{
	if(!bSurvive)
	{
		
		//初始化
		ptsBody=new tsSnakeBody[ilen];
		pCCount=new JCCounter();
		
		
		if(ptsBody!=NULL)
		{
			enID=enid;
			iLength=ilen;
			iSpeed=ispeed;
			pCCount->SetTimer (ispeed);
			pCCount->Begin ();
			menDirection=No;//目前沒方向
			pCMap=pcmap;//帶入NULL借等著出錯吧=_=""
			miMapWidth=pCMap->miW ;
			miMapHeight=pCMap->miH ;
			for(int i=0;i<ilen;i++)
			{
				

				if(i+1<ilen)
				{
					ptsBody[i].psNext=&ptsBody[i+1];
				
				}
				else
				{
					ptsTail=&ptsBody[i];
					
					ptsBody[i].psNext=NULL;
				
				}
				ptsBody[i].enD =No;
				ptsBody[i].iLocation=ilocation;
				pCMap->penMap [ilocation]=enID;
			}
			return bSurvive=true;
		}
		
	}
	return false;
}

// 吃東西.in:世界的位置
void GSnake::Eat(enObjectType enOTLocation)
{
	//for Egg1
	tsSnakeBody *pTmp1=NULL;
	tsSnakeBody *pTmp2=NULL;

	//for Egg2
	tsSnakeBody *head,*tail,*p,*q,*pre=NULL;
	switch( enOTLocation)
	{
	case Nothing :
		//什麼時都沒發生
		//飢餓度增加
		iHunger++;
		break;
	case Egg1  :
		//增加長度
		pTmp1=new tsSnakeBody;//新增
		if(pTmp1!=NULL)
		{
			pTmp2=ptsTail;//尾巴
			pTmp1->iLocation =pTmp2->iLocation ;//直接繼承
			pTmp1->psNext =pTmp2->psNext ;
			pTmp2->psNext =pTmp1;

			//重新設定尾巴
			ptsTail=pTmp1;
			iLength++;
		}
		else
			break ;
		
		break;
	case Egg2  :
		//減少長度
		//GetPreNode
		/*
			尋找Tail之前的節點
		*/
		
		head=ptsBody;
		tail=ptsTail;
		pCMap->penMap [ tail->iLocation ]=Nothing;
		if(head==tail)
			//沒東西可以刪了
			break;

		p=head;
		q=head->psNext ;
		while(q->psNext!=NULL )
		{
			p=q;
			q=q->psNext ;
		}
		if(q!=NULL)
			pre=p;

		if(pre==NULL)
			//節點不存在
			break;
		
		pre->psNext =NULL ; //一搬來說應該是給NULL
		//delete &q->iLocation  ;
		 

		ptsTail=pre;
		iLength--;
		break;
	case Egg3  :
		//增加速度
		iSpeed-=20;
		
		break;
	case Egg4  :
		//減短速度
		iSpeed+=80;
		break;

	case Snake1 :
	case Snake2 :
	case Snake3 :
	case Snake4 :
	case RingOut:
		//死亡
		bSurvive=false;
		break;

	}
	if(enOTLocation!=Nothing)
	{
		//加分
		iMark+=(DefSNAKEMAXSPEED/iHunger);
		iSpeed+=(DefSNAKEMAXSPEED/iHunger*2);
		iHunger=1;
	}
	else
	{
		iSpeed--;
	}

	if(iSpeed>DefSNAKEMAXSPEED)
		iSpeed=DefSNAKEMAXSPEED;
	if(iSpeed<DefSNAKEMINSPEED)
		iSpeed=DefSNAKEMINSPEED;
}

// 存活
bool GSnake::IsSurvive(void)
{
	return  bSurvive;
}

// 活動::out 狀態訊息 0為正常
int GSnake::Activity()
{
	

	/*if(itimer<iSpeed)//判斷是否可以動
		return DefSNAKE_WAIT;*/

	if(bSurvive)
	{
		if(!pCCount->IsTimeUp (NULL))
			return DefSNAKE_WAIT;

		if	(
			//左右
			((menDirection==Up || menDirection==Down) && (menTmpDirection==Left ||menTmpDirection==Right))
			||
			//上下
			((menDirection==Left || menDirection==Right) && (menTmpDirection==Down ||menTmpDirection==Up))
			||
			menDirection==Nothing
		)
		{
			menDirection=menTmpDirection;
		}
		int inewL,ix,iy;
		tsSnakeBody *pTmp;
		int iTmp1;
		int iTmp2;
		enDirection enTmp1;
		enDirection enTmp2;
		
		inewL=ptsBody->iLocation ; //把頭的位置給新的位置
		iy=inewL/miMapWidth;		//算出位置y
		ix=inewL%miMapWidth;		//算出位置x
		switch (menDirection)				
		{
		case No:
			//沒有動
			pCCount->SetTimer (iSpeed);
			pCCount->Begin ();
			return DefSNAKE_OK;
			break;
		case Up:
			//y--
			//計算出新的Location
		
			if(iy<=0)
				Eat(RingOut);
			else
				iy--;
				
			break;
		case Down:
			//y++
			if(iy>=miMapHeight-1)
				Eat(RingOut);
			else
				iy++;
			
			break;
		case Left:
			//x--
			if(ix<=0)
				Eat(RingOut);
			else
				ix--;

			break;
		case Right:
			//x++
			if(ix>=miMapWidth-1)
				Eat(RingOut);
			else
				ix++;

			break;
		}
		inewL=iy*miMapWidth+ix;//新的位置

		//移動到新的位置
		/*
			定義
			iTmp1=要傳給下一個變動資料的值
			iTmp2=暫存iLocation的值
		*/
		
		pTmp=ptsBody;
		iTmp1=inewL;
		enTmp1=menDirection;
		Eat (pCMap->penMap[iTmp1]);//吃到了什麼??

		while(pTmp !=NULL )
		{
			/*
				驗算區:
				iTmp=10 
				iTmp2=20 
				iLocation=30

				1.iTmp2=20
				2.iLocation=10
				3.iTmp1=20

			*/

			iTmp2=pTmp->iLocation ;
			pTmp->iLocation=iTmp1;
			iTmp1=iTmp2;
			
			enTmp2=pTmp->enD  ;
			pTmp->enD =enTmp1;
			enTmp1=enTmp2;

			pCMap->penMap[pTmp->iLocation]=this->enID ;//改變蛇的位置
			pTmp=pTmp->psNext ;
		}

		//最後一個給空白
		pCMap->penMap[iTmp1]=Nothing;
		
		pCCount->SetTimer (iSpeed);
		pCCount->Begin ();

		return DefSNAKE_OK;
	}
	else
		return DefSNAKE_DIE;
	
}

// 取得命令
void GSnake::GetCommand(enDirection enCmd)
{
	menTmpDirection=enCmd;
}

int GSnake::GetSpeed(void)
{
	return iSpeed;
}

void GSnake::Destory(void)
{
	if(ptsBody!=NULL)
	{
		while(iLength!=1)
		{
			this->Eat (Egg2);
		}
		delete [] ptsBody;
		ptsBody=NULL;
	}
	
}
