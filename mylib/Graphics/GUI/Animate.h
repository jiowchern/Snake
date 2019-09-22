#pragma once
#include "guibase.h"
#include "..\..\Base\FileAccress.h"
#include "..\..\Base\JCCounter.h"
typedef struct _SAnimate
{
	JCString *psFileName;//載入的檔案名稱
	int *piTimeLength;//每張圖顯示的時間
	int iImgAmount;//圖形量
	int *piImg;//圖形編號陣列
	int iCurrentImg;//目前顯示的圖形編號
	int iWidth;
	int iHeight;
	int dwColorKey;
	bool bUse;
} SAnimate;


class CAnimate :
	public CGUIBase
{
private:
	SAnimate *mpSAnimate;
	int iAmount;
	int iCurrent;//目前所執行的動畫編號
	JCCounter CTimer;//計時器
public:
	bool IsInit();
	CAnimate(void);
	~CAnimate(void);
	void Release(void);
	bool Init(JCGraphics *Grp
			 ,CTexManager *TM	//材質管理器
		     ,int Amount);

	bool ChkNumber(int iNum);
	
	bool Del(char *sFileName);
	int NameToNum(char *sFileName);
	bool Del(int iNumber);
	bool SelectImg(JCString sFileName);
	bool SelectImg(int iNum)
	{
		if(ChkNumber(iNum)&&mpSAnimate[iNum].bUse)
		{
			iCurrent=iNum;
			return true;
		}
		return false;
	}
	bool Display(void);
	int Add(char *sFileName,DWORD dwColorKey=0xffff00ff);
};
