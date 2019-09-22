// JCString.h: interface for the JCString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JCSTRING_H__28C82C63_96F4_43FF_B936_F6A4876351E2__INCLUDED_)
#define AFX_JCSTRING_H__28C82C63_96F4_43FF_B936_F6A4876351E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	JC字串類別...

	以後有字串的問題都可用它來解決
*/
//函數引入區
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//變數定義區
#define DefMAXSTRINGSIZE 255

class JCString  
{
private:
	
	char *msBuf;//緩衝區 存放字串的位置指標
	int miLen;//字串長度
public:
	int GetCharAmount(char c);
	bool InsertString(int iPos,char *sString);
	bool DelChar(void);
	bool DelLength(int iLen=1);
	bool FullCompared(char * sString);
	void Update(void);
	char * GetBuffer(void);
	int ToInt(void);
	int Length(void);
	bool IsEmpty(void);
	JCString();
	JCString(char *sInit);
	virtual ~JCString();
	void ToUpper(void);
	void ToLower(void);
	operator =(const char *sStr);
	operator +=(const char *sStr);
	operator +=(char c);
	operator =(int iNum);
	//
	void ClearBuf(void);
	
	char* sErrorMessage;//顯示錯誤訊息用
	// 取得一行資料,參數為要(輸入之行數,輸出的位置)... 傳回若為false則代表無該行數
	JCString GetLine(int INiNum, JCString OUTjsString);
	int GetPosToChar(char cEnd,int iBeginPos=0);
	JCString GetString(int iStart,int iLen);
	
	
};

#endif // !defined(AFX_JCSTRING_H__28C82C63_96F4_43FF_B936_F6A4876351E2__INCLUDED_)
