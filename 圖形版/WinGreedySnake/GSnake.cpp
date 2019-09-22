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

// �X��...��l��,out:���\ in:id�s�� in1:����,�̤p��2,in2:�t��,in3:�X�ͦ�m,in4:�@�ɫ���
bool GSnake::Born(enObjectType enid,int ilen, int ispeed, int ilocation,GSWorld* pcmap)
{
	if(!bSurvive)
	{
		
		//��l��
		ptsBody=new tsSnakeBody[ilen];
		pCCount=new JCCounter();
		
		
		if(ptsBody!=NULL)
		{
			enID=enid;
			iLength=ilen;
			iSpeed=ispeed;
			pCCount->SetTimer (ispeed);
			pCCount->Begin ();
			menDirection=No;//�ثe�S��V
			pCMap=pcmap;//�a�JNULL�ɵ��ۥX���a=_=""
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

// �Y�F��.in:�@�ɪ���m
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
		//����ɳ��S�o��
		//���j�׼W�[
		iHunger++;
		break;
	case Egg1  :
		//�W�[����
		pTmp1=new tsSnakeBody;//�s�W
		if(pTmp1!=NULL)
		{
			pTmp2=ptsTail;//����
			pTmp1->iLocation =pTmp2->iLocation ;//�����~��
			pTmp1->psNext =pTmp2->psNext ;
			pTmp2->psNext =pTmp1;

			//���s�]�w����
			ptsTail=pTmp1;
			iLength++;
		}
		else
			break ;
		
		break;
	case Egg2  :
		//��֪���
		//GetPreNode
		/*
			�M��Tail���e���`�I
		*/
		
		head=ptsBody;
		tail=ptsTail;
		pCMap->penMap [ tail->iLocation ]=Nothing;
		if(head==tail)
			//�S�F��i�H�R�F
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
			//�`�I���s�b
			break;
		
		pre->psNext =NULL ; //�@�h�ӻ����ӬO��NULL
		//delete &q->iLocation  ;
		 

		ptsTail=pre;
		iLength--;
		break;
	case Egg3  :
		//�W�[�t��
		iSpeed-=20;
		
		break;
	case Egg4  :
		//��u�t��
		iSpeed+=80;
		break;

	case Snake1 :
	case Snake2 :
	case Snake3 :
	case Snake4 :
	case RingOut:
		//���`
		bSurvive=false;
		break;

	}
	if(enOTLocation!=Nothing)
	{
		//�[��
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

// �s��
bool GSnake::IsSurvive(void)
{
	return  bSurvive;
}

// ����::out ���A�T�� 0�����`
int GSnake::Activity()
{
	

	/*if(itimer<iSpeed)//�P�_�O�_�i�H��
		return DefSNAKE_WAIT;*/

	if(bSurvive)
	{
		if(!pCCount->IsTimeUp (NULL))
			return DefSNAKE_WAIT;

		if	(
			//���k
			((menDirection==Up || menDirection==Down) && (menTmpDirection==Left ||menTmpDirection==Right))
			||
			//�W�U
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
		
		inewL=ptsBody->iLocation ; //���Y����m���s����m
		iy=inewL/miMapWidth;		//��X��my
		ix=inewL%miMapWidth;		//��X��mx
		switch (menDirection)				
		{
		case No:
			//�S����
			pCCount->SetTimer (iSpeed);
			pCCount->Begin ();
			return DefSNAKE_OK;
			break;
		case Up:
			//y--
			//�p��X�s��Location
		
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
		inewL=iy*miMapWidth+ix;//�s����m

		//���ʨ�s����m
		/*
			�w�q
			iTmp1=�n�ǵ��U�@���ܰʸ�ƪ���
			iTmp2=�ȦsiLocation����
		*/
		
		pTmp=ptsBody;
		iTmp1=inewL;
		enTmp1=menDirection;
		Eat (pCMap->penMap[iTmp1]);//�Y��F����??

		while(pTmp !=NULL )
		{
			/*
				����:
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

			pCMap->penMap[pTmp->iLocation]=this->enID ;//���ܳD����m
			pTmp=pTmp->psNext ;
		}

		//�̫�@�ӵ��ť�
		pCMap->penMap[iTmp1]=Nothing;
		
		pCCount->SetTimer (iSpeed);
		pCCount->Begin ();

		return DefSNAKE_OK;
	}
	else
		return DefSNAKE_DIE;
	
}

// ���o�R�O
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
