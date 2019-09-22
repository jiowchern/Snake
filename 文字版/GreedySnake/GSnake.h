#pragma once
/*
	Programmer:Jiowchern Chen
	蛇的類別

*/
#include "GSWorld.h"
#include "..\..\mylib\base\jccounter.h"

#define DefSNAKEMAXSPEED	200
#define DefSNAKEMINSPEED	10

#define DefSNAKE_OK		0	//正常
#define DefSNAKE_NOTAIL 1	//沒有尾巴
#define DefSNAKE_DIE	2	//死亡
#define DefSNAKE_WAIT	3	//等待中不動作

typedef struct sSnakeBody
{
	enDirection enD;//方向
	int iLocation;//身體位置
	struct sSnakeBody *psNext;//下一個環節
	
} tsSnakeBody;

typedef tsSnakeBody* LPtsSnakeBody;

class GSnake
{
public:
	GSnake(void);
	~GSnake(void);
private:
	//
	JCCounter *pCCount;
	// 存活
	bool bSurvive;
	// 蛇的朝向方向
	enDirection menDirection;
	enDirection menTmpDirection;
	// 長度
	int iLength;
	// 速度,值越大越慢
	/*
		期望值定義:1=1ms
	*/
	int iSpeed;
	// 蛇的身體,紀錄實際的位置 (位置是編號)
	tsSnakeBody *ptsBody;

	/*
		因為蛇的身體本身不管增加或減少,
		都是從尾巴變化,
		所以直接紀錄其指標會比用搜尋來的省事...
	*/
	tsSnakeBody *ptsTail;//尾巴
	// 分數
	int iMark;
	// 飢餓程度...越高越餓
	int iHunger;
	//地圖指標
	GSWorld* pCMap;
	enObjectType enID;
	int miMapWidth;//地圖寬度
	int miMapHeight;//地圖高度
public:
	// 出生...初始化,out:成功 in1:長度,in2:速度,in3:出生位置,in4:世界指標,in5 地圖寬度
	bool Born(enObjectType enid,int iLen, int ispeed, int iLocation,GSWorld* pMap);
	// 吃東西.in:世界的位置
	void Eat(enum enObjectType enOTLocation);

	int GetMark(void){return iMark;}
	int GetLength(void){return iLength;}
	// 存活
	bool IsSurvive(void);
	// 活動::out 狀態訊息 0為正常
	int Activity();
	// 取得命令
	void GetCommand(enDirection enCmd);
	int GetSpeed(void);
};

