#pragma once
#include "guibase.h"
#include "..\..\Base\FileAccress.h"
#include "..\..\Base\JCCounter.h"
typedef struct _SAnimate
{
	JCString *psFileName;//���J���ɮצW��
	int *piTimeLength;//�C�i����ܪ��ɶ�
	int iImgAmount;//�ϧζq
	int *piImg;//�ϧνs���}�C
	int iCurrentImg;//�ثe��ܪ��ϧνs��
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
	int iCurrent;//�ثe�Ұ��檺�ʵe�s��
	JCCounter CTimer;//�p�ɾ�
public:
	bool IsInit();
	CAnimate(void);
	~CAnimate(void);
	void Release(void);
	bool Init(JCGraphics *Grp
			 ,CTexManager *TM	//����޲z��
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
