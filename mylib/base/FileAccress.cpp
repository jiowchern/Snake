#include "fileaccress.h"

CFileAccress::CFileAccress(void)
{
	this->bOpening =false;
	this->jcsFileName="";
	this->pFile =NULL;
	
}

CFileAccress::~CFileAccress(void)
{
}

// 開啟檔案,in1:檔案名稱 ,in2:沒該檔案是否建立(預設為真) out:成功於否
bool CFileAccress::Open(JCString jcsfilename, bool bCreate)
{
	//開啟檔案
	pFile=fopen(jcsfilename.GetBuffer (),"r+b");

	if(pFile==NULL && bCreate)
	{//檔案不存在嘗試製造新檔案
		pFile=fopen(jcsfilename.GetBuffer (),"w+b");

		if(pFile==NULL)
		{	//無法建立檔案
			this->pcReturnMessage ="CFileAccress::Open(JCString jcsfilename, bool bCreate) 檔案建立並未成功\0";
			return false;
		}
	}
	

	jcsFileName=jcsfilename;
	pcReturnMessage="CFileAccress::Open(JCString jcsfilename, bool bCreate) 執行成功\0";
	return bOpening=true;
}
// 重檔案串流裡讀出資料到pvbuf in1:要接收的buf in2:buf的大小 out:讀取後的檔案指標位置
long CFileAccress::Read(void* pvbuf, size_t bufsize)
{
	if(bOpening)	
	{
		if(feof(pFile))
		{
			this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int bufsize) 檔案已到結尾\0";
			return 0;
		}
		size_t stRealReadSize=fread(pvbuf,1,bufsize,pFile);

		if(stRealReadSize==bufsize)
		{	
			//讀取成功
			this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) 讀取成功\0";
			return ftell(pFile);
		}
		else if (stRealReadSize<=bufsize)
		{
			//如果真實讀到的大小小於原本的大小
			//代表檔案已到結尾
			this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) 讀取成功,但是並不是完整的緩衝大小\0";
			return ftell(pFile);

		}
		else if(stRealReadSize==0)
		{
			//讀取失敗
			if(feof(pFile))
			{
				this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) 檔案已到結尾\0";
			}
			else
			{
				this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) 讀取失敗\0";
			}
			return 0;
		}
		
	}


	this->pcReturnMessage ="CFileAccress 並沒有檔案被開啟\0";

	return 0;
}

// 取得檔案大小
long CFileAccress::GetFileSize(void)
{
	if(bOpening)
	{
		return filelength(fileno(pFile));
	}

	this->pcReturnMessage ="CFileAccress 並沒有檔案被開啟\0";
	return 0;
}

// 設定檔案讀取指標
bool CFileAccress::SetPos(long lpos)
{
	if(bOpening)
	{
		fpos_t fpt;

		fgetpos(pFile,&fpt);

		fpt=(fpos_t)lpos;

		if(fsetpos(pFile,&fpt))
		{
			this->pcReturnMessage ="CFileAccress::SetPos(long lpos) 失敗\0";
			return false;
		}
		return true;
	}

	this->pcReturnMessage ="CFileAccress 並沒有檔案被開啟\0";
	return false;
}

// 檔案寫入,in1: 要寫入的緩衝區,in2:緩衝區大小 out:檔案指標位置
long CFileAccress::Write(void* pvbuf, long bufsize)
{
	if(bOpening)
	{
		fwrite(pvbuf,1,bufsize,pFile);
		return ftell(pFile);
	}

	this->pcReturnMessage ="CFileAccress 並沒有檔案被開啟\0";
	return 0;
}

// 取得目前檔案指標位置
long CFileAccress::GetPos(void)
{
	if(bOpening)
	{
		fpos_t pfpt;

		fgetpos(pFile,&pfpt);
		return (long)pfpt;
	}
	this->pcReturnMessage ="CFileAccress 並沒有檔案被開啟\0";
	return 0;
}

bool CFileAccress::Close(void)
{
	//如果檔案被開啟
	if(bOpening)
	{
		close(fileno(pFile));
		bOpening=false;
		pFile=NULL;
		jcsFileName="";
		return true;
	}

	this->pcReturnMessage ="CFileAccress 並沒有檔案被開啟\0";
	return false;
}

long CFileAccress::SearchChar(char c)
{
	if(bOpening)
	{
		//備份目前的位置	
		long lBPos= this->GetPos ();
		long lFindPos;
		char c1;//抓取的字元
		do
		{
			this->Read(&c1,1);
		}
		while(c1!=c&& (!IsEof()) );//比較

		lFindPos=this->GetPos ();
		
		//還原位置
		this->SetPos (lBPos);
		
		return lFindPos-lBPos;
	}
	return 0;
}

JCString CFileAccress::GetStringToChar(char cEnd)
{

	JCString sTmp="";
	if(bOpening)
	{
		long lCharPos;
		char *pcBuffer;
		lCharPos= SearchChar (cEnd)+1;//+1是\0的空間
		pcBuffer=new char[lCharPos];
		memset(pcBuffer,0,lCharPos);
		Read (pcBuffer,(size_t)lCharPos-1);
		sTmp=pcBuffer;		
		delete [] pcBuffer;
	}
	return sTmp;
}