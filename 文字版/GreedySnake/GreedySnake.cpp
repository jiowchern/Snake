// GreedySnake.cpp : �w�q�D���x���ε{�����i�J�I�C
//
/*
	Programmer:Jiowchern Chen
	Project name:�g�Y�D
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
	���ϩw�q�ܼ�
*/
GSWorld *pCGSW;
std::vector<GSnake> Snakes;

GSEgg *pCEgg;
int giPlay=0;//���a�H��

/*
	����w�q
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

//�~....�~�M�o��·�XD"
void gotoxy(int x, int y) 
{ 
	COORD c; 
  
	c.X = x - 1; 
	c.Y = y - 1; 
 
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c); 
	
}

//�e��
int ShowTitle(void)
{
	system("cls");
	printf("Name:�g�Y�D\n");
	printf("Programmer:Jiowchern Chen\n");
	printf("�ާ@����:\n");
	printf("Player1:[Up] [Dowm] [Left] [Right] \n");
	printf("Player2:[w] [s] [a] [d] \n");
	printf("�п�J�H��(1~2�H):");
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
	//�e�u
	for(y=1;y<=DefSCREENHEIGHT;y++)
	{
		gotoxy(60,y);printf("|");
	}
	for(x=1;x<=80;x++)
	{
		gotoxy(x,DefSCREENHEIGHT+1);printf("-");
	}
	//��ܸ��

	
	for(int i=0,j=0;i<giPlay;i++,j+=8)
	{
		auto& snake = Snakes.at(i);
		gotoxy(61,1+j);printf("Player%d:",i+1);
		gotoxy(61,3+j);printf("����:%d ", snake.GetMark ());
		gotoxy(61,5+j);printf("����:%d ", snake.GetLength());
		gotoxy(61,7+j);printf("�t��:%d ", snake.GetSpeed ());
	}
	//Test
	//gotoxy(61,25);printf("�ɶ�:%d ",pCCount[0].);
	return 0;
}





//������R�O
int KB2Cmd(int iKB)
{
	
	
	//�B�n���S��r��
	if(iKB==DefSPECIALCHAR)
		iKB=_getch();
	switch (iKB)
	{
	case DefQUIT :
		//���}�C��
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
	//��l�e�C��
	
	

	pCEgg=new GSEgg();//4���������J
	pCGSW=new GSWorld();//�@�ɤ@��XD"
	
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
	//new�F����N�ӧR������
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

		//���ë���
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
			#define DefSNAKE_OK		0	//���`
			#define DefSNAKE_NOTAIL 1	//�S������
			#define DefSNAKE_DIE	2	//���`
			#define DefSNAKE_WAIT	3	//���ݤ����ʧ@
			*/
			switch(Snakes[idx].Activity())
			{
			case DefSNAKE_OK://���ʧ���
				
				break;
			case DefSNAKE_NOTAIL:
				//�C�����~...�D���ڤ����F!?
				/*
					�o�O�ˬd�ΰT����Function���٨S�gXD"
				*/
				iWhoDie= idx +1;
				break;
			case DefSNAKE_DIE:
				//���`,�C���i�H�����F
				iWhoDie= idx +1;
				break;
			case DefSNAKE_WAIT://���ݤ�
				break;
			}
			
			
			if(!pCEgg->IsExist ())
			{
				pCEgg->ReBorn (RndGetEggType(),rand()% (pCGSW->miH * pCGSW->miW ) );	
			}
			
			//DrawScreen
			if(Render()==0)//ø�s�e�� ��0�N���T����
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
		gotoxy(10,DefSCREENHEIGHT+2);printf("���a %d ���`...  ʨRZ\n",iWhoDie);
	}//if (initgame)

	system("PAUSE");
	return 0;
}

