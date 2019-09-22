// FontManager.cpp: implementation of the CFontManager class.
//
//////////////////////////////////////////////////////////////////////

#include "FontManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFontManager::CFontManager()
{
	pD3D8Dev=NULL;
	iAmount=0;//文字數量
	pFont=NULL;
}

CFontManager::~CFontManager()
{
	//Release Fonts
	pD3D8Dev=NULL;
	iAmount=0;
}

bool CFontManager::Init(LPDIRECT3DDEVICE8 pDev, int Amount)
{
	if (pDev==NULL)	
		return false;
	pFont=new SFontFmt[Amount];
	int iIdx;
	for(iIdx=0;iIdx<Amount;iIdx++)
	{
		memset(&pFont[iIdx],0,sizeof(SFontFmt));
	}
	iAmount=Amount;
	pD3D8Dev=pDev;
	return true;	
}

int CFontManager::Add(int iFontSize,DWORD dwFontColor,char * sFontName,int iFontWeight)
{
	HFONT hFont ;
	//找未使用的字串位置
	int idx;

	for (idx=0;idx<iAmount;idx++)
	{
		if(pFont[idx].bEnable ==false)	
			break;
	}
	if (idx==iAmount)
		//找不到空白的
		return 0;

	pFont[idx].dwFontColor =dwFontColor;
	pFont[idx].iFontSize =iFontSize;
	pFont[idx].iFontWeight =iFontWeight;
	pFont[idx].iShowTextPosX =0;
	pFont[idx].iShowTextPosY =0;
	pFont[idx].pcFontName =sFontName;
	pFont[idx].sText ="";

	hFont=CreateFont
	(
		iFontSize,	// logical height of font 
		iFontSize/2,	// logical average character width 
		GM_ADVANCED,	// angle of escapement 
		0,	// base-line orientation angle 
		iFontWeight,	// font weight 
		FALSE,	// italic attribute flag 
		FALSE,	// underline attribute flag 
		FALSE,	// strikeout attribute flag 
		DEFAULT_CHARSET,	// character set identifier 
		OUT_DEFAULT_PRECIS	,	// output precision 
		CLIP_DEFAULT_PRECIS	,	// clipping precision 
		DEFAULT_QUALITY	,	// output quality 
		DEFAULT_PITCH,	// pitch and family 
		sFontName	// pointer to typeface name string 
	);

	if( FAILED(D3DXCreateFont(pD3D8Dev,hFont,&pFont[idx].pFont  )))
	{
		//sErrMsg="Font建立失敗\0";
		return 0;
	}	
	pFont[idx].bEnable =true;
	return idx+1;
}

bool CFontManager::SetText(int iNum, JCString sText, int iX, int iY, DWORD dwColor)
{
	iNum-=1;
	if (!(iNum>=0&&iNum<iAmount))
		return false;

	if (!pFont[iNum].bEnable )
		return false;

	pFont[iNum].dwFontColor =dwColor;
//	pFont[idx].iFontSize =iFontSize;
//	pFont[idx].iFontWeight =iFontWeight;
	pFont[iNum].iShowTextPosX =iX;
	pFont[iNum].iShowTextPosY =iY;
//	pFont[idx].pcFontName =sFontName;
	pFont[iNum].sText =sText;
	return true;
}

bool CFontManager::Draw(int iNum)
{
	iNum-=1;
	if (!(iNum>=0&&iNum<iAmount))
		return false;

	if (!pFont[iNum].bEnable )
		return false;
	RECT rt;
	rt=GetTextRect(iNum+1);//因為要給的是編號不是實際位置所以要－１
	

	pFont[iNum].pFont->Begin ();
	pFont[iNum].pFont->DrawText (pFont[iNum].sText.GetBuffer () ,pFont[iNum].sText.Length () ,&rt,DT_LEFT,pFont[iNum].dwFontColor );
	pFont[iNum].pFont->End ();

	return true;
}



bool CFontManager::Delete(int iNum)
{
	iNum-=1;
	if (!(iNum>=0&&iNum<iAmount))
		return false;
	pFont[iNum].sText=""; 
	if(pFont[iNum].pFont!=NULL)
	{
		pFont[iNum].pFont->Release();
		pFont[iNum].pFont=NULL;
	}
	pFont[iNum].bEnable =false;
	return true;
}


//利用輸入字串找尋編號 0為沒有找到
int CFontManager::GetNumberByText(char *sText)
{
	int idx;
	for(idx=0;idx<iAmount;idx++)
	{
		if(pFont[idx].bEnable  && pFont[idx].sText.FullCompared(sText)   )
			return idx+1;
	}

	return 0;
}

void CFontManager::Release()
{
	int idx;
	for(idx=0;idx<iAmount;idx++)
	{
		Delete(idx+1);
	}

}

//取得SFontFmt
SFontFmt* CFontManager::GetFontFmt(int iNum)
{
	iNum-=1;
	
	if(iNum>=0&&iNum<iAmount)
		if(pFont[iNum].bEnable)
			return &pFont[iNum];

	return NULL;
}

//取得文字顯示區域
RECT CFontManager::GetTextRect(int iNum)
{
	RECT rt;
	rt.bottom =0;
	rt.left =0;
	rt.right =0;
	rt.top =0;

	iNum-=1;
	if(iNum>=0&&iNum<iAmount)
		if(pFont[iNum].bEnable)
		{
			rt.top =(int)pFont[iNum].iShowTextPosY  ;
			rt.left =(int)pFont[iNum].iShowTextPosX ;
			rt.right =(int)pFont[iNum].sText.Length ()*((pFont[iNum].iFontSize/2)  /*+pFont[iNum].iShowTextPosX*/ );
			rt.bottom =(int)pFont[iNum].iFontSize;
		}

	return rt;
}


//自訂顯示區域
bool CFontManager::Draw(int iNum, RECT rt)
{
	iNum-=1;
	if (!(iNum>=0&&iNum<iAmount))
		return false;

	if (!pFont[iNum].bEnable )
		return false;

	pFont[iNum].pFont->Begin ();
	pFont[iNum].pFont->DrawText (pFont[iNum].sText.GetBuffer () ,pFont[iNum].sText.Length () ,&rt,DT_LEFT,pFont[iNum].dwFontColor );
	pFont[iNum].pFont->End ();

	return true;
}

bool CFontManager::Draw(int iNum, RECT rt, DWORD dwFmt)
{
	iNum-=1;
	if (!(iNum>=0&&iNum<iAmount))
		return false;

	if (!pFont[iNum].bEnable )
		return false;

	pFont[iNum].pFont->Begin ();
	pFont[iNum].pFont->DrawText (pFont[iNum].sText.GetBuffer () ,pFont[iNum].sText.Length () ,&rt,dwFmt,pFont[iNum].dwFontColor );
	pFont[iNum].pFont->End ();
}
