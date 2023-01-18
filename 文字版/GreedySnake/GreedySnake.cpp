// GreedySnake.cpp : 定義主控台應用程式的進入點。
//
/*
	Programmer:Jiowchern Chen
	Project name:貪吃蛇
*/
#include "stdafx.h"
#include "GSnake.h"
#include <time.h>
#include <vector>

//SystemDefine
#define DefGSNAKELENGTH	20
#define DefGSNAKESPEED	200
#define DefSCREENHEIGHT 20

/*
	全區定義變數
*/
GSWorld *pCGSW;
std::vector<GSnake> Snakes;

GSEgg *pCEgg;
int giPlay=0;//玩家人數

/*
	按鍵定義
*/
#define DefPLAY1UP		72
#define DefPLAY1DOWN	80
#define DefPLAY1LEFT	75
#define DefPLAY1RIGHT	77
#define DefPLAY2UP		'w'
#define DefPLAY2DOWN	's'
#define DefPLAY2LEFT	'a'
#define DefPLAY2RIGHT	'd'
#define DefQUIT			27
#define DefSPECIALCHAR	224

//居....居然這麼麻煩XD"
void gotoxy(int x, int y) 
{ 
	COORD c; 
  
	c.X = x - 1; 
	c.Y = y - 1; 
 
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c); 
	
}

//畫面
int ShowTitle(void)
{
	system("cls");
	printf("Name:貪吃蛇\n");
	printf("Programmer:Jiowchern Chen\n");
	printf("操作說明:\n");
	printf("Player1:[Up] [Dowm] [Left] [Right] \n");
	printf("Player2:[w] [s] [a] [d] \n");
	printf("請輸入人數(1~2人):");
	scanf("%d",&giPlay);
	return 0;
}
int Render(void)
{
	int y,x;
	for(y=0;y<pCGSW->miH ;y++)
		for(x=0;x<pCGSW->miW ;x++)
		switch( pCGSW->penMap[y*pCGSW->miW +x])
		{
		case Nothing:

			gotoxy(x+1,y+1);printf(" ");
			break;
		case Egg1:
			gotoxy(x+1,y+1);printf("O");
			break;
		case Egg2:
			gotoxy(x+1,y+1);printf("o");
			break;
		case Egg3:
			gotoxy(x+1,y+1);printf("+");
			break;
		case Egg4:
			gotoxy(x+1,y+1);printf("*");
			break;

		case Snake1:
			gotoxy(x+1,y+1);printf("X");
			break;
		case Snake2:
			gotoxy(x+1,y+1);printf("#");
			break;
		case Snake3:
			break;
		case Snake4:
			break;
		default :
			break;
		}
	//DrawTable
	//畫線
	for(y=1;y<=DefSCREENHEIGHT;y++)
	{
		gotoxy(60,y);printf("|");
	}
	for(x=1;x<=80;x++)
	{
		gotoxy(x,DefSCREENHEIGHT+1);printf("-");
	}
	//顯示資料

	
	for(int i=0,j=0;i<giPlay;i++,j+=8)
	{
		auto& snake = Snakes.at(i);
		gotoxy(61,1+j);printf("Player%d:",i+1);
		gotoxy(61,3+j);printf("分數:%d ", snake.GetMark ());
		gotoxy(61,5+j);printf("長度:%d ", snake.GetLength());
		gotoxy(61,7+j);printf("速度:%d ", snake.GetSpeed ());
	}
	//Test
	//gotoxy(61,25);printf("時間:%d ",pCCount[0].);
	return 0;
}





//按鍵轉命令
int KB2Cmd(int iKB)
{
	
	
	//遮罩掉特殊字元
	if(iKB==DefSPECIALCHAR)
		iKB=_getch();
	switch (iKB)
	{
	case DefQUIT :
		//離開遊戲
		return 1;
		break;
	

	
	}
	if (Snakes.size() > 0)
	{
		auto& snake = Snakes.at(0);
		switch (iKB)
		{
		case DefPLAY1UP:
			snake.GetCommand(Up);
			break;
		case DefPLAY1DOWN:
			snake.GetCommand(Down);
			break;
		case DefPLAY1LEFT:
			snake.GetCommand(Left);
			break;
		case DefPLAY1RIGHT:
			snake.GetCommand(Right);
			break;
		}
	}
	if (Snakes.size() > 1)
	{
		auto& snake = Snakes.at(1);

		switch (iKB)
		{
		case DefPLAY2UP:
			snake.GetCommand(Up);
			break;
		case DefPLAY2DOWN:
			snake.GetCommand(Down);
			break;
		case DefPLAY2LEFT:
			snake.GetCommand(Left);
			break;
		case DefPLAY2RIGHT:
			snake.GetCommand(Right);
			break;
		}
	}
	return 0;

}
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
	//gotoxy(61,25);printf("Test1:%d ",iVal);
	return entype;
}

int InitGame(int iPlay)
{
	if(iPlay!=1 && iPlay!=2)
	{
		return 1;
	}
	//初始畫遊戲
	
	

	pCEgg=new GSEgg();//4個類型的蛋
	pCGSW=new GSWorld();//世界一個XD"
	
	pCGSW->Init (59,DefSCREENHEIGHT);
	
	for(int i=0;i<giPlay;i++)
	{
		GSnake snake;
		snake.Born((enObjectType)(i + 1), DefGSNAKELENGTH, DefGSNAKESPEED, rand() % (pCGSW->miH * pCGSW->miW), pCGSW);
		Snakes.push_back(snake);

		
	}
	
	pCEgg[0].Born (RndGetEggType() ,rand()% (pCGSW->miH * pCGSW->miW ) ,pCGSW);
	

	return 0;
}

void DestoryProject()
{
	//new了什麼就該刪除什麼
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand( (unsigned)time( NULL ) );
	//Show Title

	ShowTitle();

	//InitGame
	if(!InitGame(giPlay))
	{
		

		//Game Loop

		//隱藏指標
		CONSOLE_CURSOR_INFO cur;
		cur.bVisible =false;
		cur.dwSize =15;
		SetConsoleCursorInfo (GetStdHandle(STD_OUTPUT_HANDLE),&cur);

		
		int idx = 0;
		
		int iWhoDie=0;
		
		while(iWhoDie==0)
		{
			
			

			//GetKey
			if(kbhit() )
			{
				if(KB2Cmd( _getch()))
				break;
			}			

			/*
			#define DefSNAKE_OK		0	//正常
			#define DefSNAKE_NOTAIL 1	//沒有尾巴
			#define DefSNAKE_DIE	2	//死亡
			#define DefSNAKE_WAIT	3	//等待中不動作
			*/
			switch(Snakes[idx].Activity())
			{
			case DefSNAKE_OK://移動完畢
				
				break;
			case DefSNAKE_NOTAIL:
				//遊戲錯誤...蛇尾巴不見了!?
				/*
					這是檢查用訊息期Function我還沒寫XD"
				*/
				iWhoDie= idx +1;
				break;
			case DefSNAKE_DIE:
				//死亡,遊戲可以結束了
				iWhoDie= idx +1;
				break;
			case DefSNAKE_WAIT://等待中
				break;
			}
			
			
			if(!pCEgg->IsExist ())
			{
				pCEgg->ReBorn (RndGetEggType(),rand()% (pCGSW->miH * pCGSW->miW ) );	
			}
			
			//DrawScreen
			if(Render()==0)//繪製畫面 為0代表正確執行
			{
		
			}
			else
			{
				DestoryProject();
				return 0;
			}

			
			if (++idx >= giPlay)
				idx = 0;
		} //while
		//system("PAUSE");
		cur.bVisible =true;
		cur.dwSize =15;
		SetConsoleCursorInfo (GetStdHandle(STD_OUTPUT_HANDLE),&cur);

		//GameOver
		gotoxy(10,DefSCREENHEIGHT+2);printf("玩家 %d 死亡...  囧RZ\n",iWhoDie);
	}//if (initgame)

	system("PAUSE");
	return 0;
}

