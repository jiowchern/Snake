/*
	Designer:Jiowchern Chen
	
	ProgrameName:�g�Y�D������
	
*/

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

//�ޤJSnake��Lib
#include "GSWorld.h"
#include "GSnake.h"
//JCGrapgics
#include "..\..\MyLib\Graphics\2dlib\JCGraphics.h"
#include "..\..\MyLib\Graphics\2dlib\TexManager.h"
#include "..\..\MyLib\Graphics\2dlib\FontManager.h"
#include "..\..\MyLib\audio\JCMusic.h"
#include "..\..\MyLib\Graphics\Gui\GUIButton.h" //GUI���s
#include "..\..\MyLib\Graphics\Gui\GUIText.h"	//GUI��r����
#include "..\..\MyLib\Graphics\Gui\GUIMouse.h"	//GUI�ƹ�����
#define DefMAINWINDOWNAME "�g�Y�D������ by J.C"
#define DefTHISCLASSNAME  "�g�Y�D���O"
#define DefWINDOWWIDTH 800				//�e���e��
#define DefWINDOWHEIGHT 600				//�e������
#define DefIsFullScreen false			//�O�_�����ù�
#define DefSHOWSYSTEMMOUSEPOINT false	//�ƹ�����
#define DefIMGAMOUNT 1000				//�C���i��Ψ쪺�̤j�϶q

#define DefFPS 60 //FPS
#define DefCOLORKEY 0Xffff00ff
#define DefSafeRelease(pObject) if(pObject != NULL) {pObject->Release(); pObject=NULL;}

//�C���R�x
#define DefQUIT			0	//���}
#define DefMAINMENU		1	//�D���
#define Def1PLAY		2	//�C���D�� ��H��
#define Def2PLAY		3	//�C���D�� ���H��
#define DefABOUT		4	//����s�@


//�C���]�w
#define DefGSNAKESPEED	200
#define DefGSNAKELENGTH 20
//����w�q
#define DefPLAY1UP		VK_UP
#define DefPLAY1DOWN	VK_DOWN
#define DefPLAY1LEFT	VK_LEFT
#define DefPLAY1RIGHT	VK_RIGHT
#define DefPLAY2UP		0X57
#define DefPLAY2DOWN	0X53
#define DefPLAY2LEFT	0X41
#define DefPLAY2RIGHT	0X44
#define DefESC			VK_ESCAPE 		

//�����ܼ�
//�R�x����
int giGameSceneIdx=DefMAINMENU;
int giSystemFont;//�t�Τ�r
//�e��
JCGraphics *gpGrp=NULL;

//����޲z��
CTexManager *gpTexM=NULL;
CFontManager *gpFontM=NULL;
//�C������
JCMusic *gpMusic=NULL;
//GSnake *gpSnake=NULL;
//GSWorld *gpWorld=NULL;
//GSEgg *gpEgg=NULL;
CGUIMouse *gpMPoint=NULL;

/////////////////////////////////////////////////////////////////////////////
/*
	�C���R�x�������O
*/

__interface IGameBase
{
	bool GetMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) ;
	int Action(void);
	bool Render(void);
	bool IsInit(void);
	bool Init(void);
	void Release(void);
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/*
	�C���D��
*/

class CGameBody : public IGameBase
{
private:
	bool bInit;
	GSWorld *pCGSW;
	GSnake *pCSnake;
	GSEgg *pCEgg;
	int iPlay;//���a�H��
	JCString sNothing;
	JCString sSnakeHead1;
	JCString sSnakeTail1;
	JCString sSnakeBody1;
	JCString sSnakeHead2;
	JCString sSnakeTail2;
	JCString sSnakeBody2;
	JCString sEgg1;
	JCString sEgg2;
	JCString sEgg3;
	JCString sEgg4;
	JCString sBtn1;
	JCString sBtn2;
	JCString sBtn3;
	JCString sText;
	CGUIButton *pBtn1;
	
	CGUIText *pText;
	int i;//���y����
	int ip;//���ޥ[�v��
	bool bGameOver;
public:
	enObjectType RndGetEggType(void)
	{	
		enObjectType entype;
		int iVal=rand()%100+1;

		if(iVal>75)//76~100
			entype=Egg4;
		else if(iVal>50)//51~75
			entype=Egg3;
		else if(iVal>40)//41~50
			entype=Egg2;
		else if(iVal>0)//1~40
			entype=Egg1;
		
		return entype;
	}

	CGameBody()
	{
		iPlay=1;
		i=0;
		ip=1;
		pCGSW=NULL;
		pCSnake=NULL;
		pCEgg=NULL;
		bInit=false;
		sNothing	="img\\nothing.bmp";
		sSnakeHead1	="img\\SnakeHead.bmp";
		sSnakeTail1="img\\snaketail.bmp";
		sSnakeBody1="img\\snakebody.bmp";
		sSnakeHead2	="img\\SnakeHead2.bmp";
		sSnakeTail2="img\\snaketail2.bmp";
		sSnakeBody2="img\\snakebody2.bmp";
		sEgg1="img\\egg1.bmp";
		sEgg2="img\\egg2.bmp";
		sEgg3="img\\egg3.bmp";
		sEgg4="img\\egg4.bmp";

		sBtn1="img\\btn_ok.bmp";
		sBtn2="img\\btn_ok_A.bmp";
		sBtn3="img\\btn_ok_b.bmp";
		sText="img\\win_msgbox.bmp";
		pBtn1=NULL;
		bGameOver=true;
		pText=NULL;
	}
	bool GetMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if(pBtn1!=NULL&&pBtn1->IsInit ())
			pBtn1->GetWinMessage (hWnd,msg,wParam,lParam);
		if(msg==WM_KEYDOWN)
			switch (wParam)
			{
			case DefESC :
				//���}�C��
				return false;
				break;
			case DefPLAY1UP :
				pCSnake->GetCommand (Up );
				break;
			case DefPLAY1DOWN:
				pCSnake->GetCommand (Down );
				break;
			case DefPLAY1LEFT:
				pCSnake->GetCommand (Left );
				break;
			case DefPLAY1RIGHT:
				pCSnake->GetCommand (Right );
				break;

			case DefPLAY2UP :
				pCSnake[1].GetCommand (Up );
				break;
			case DefPLAY2DOWN:
				pCSnake[1].GetCommand (Down );
				break;
			case DefPLAY2LEFT:
				pCSnake[1].GetCommand (Left );
				break;
			case DefPLAY2RIGHT:
				pCSnake[1].GetCommand (Right );
				break;
			}
		return true;
	}
	int Action(void)
	{
		if(!bInit)
			return (Def1PLAY+iPlay-1);
		if(bGameOver)
		{
			gpMPoint->Show ();
			//return DefMAINMENU;
			//��ܦ��`����
			
			//pText->SetText ("���H���ӱ��F...oTZ",16,0xff0000ff);
			
			pText->Show ();
			pBtn1->Show ();
			
			if(pBtn1->GetState ()==DefONMOUSEDOWN)
			{
				//gpMusic->Stop ();
				return DefMAINMENU;
			}
			else
				return (Def1PLAY+iPlay-1);
		}
		/*
		0->1
		1->2
		2->1
		1->0
		0->1
		*/
		i+=ip;
		if(i==iPlay)
		{
			i=iPlay-1;	
			ip=-1;
		}

		if(i==-1)
		{
			i=0;
			ip=1;
		}
		
		/*
		#define DefSNAKE_OK		0	//���`
		#define DefSNAKE_NOTAIL 1	//�S������
		#define DefSNAKE_DIE	2	//���`
		#define DefSNAKE_WAIT	3	//���ݤ����ʧ@
		*/
		switch(pCSnake[i].Activity ())
		{
		case DefSNAKE_OK://���ʧ���
			
			break;
		case DefSNAKE_NOTAIL:
			//�C�����~...�D���ڤ����F!?
			/*
				�o�O�ˬd�ΰT����Function���٨S�gXD"
			*/
			return DefQUIT;
			break;
		case DefSNAKE_DIE:
			//���`,�C���i�H�����F
			bGameOver=true;
			
			break;
		case DefSNAKE_WAIT://���ݤ�
			break;
		}
		
		
		if(!pCEgg->IsExist ())
		{
			pCEgg->ReBorn (RndGetEggType(),rand()% (pCGSW->miH * pCGSW->miW ) );	
		}

		
		return (Def1PLAY+iPlay-1);
	}
	bool Render(void)
	{
		if(!bInit)
			return false;
		gpGrp->Draw (0,0,gpTexM->GetTextureData (sNothing.GetBuffer ()),DefWINDOWWIDTH,DefWINDOWHEIGHT);
		int y,x;
		for(y=0;y<pCGSW->miH ;y++)
			for(x=0;x<pCGSW->miW ;x++)
				switch( pCGSW->penMap[y*pCGSW->miW +x])
				{
				case Nothing:
					//gotoxy(x+1,y+1);printf(" ");
					//gpGrp->Draw (x*20+1,y*20+1,gpTexM->GetTextureData (sNothing.GetBuffer ()));
					break;
				case Egg1:
					//gotoxy(x+1,y+1);printf("O");
					gpGrp->Draw (x*20,y*20,gpTexM->GetTextureData (sEgg1.GetBuffer ()));
					break;
				case Egg2:
					//gotoxy(x+1,y+1);printf("o");
					gpGrp->Draw (x*20,y*20,gpTexM->GetTextureData (sEgg2.GetBuffer ()));
					break;
				case Egg3:
					//gotoxy(x+1,y+1);printf("+");
					gpGrp->Draw (x*20,y*20,gpTexM->GetTextureData (sEgg3.GetBuffer ()));
					break;
				case Egg4:
					//gotoxy(x+1,y+1);printf("*");
					gpGrp->Draw (x*20,y*20,gpTexM->GetTextureData (sEgg4.GetBuffer ()));
					break;

				case Snake1:
					gpGrp->Draw (x*20,y*20,gpTexM->GetTextureData (sSnakeBody1.GetBuffer ()));
					break;
				case Snake2:
//					gotoxy(x+1,y+1);printf("#");
					gpGrp->Draw (x*20,y*20,gpTexM->GetTextureData (sSnakeBody2.GetBuffer ()));
					break;
				case Snake3:
					break;
				case Snake4:
					break;
				default :
					break;
		
		}
		
		if(pText->IsInit ())
			pText->Display ();
		if(pBtn1->IsInit ())
			pBtn1->Display ();		

		return true;
	}
	bool IsInit(void)
	{
		return bInit;
	}
	
	bool Init(void)
	{
		
		if(iPlay!=1 && iPlay!=2)
		{
			return false;
		}
		//��l�e�C��
		pCSnake=new GSnake[iPlay];//�D

		pCEgg=new GSEgg();//4���������J
		pCGSW=new GSWorld();//�@�ɤ@��XD"
	
		pCGSW->Init (40,30);
	
		for(int i=0;i<iPlay;i++)
		{
			pCSnake[i].Born ((enObjectType)(i+1) , DefGSNAKELENGTH,DefGSNAKESPEED,rand()% (pCGSW->miH * pCGSW->miW ) ,pCGSW);
		}
	
		pCEgg[0].Born (RndGetEggType() ,rand()% (pCGSW->miH * pCGSW->miW ) ,pCGSW);
		//�ϧθ��J
		gpTexM->Add (sSnakeHead1.GetBuffer (),DefCOLORKEY);	
		gpTexM->Add (sSnakeTail1.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sSnakeBody1.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sSnakeHead2.GetBuffer (),DefCOLORKEY);	
		gpTexM->Add (sSnakeTail2.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sSnakeBody2.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sEgg1.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sEgg2.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sEgg3.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sEgg4.GetBuffer (),DefCOLORKEY);
		gpTexM->Add (sNothing.GetBuffer (),DefCOLORKEY);

		int iWindowX=255,iWindowY=335;
		pText=new CGUIText();
		pText->Init (gpGrp,gpFontM,gpTexM,"",sText,iWindowX,iWindowY,280,120,25);
		pText->SetText ("���H���ӱ��F...oTZ",16,0xff0000ff);
		pText->Hide ();
		pBtn1=new CGUIButton();
		/*
		iWindowX+100iWindowY+95
		*/
		pBtn1->Init (gpGrp,gpFontM,gpTexM,"",sBtn1,sBtn2,sBtn3,iWindowX+210,iWindowY+95,42,20);
		pBtn1->Hide ();
		bInit=true;
		gpMPoint->Hide ();
		//gpMusic->LoadFile ("music/timeriver.mp3");
		//gpMusic->Play ();
		bGameOver=false;
		return true;
	}
	bool Init(int ip)
	{
		iPlay=ip;
		return Init();
	}
	void Release(void)
	{
		gpTexM->Del (sSnakeHead1.GetBuffer ());	
		gpTexM->Del (sSnakeTail1.GetBuffer ());
		gpTexM->Del (sSnakeBody1.GetBuffer ());
		gpTexM->Del (sEgg1.GetBuffer ());
		gpTexM->Del (sEgg2.GetBuffer ());
		gpTexM->Del (sEgg3.GetBuffer ());
		gpTexM->Del (sEgg4.GetBuffer ());
		gpTexM->Del (sNothing.GetBuffer ());
		pBtn1->Release ();
		pText->Release ();
		int i;
		for(i=0;i<iPlay;i++)
		{
			pCSnake[i].Destory ();
			
			//&pCSnake[i] =NULL;
		}
		pCGSW->Destory ();
		pCGSW=NULL;
		
		delete  pCEgg;
		pCEgg=NULL;
		
		
		
		bInit=false;
	}	
};


CGameBody *gpGB=NULL;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*
	�C���D�e�����O
*/

class CMainMenu :public IGameBase
{
private:
	JCString sBG;
	JCString sSMN;
	JCString sSMO;
	JCString sSMD;
	JCString sSMN2;
	JCString sSMO2;
	JCString sSMD2;
	JCString sEMN;
	JCString sEMO;
	JCString sEMD;
	bool bInit;
	CGUIButton *pBtn;
	CGUIButton *pBtn2;
	CGUIButton *pBtn3;
	
public:
	bool IsInit(void)
	{
		return bInit;
	}
	 CMainMenu()
	{
		//�I���W��
		sBG="img//title.bmp";
		sSMN="img//StartMN.bmp";
		sSMO="img//StartMO.bmp";
		sSMD="img//StartMN.bmp";
		sSMN2="img//StartMO2.bmp";
		sSMO2="img//StartMD2.bmp";
		sSMD2="img//StartMD2.bmp";
		sEMN="img//EndMN.bmp";
		sEMO="img//EndMO.bmp";
		sEMD="img//EndMD.bmp";
		bInit=false;
		pBtn=NULL;
		pBtn2=NULL;
		pBtn3=NULL;
	}
	bool Init(void)
	{
		pBtn=new CGUIButton();
		pBtn2=new CGUIButton();
		pBtn3=new CGUIButton();
		gpTexM->Add (sBG.GetBuffer () ,DefCOLORKEY);
		//gpTexM->Add (sSMN.GetBuffer () ,DefCOLORKEY);
		//gpTexM->Add (sSMO.GetBuffer () ,DefCOLORKEY);
		//gpTexM->Add (sSMD.GetBuffer () ,DefCOLORKEY);
		pBtn->Init (gpGrp,gpFontM,gpTexM,"",sSMN,sSMO,sSMD,200,300,200,50,DefCOLORKEY);
		pBtn->Show ();
		pBtn2->Init (gpGrp,gpFontM,gpTexM,"",sSMN2,sSMO2,sSMD2,200,350,200,50,DefCOLORKEY);
		pBtn2->Show ();
		pBtn3->Init (gpGrp,gpFontM,gpTexM,"",sEMN,sEMO,sEMD,200,400,200,50,DefCOLORKEY);
		pBtn3->Show ();
		//FORCESIII.mp3
	
		return (bInit=true);
	}
	int Action(void)
	{
		if(bInit)
		{
			/*
			#define DefONMOUSENORMAL 0
			#define DefONMOUSEMOVE 1
			#define DefONMOUSEDOWN 2
			*/
			if(pBtn->GetState ()==DefONMOUSEDOWN)
			{
	
				
				return Def1PLAY	;		
			}
			if(pBtn2->GetState ()==DefONMOUSEDOWN)
			{
	
				return Def2PLAY	;
			}
			if(pBtn3->GetState ()==DefONMOUSEDOWN)
			{
	
				return DefABOUT	;
			}
		}
		return DefMAINMENU;
	}
	bool Render(void)
	{
		if(!bInit)
			return false;
		gpGrp->Draw (0,0,gpTexM->GetTextureData (sBG.GetBuffer ())); 
		pBtn->Display ();
		pBtn2->Display ();
		pBtn3->Display ();
		return true;
	}
	bool GetMsg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if(bInit)
		{
			pBtn->GetWinMessage (hWnd,msg,wParam,lParam);
			pBtn2->GetWinMessage (hWnd,msg,wParam,lParam);
			pBtn3->GetWinMessage (hWnd,msg,wParam,lParam);
		}
		return true;
	}
	void Release(void)
	{
		gpTexM->Del (sBG.GetBuffer ());	
		//gpTexM->Del (sSMN.GetBuffer ());
		//gpTexM->Del (sSMO.GetBuffer ());
		//gpTexM->Del (sSMD.GetBuffer ());
		pBtn->Release ();
		
		pBtn2->Release ();
		pBtn3->Release ();

		pBtn=NULL;
		pBtn2=NULL;
		pBtn3=NULL;
		bInit=false;
		
	}
};

CMainMenu *gpMM=NULL;

/////////////////////////////////////////////////////////////////////////////

//�T���^�I
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(gpMPoint!=NULL)
		gpMPoint->GetWinMessage (hWnd,msg,wParam,lParam);

    switch(giGameSceneIdx)
	{
	case DefMAINMENU:
		if(gpMM!=NULL)
		{
			if(!gpMM->GetMsg (hWnd,msg,wParam,lParam))
				msg=WM_DESTROY;
		}
		break;
	case Def1PLAY:
	case Def2PLAY:
		if(gpGB!=NULL)
		{
			if(!gpGB->GetMsg (hWnd,msg,wParam,lParam))
				msg=WM_DESTROY;
		}
		break;
					
	}
	
	switch( msg )
    {
	case WM_MOUSEMOVE:
		/*
		xPos = GET_X_LPARAM(lParam); 
		yPos = GET_Y_LPARAM(lParam); 
		*/
		
		
		
		break;
    case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    };
	
    return DefWindowProc( hWnd, msg, wParam, lParam );
}


//�X�l�C��
bool InitGame(HWND hWnd)
{
	ShowCursor(DefSHOWSYSTEMMOUSEPOINT);
	gpGrp=new JCGraphics();	
	gpGrp->Init (hWnd,DefWINDOWWIDTH,DefWINDOWHEIGHT,DefIsFullScreen);
	gpTexM=new CTexManager();
	gpTexM->Init (gpGrp->pd3dDevice ,DefIMGAMOUNT);
	gpFontM=new CFontManager();
	gpFontM->Init (gpGrp->pd3dDevice ,DefIMGAMOUNT);
	gpMM=new CMainMenu();
	gpGB=new CGameBody();
	giSystemFont=gpFontM->Add ();
	
	gpMPoint=new CGUIMouse();
	if(gpMPoint->Init(gpGrp,gpTexM,1)  )
	{
		gpMPoint->Add("img/ma.txt",DefCOLORKEY);
		gpMPoint->Show ();
	}

	gpMusic=new JCMusic();
	gpMusic->Init ();

	return true;
}


//�e��ø�s
int Render(HWND hWnd)
{
	
	gpGrp->Clear ();
	gpGrp->Begin ();
	switch(giGameSceneIdx)
	{
	case DefMAINMENU:
		gpMM->Render ();
		break;
	case Def1PLAY:
	case Def2PLAY:
		gpGB->Render ();
		break;
					
	}
	gpMPoint->Display ();
	//gpFontM->Draw (giSystemFont);
	gpGrp->Render ();
	return 0;
}

void DestoryProject(void)
{
	 DefSafeRelease(gpGrp);
}


//�C���i�J�I
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      DefTHISCLASSNAME, NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( DefTHISCLASSNAME, DefMAINWINDOWNAME,
                              WS_OVERLAPPED, 0, 0, DefWINDOWWIDTH, DefWINDOWHEIGHT,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );
	// Enter the message loop
    MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	// Show the window
    ShowWindow( hWnd, SW_SHOWDEFAULT );
    UpdateWindow( hWnd );

	//�X�l�ƹC��
	if(!InitGame(hWnd))
	{		

		DestoryProject();
		return 0;
	}

	LARGE_INTEGER LintTC;	//�C��p�Ʀ���
	LARGE_INTEGER LintBegin;//�}�l�ֿn����
	LARGE_INTEGER LintEnd;	//�����ֿn����
	QueryPerformanceFrequency(&LintTC);//���o�C���W�v
	
	QueryPerformanceCounter(&LintBegin);//�X�l�ƶ}�l�ɶ�

	
    while( msg.message!=WM_QUIT )
    {
		//�T���j��
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

		switch(giGameSceneIdx)
		{
		case DefMAINMENU:
			if(gpMM->IsInit ())
			{
				giGameSceneIdx=gpMM->Action ();
				if(giGameSceneIdx!=DefMAINMENU)
					gpMM->Release ();
			}
			else
				gpMM->Init ();
			break;
		case Def1PLAY:
			if(gpGB->IsInit ())
			{
				giGameSceneIdx=gpGB->Action ();
				if(giGameSceneIdx!=Def1PLAY)
					gpGB->Release ();
			}
			else
				gpGB->Init (1);
			break;
		case Def2PLAY:
			if(gpGB->IsInit ())
			{
				giGameSceneIdx=gpGB->Action ();
				if(giGameSceneIdx!=Def2PLAY)
					gpGB->Release ();
			}
			else
				gpGB->Init (2);
			break;
		case DefABOUT:
			msg.message=WM_QUIT;
			break;
		case DefQUIT:
			break;
		}
		
		QueryPerformanceCounter(&LintEnd);
		

		if((LintEnd.QuadPart-LintBegin.QuadPart) >LintTC.QuadPart /DefFPS )
		{
			if(Render(hWnd)==0)//ø�s�e�� ��0�N���T����
			{
				///////////////
				//�p��FPS
				//char cFPS[17]={0};
				//int iCount;//�p��FPS
				//iCount=(int)LintTC.QuadPart/(LintEnd.QuadPart-LintBegin.QuadPart);
				//itoa(iCount,cFPS,10);
				//::SetWindowText (hWnd, cFPS);
				///////////////
				QueryPerformanceCounter(&LintBegin);
		
			}
			else
			{
				break;
			}
		}
		
			
		
        
    }
	// Clean up everything and exit the app
    
	UnregisterClass( DefTHISCLASSNAME, wc.hInstance );
	DestoryProject();
	return 0;
	
}





