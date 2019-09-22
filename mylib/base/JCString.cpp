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
		sErrorMessage="operator =(const char *sStr) : 讀入的字串為空字元\0";
	}
	return 0;
}

//直接讀入數字轉字串
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
		int iStrLen=strlen(sStr);//讀入字串的長度
		char *sTmp;
		sTmp=new char [miLen+iStrLen+1];//建立新的字串空間
		//memset(sTmp,0,miLen+iStrLen+1);//清除該空間資料

		//strcat(sTmp,msBuf);//將原Buffer複製到此空間
		memcpy(sTmp,msBuf,miLen);
		//int i;
		//for(i=0;i<miLen;i++)
		//{
		//	sTmp[i]=msBuf[i];
		//}

		//strcat(sTmp,sStr);//江心讀入的資料接上去
		memcpy(sTmp+miLen,sStr,iStrLen);
		//for(i=0;i<iStrLen;i++)
		//{
		//	sTmp[miLen+i]=sStr[i];
		//}
		sTmp[miLen+iStrLen]='\0';
		ClearBuf();
		msBuf=sTmp;
		//msBuf=new char [strlen(sTmp)+1];//建立新的字串空間
		//memcpy(msBuf,sTmp,strlen(sTmp));
		
		//msBuf[strlen(sTmp)]='\0';

		Update();//更變心長度

		//刪除站存
		//delete [] sTmp;
	}
	else
	{
		sErrorMessage="operator +=(const char *sStr) :讀入的字串為空字元\0";
	}
	return 0;
}
JCString::operator +=(char sStr)
{
	if(sStr!=NULL)
	{
		int iStrLen=1;//讀入字串的長度
		char *sTmp;
		sTmp=new char [miLen+iStrLen+1];//建立新的字串空間
		

		//strcat(sTmp,msBuf);//將原Buffer複製到此空間
		memcpy(sTmp,msBuf,miLen);
		//int i;
		//for(i=0;i<miLen;i++)
		//{
		//	sTmp[i]=msBuf[i];
		//}

		//strcat(sTmp,sStr);//江心讀入的資料接上去
		memcpy(sTmp+miLen,&sStr,iStrLen);
		//for(i=0;i<iStrLen;i++)
		//{
		//	sTmp[miLen+i]=sStr[i];
		//}
		sTmp[miLen+iStrLen]='\0';
		ClearBuf();
		msBuf=sTmp;
		//msBuf=new char [strlen(sTmp)+1];//建立新的字串空間
		//memcpy(msBuf,sTmp,strlen(sTmp));
		
		//msBuf[strlen(sTmp)]='\0';

		Update();//更變心長度

		//刪除站存
		//delete [] sTmp;
	}
	else
	{
		sErrorMessage="operator +=(const char *sStr) :讀入的字串為空字元\0";
	}
	return 0;
}
void JCString::ClearBuf()
{
	if(msBuf!=NULL)//清除先前的緩衝區
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
	//如果更新後的長度小於之前長度
	//代表有遺失的長度
	if(strlen(msBuf)<miLen )
	{
		//將移師的部分free
		DelLength(miLen-strlen(msBuf));
	}
	miLen=strlen(msBuf);
}


//完整字串比較 為真傳回 true
bool JCString::FullCompared(char *sString)
{
	return !(bool)strcmp(sString,msBuf);
}

//重尾端減掉字串長度
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
		sTmp=new char [iNewLen+1];//建立新的字串空間
		memset(sTmp,0,iNewLen+1);//清除該空間資料
		
		//strcat(sTmp,msBuf);//將原Buffer複製到此空間
		memcpy(sTmp,msBuf,iNewLen);
		//int i;
		//for(i=0;i<iNewLen;i++)
		//{
		//	sTmp[i]=msBuf[i];
		//}
		sTmp[iNewLen]=0;
		

		ClearBuf();

		//msBuf=new char [iNewLen];//建立新的字串空間
		//memcpy(msBuf,sTmp,iNewLen);
		
		//msBuf[iNewLen-1]='\0';
		msBuf=sTmp;

		Update();//更變心長度

		//刪除站存
		//delete [] sTmp;
		sTmp=NULL;
		return true;
		
	}
	else
	{
		sErrorMessage="DelLength(int iLen)讀入的長度有誤\0";
	}
	return false;
}


//減掉一個字元..含中文字
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

//重指定位置中插入字串
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
		//尋找字元
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