/*
	�]�p��:Jiowchern Chen
	�ت�:�@���ɮצs�����,�Ʊ�వ�칳�s���O����@��²��

*/
//#pragma once

#ifndef DefJCFileAccress
#define DefJCFileAccress
#include "JCString.h"
#include <stdio.h>
#include <io.h>
class CFileAccress
{
	bool bOpening;//�O�_���ɮ׶}��
	JCString jcsFileName;
	FILE *pFile;
public:
	char *pcReturnMessage;
	CFileAccress(void);
	~CFileAccress(void);

	// �}���ɮ�,in1:�ɮצW�� ,in2:�S���ɮ׬O�_�إ�(�w�]���u) out:���\��_
	bool Open(JCString jcsfilename, bool bCreate=true);

	// ���ɮצ�y��Ū�X��ƨ�pvbuf in1:�n������buf in2:buf���j�p out:Ū���᪺�ɮ׫��Ц�m
	long Read(void* pvbuf, size_t bufsize);

	// ���o�ɮפj�p
	long GetFileSize(void);

	// �]�w�ɮ�Ū������
	bool SetPos(long lpos);

	// �ɮ׼g�J,in1: �n�g�J���w�İ�,in2:�w�İϤj�p out:�ɮ׫��Ц�m
	long Write(void* pvbuf, long bufsize);

	// ���o�ثe�ɮ׫��Ц�m
	long GetPos(void);

	//�����ɮ�
	bool Close(void);

	/*
		
	*/
	//�j�M�r�� (�D����r) ��J:�j�M���r�� ��X:�P�ثe�ɮ׫��Ъ��۹��m
	long SearchChar(char c);

	//����r��,�q�ثe���ɮ׫��Ц�m�@����r���쵲���r��(�]�t�����r��) out:��X�r�� in:�����r��
	JCString GetStringToChar(char cEnd='\0');

	bool IsEof(void)
	{
		return feof(pFile);
	}
};

#endif