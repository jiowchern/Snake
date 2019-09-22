// JCString.cpp: implementation of the JCString class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "JCString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JCString::JCString()
{
	msBuf=NULL;
	miLen=0;
}

JCString::JCString(char *sInit)
{

	msBuf=NULL;
	miLen=0;

	JCString::operator = (sInit);
}
JCString::~JCString()
{
	//ClearBuf();

	
}
void JCString::ToUpper(void)
{
	for(int i=0;i<=miLen;i++)
	{
		*(msBuf+i)=toupper((int)*(msBuf+i));
	}
}
void JCString::ToLower(void)
{
	for(int i=0;i<=miLen;i++)
	{
		*(msBuf+i)=tolower((int)*(msBuf+i));
	}
}
JCString::operator =(const char *sStr)
{
	if(sStr!=NULL)
	{
		ClearBuf();
		
		miLen=(int)strlen(sStr);
		
		
		msBuf=new char[miLen+1];
		memset(msBuf,0,miLen);
		memcpy(msBuf,sStr,miLen);
		msBuf[miLen]='\0';
		
		miLen=(int)strlen(msBuf);
		
	}
	else
	{
		sErrorMessage="operator =(const char *sStr) : Ū�J���r�ꬰ�Ŧr��\0";
	}
	return 0;
}

//����Ū�J�Ʀr��r��
JCString::operator =(int iNum)
{
	ClearBuf();
	msBuf=new char[17];
	memset(msBuf,0,17);
	itoa(iNum,msBuf,10);
	miLen=17;
	return 0;
}

bool JCString::IsEmpty()
{
	//miLen=strlen(msBuf);
	if(miLen<=0)
		return true;	
	return false;
}

JCString::operator +=(const char *sStr)
{
	if(sStr!=NULL)
	{
		int iStrLen=strlen(sStr);//Ū�J�r�ꪺ����
		char *sTmp;
		sTmp=new char [miLen+iStrLen+1];//�إ߷s���r��Ŷ�
		//memset(sTmp,0,miLen+iStrLen+1);//�M���ӪŶ����

		//strcat(sTmp,msBuf);//�N��Buffer�ƻs�즹�Ŷ�
		memcpy(sTmp,msBuf,miLen);
		//int i;
		//for(i=0;i<miLen;i++)
		//{
		//	sTmp[i]=msBuf[i];
		//}

		//strcat(sTmp,sStr);//����Ū�J����Ʊ��W�h
		memcpy(sTmp+miLen,sStr,iStrLen);
		//for(i=0;i<iStrLen;i++)
		//{
		//	sTmp[miLen+i]=sStr[i];
		//}
		sTmp[miLen+iStrLen]='\0';
		ClearBuf();
		msBuf=sTmp;
		//msBuf=new char [strlen(sTmp)+1];//�إ߷s���r��Ŷ�
		//memcpy(msBuf,sTmp,strlen(sTmp));
		
		//msBuf[strlen(sTmp)]='\0';

		Update();//���ܤߪ���

		//�R�����s
		//delete [] sTmp;
	}
	else
	{
		sErrorMessage="operator +=(const char *sStr) :Ū�J���r�ꬰ�Ŧr��\0";
	}
	return 0;
}
JCString::operator +=(char sStr)
{
	if(sStr!=NULL)
	{
		int iStrLen=1;//Ū�J�r�ꪺ����
		char *sTmp;
		sTmp=new char [miLen+iStrLen+1];//�إ߷s���r��Ŷ�
		

		//strcat(sTmp,msBuf);//�N��Buffer�ƻs�즹�Ŷ�
		memcpy(sTmp,msBuf,miLen);
		//int i;
		//for(i=0;i<miLen;i++)
		//{
		//	sTmp[i]=msBuf[i];
		//}

		//strcat(sTmp,sStr);//����Ū�J����Ʊ��W�h
		memcpy(sTmp+miLen,&sStr,iStrLen);
		//for(i=0;i<iStrLen;i++)
		//{
		//	sTmp[miLen+i]=sStr[i];
		//}
		sTmp[miLen+iStrLen]='\0';
		ClearBuf();
		msBuf=sTmp;
		//msBuf=new char [strlen(sTmp)+1];//�إ߷s���r��Ŷ�
		//memcpy(msBuf,sTmp,strlen(sTmp));
		
		//msBuf[strlen(sTmp)]='\0';

		Update();//���ܤߪ���

		//�R�����s
		//delete [] sTmp;
	}
	else
	{
		sErrorMessage="operator +=(const char *sStr) :Ū�J���r�ꬰ�Ŧr��\0";
	}
	return 0;
}
void JCString::ClearBuf()
{
	if(msBuf!=NULL)//�M�����e���w�İ�
	{
		delete [] msBuf;
		msBuf=NULL;
		miLen=0;
	}
}

int JCString::Length()
{
	return miLen;
}

int JCString::ToInt()
{
	char *sTmp;
	return (int)strtol(msBuf,&sTmp,0);
}

char * JCString::GetBuffer()
{
	return msBuf;
}

void JCString::Update()
{
	//�p�G��s�᪺���פp�󤧫e����
	//�N���򥢪�����
	if(strlen(msBuf)<miLen )
	{
		//�N���v������free
		DelLength(miLen-strlen(msBuf));
	}
	miLen=strlen(msBuf);
}


//����r���� ���u�Ǧ^ true
bool JCString::FullCompared(char *sString)
{
	return !(bool)strcmp(sString,msBuf);
}

//�����ݴ�r�����
bool JCString::DelLength(int iLen)
{
	int iNewLen=miLen-iLen;
	if(iNewLen==0)
	{
		ClearBuf();
		return true;
	}
	if(iNewLen>=1)
	{	
		char *sTmp;
		sTmp=new char [iNewLen+1];//�إ߷s���r��Ŷ�
		memset(sTmp,0,iNewLen+1);//�M���ӪŶ����
		
		//strcat(sTmp,msBuf);//�N��Buffer�ƻs�즹�Ŷ�
		memcpy(sTmp,msBuf,iNewLen);
		//int i;
		//for(i=0;i<iNewLen;i++)
		//{
		//	sTmp[i]=msBuf[i];
		//}
		sTmp[iNewLen]=0;
		

		ClearBuf();

		//msBuf=new char [iNewLen];//�إ߷s���r��Ŷ�
		//memcpy(msBuf,sTmp,iNewLen);
		
		//msBuf[iNewLen-1]='\0';
		msBuf=sTmp;

		Update();//���ܤߪ���

		//�R�����s
		//delete [] sTmp;
		sTmp=NULL;
		return true;
		
	}
	else
	{
		sErrorMessage="DelLength(int iLen)Ū�J�����צ��~\0";
	}
	return false;
}


//��@�Ӧr��..�t����r
bool JCString::DelChar(void)
{
	if(miLen==0)
		return true;
	int iChr;
	if(msBuf[miLen-1]<=127&&msBuf[miLen-1]>=0)
		iChr=1;
	else
		iChr=2;

	return DelLength(iChr);
	
}

//�����w��m�����J�r��
bool JCString::InsertString(int iPos, char *sString)
{
	return true;
}

int JCString::GetCharAmount(char c)
{
	int i;
	int iCharCount=0;
	for(i=0;i<miLen;i++)
		if(msBuf[i]==c)
			iCharCount++;
	
	return iCharCount;
}

int JCString::GetPosToChar(char cEnd,int iBeginPos)
{
	
	if(msBuf)
	{
		int iIdx;
		//�M��r��
		for(iIdx=iBeginPos;iIdx<miLen;iIdx++)
		{
			if( msBuf[iIdx]==cEnd )
			{
				return iIdx+1;
			}
		}
	}
	return 0;

}

JCString JCString::GetString (int iStart,int iLen)
{
		JCString sRet="";
		int i;
		for(i=iStart-1;i<iStart+iLen&& i<miLen ;i++)		
		{
			sRet+=msBuf[i];
		}
		return sRet;
}