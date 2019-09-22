#include "StdAfx.h"
#include ".\gsworld.h"

GSWorld::GSWorld(void)
{
	penMap=NULL;
	miW=0;
	miH=0;
}

GSWorld::~GSWorld(void)
{
}

bool GSWorld::Init(int iWidth, int iHeight)
{
	penMap=new enObjectType[iWidth*iHeight];

	for(int i=0;i<iWidth*iHeight;i++)
	{
		penMap[i]=Nothing;
	}
	if(penMap!=NULL)
	{
		miW=iWidth;
		miH=iHeight;
		return true;
	}
	return false;
}


GSEgg::GSEgg()
{
}
GSEgg::~GSEgg()
{}

bool GSEgg::Born (enObjectType entype,int ilocation ,GSWorld *pcmap)
{
	//誕生...
	GSEgg::enType =entype;
	GSEgg::mpCMap =pcmap;
	GSEgg::miLocation=ilocation;
	mpCMap->penMap [miLocation]=enType;
	return false;
}

bool GSEgg::IsExist ()
{
	if(mpCMap->penMap [miLocation]!= enType )
	{
		//死了
		return false;
	}
	return true;
}

bool GSEgg::ReBorn (enObjectType entype,int ilocation)
{
	if(!IsExist())
	{
		GSEgg::enType =entype;
		GSEgg::miLocation=ilocation;
		mpCMap->penMap [miLocation]=enType;
		return true;
	}
	return false; //還活著
}

void GSWorld::Destory(void)
{
	delete [] penMap;
}
