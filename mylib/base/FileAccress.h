/*
	設計者:Jiowchern Chen
	目的:一個檔案存取控制器,希望能做到像存取記憶體一樣簡單

*/
//#pragma once

#ifndef DefJCFileAccress
#define DefJCFileAccress
#include "JCString.h"
#include <stdio.h>
#include <io.h>
class CFileAccress
{
	bool bOpening;//是否有檔案開啟
	JCString jcsFileName;
	FILE *pFile;
public:
	char *pcReturnMessage;
	CFileAccress(void);
	~CFileAccress(void);

	// 開啟檔案,in1:檔案名稱 ,in2:沒該檔案是否建立(預設為真) out:成功於否
	bool Open(JCString jcsfilename, bool bCreate=true);

	// 重檔案串流裡讀出資料到pvbuf in1:要接收的buf in2:buf的大小 out:讀取後的檔案指標位置
	long Read(void* pvbuf, size_t bufsize);

	// 取得檔案大小
	long GetFileSize(void);

	// 設定檔案讀取指標
	bool SetPos(long lpos);

	// 檔案寫入,in1: 要寫入的緩衝區,in2:緩衝區大小 out:檔案指標位置
	long Write(void* pvbuf, long bufsize);

	// 取得目前檔案指標位置
	long GetPos(void);

	//關閉檔案
	bool Close(void);

	/*
		
	*/
	//搜尋字元 (非中文字) 輸入:搜尋的字元 輸出:與目前檔案指標的相對位置
	long SearchChar(char c);

	//抓取字串,從目前的檔案指標位置一直抓字直到結束字元(包含結束字元) out:輸出字串 in:結束字元
	JCString GetStringToChar(char cEnd='\0');

	bool IsEof(void)
	{
		return feof(pFile);
	}
};

#endif