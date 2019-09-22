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

// �}���ɮ�,in1:�ɮצW�� ,in2:�S���ɮ׬O�_�إ�(�w�]���u) out:���\��_
bool CFileAccress::Open(JCString jcsfilename, bool bCreate)
{
	//�}���ɮ�
	pFile=fopen(jcsfilename.GetBuffer (),"r+b");

	if(pFile==NULL && bCreate)
	{//�ɮפ��s�b���ջs�y�s�ɮ�
		pFile=fopen(jcsfilename.GetBuffer (),"w+b");

		if(pFile==NULL)
		{	//�L�k�إ��ɮ�
			this->pcReturnMessage ="CFileAccress::Open(JCString jcsfilename, bool bCreate) �ɮ׫إߨå����\\0";
			return false;
		}
	}
	

	jcsFileName=jcsfilename;
	pcReturnMessage="CFileAccress::Open(JCString jcsfilename, bool bCreate) ���榨�\\0";
	return bOpening=true;
}
// ���ɮצ�y��Ū�X��ƨ�pvbuf in1:�n������buf in2:buf���j�p out:Ū���᪺�ɮ׫��Ц�m
long CFileAccress::Read(void* pvbuf, size_t bufsize)
{
	if(bOpening)	
	{
		if(feof(pFile))
		{
			this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int bufsize) �ɮפw�쵲��\0";
			return 0;
		}
		size_t stRealReadSize=fread(pvbuf,1,bufsize,pFile);

		if(stRealReadSize==bufsize)
		{	
			//Ū�����\
			this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) Ū�����\\0";
			return ftell(pFile);
		}
		else if (stRealReadSize<=bufsize)
		{
			//�p�G�u��Ū�쪺�j�p�p��쥻���j�p
			//�N���ɮפw�쵲��
			this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) Ū�����\,���O�ä��O���㪺�w�Ĥj�p\0";
			return ftell(pFile);

		}
		else if(stRealReadSize==0)
		{
			//Ū������
			if(feof(pFile))
			{
				this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) �ɮפw�쵲��\0";
			}
			else
			{
				this->pcReturnMessage ="CFileAccress::Read(void* pvbuf, int ibufsize) Ū������\0";
			}
			return 0;
		}
		
	}


	this->pcReturnMessage ="CFileAccress �èS���ɮ׳Q�}��\0";

	return 0;
}

// ���o�ɮפj�p
long CFileAccress::GetFileSize(void)
{
	if(bOpening)
	{
		return filelength(fileno(pFile));
	}

	this->pcReturnMessage ="CFileAccress �èS���ɮ׳Q�}��\0";
	return 0;
}

// �]�w�ɮ�Ū������
bool CFileAccress::SetPos(long lpos)
{
	if(bOpening)
	{
		fpos_t fpt;

		fgetpos(pFile,&fpt);

		fpt=(fpos_t)lpos;

		if(fsetpos(pFile,&fpt))
		{
			this->pcReturnMessage ="CFileAccress::SetPos(long lpos) ����\0";
			return false;
		}
		return true;
	}

	this->pcReturnMessage ="CFileAccress �èS���ɮ׳Q�}��\0";
	return false;
}

// �ɮ׼g�J,in1: �n�g�J���w�İ�,in2:�w�İϤj�p out:�ɮ׫��Ц�m
long CFileAccress::Write(void* pvbuf, long bufsize)
{
	if(bOpening)
	{
		fwrite(pvbuf,1,bufsize,pFile);
		return ftell(pFile);
	}

	this->pcReturnMessage ="CFileAccress �èS���ɮ׳Q�}��\0";
	return 0;
}

// ���o�ثe�ɮ׫��Ц�m
long CFileAccress::GetPos(void)
{
	if(bOpening)
	{
		fpos_t pfpt;

		fgetpos(pFile,&pfpt);
		return (long)pfpt;
	}
	this->pcReturnMessage ="CFileAccress �èS���ɮ׳Q�}��\0";
	return 0;
}

bool CFileAccress::Close(void)
{
	//�p�G�ɮ׳Q�}��
	if(bOpening)
	{
		close(fileno(pFile));
		bOpening=false;
		pFile=NULL;
		jcsFileName="";
		return true;
	}

	this->pcReturnMessage ="CFileAccress �èS���ɮ׳Q�}��\0";
	return false;
}

long CFileAccress::SearchChar(char c)
{
	if(bOpening)
	{
		//�ƥ��ثe����m	
		long lBPos= this->GetPos ();
		long lFindPos;
		char c1;//������r��
		do
		{
			this->Read(&c1,1);
		}
		while(c1!=c&& (!IsEof()) );//���

		lFindPos=this->GetPos ();
		
		//�٭��m
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
		lCharPos= SearchChar (cEnd)+1;//+1�O\0���Ŷ�
		pcBuffer=new char[lCharPos];
		memset(pcBuffer,0,lCharPos);
		Read (pcBuffer,(size_t)lCharPos-1);
		sTmp=pcBuffer;		
		delete [] pcBuffer;
	}
	return sTmp;
}