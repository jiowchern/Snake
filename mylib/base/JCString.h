// JCString.h: interface for the JCString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JCSTRING_H__28C82C63_96F4_43FF_B936_F6A4876351E2__INCLUDED_)
#define AFX_JCSTRING_H__28C82C63_96F4_43FF_B936_F6A4876351E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	JC�r�����O...

	�H�ᦳ�r�ꪺ���D���i�Υ��ӸѨM
*/
//��ƤޤJ��
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//�ܼƩw�q��
#define DefMAXSTRINGSIZE 255

class JCString  
{
private:
	
	char *msBuf;//�w�İ� �s��r�ꪺ��m����
	int miLen;//�r�����
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
	
	char* sErrorMessage;//��ܿ��~�T����
	// ���o�@����,�ѼƬ��n(��J�����,��X����m)... �Ǧ^�Y��false�h�N��L�Ӧ��
	JCString GetLine(int INiNum, JCString OUTjsString);
	int GetPosToChar(char cEnd,int iBeginPos=0);
	JCString GetString(int iStart,int iLen);
	
	
};

#endif // !defined(AFX_JCSTRING_H__28C82C63_96F4_43FF_B936_F6A4876351E2__INCLUDED_)
