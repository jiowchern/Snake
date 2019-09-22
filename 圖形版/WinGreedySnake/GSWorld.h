#pragma once
/*
	貪吃蛇的世界
*/
enum enDirection
{
	No ,	//沒方向
	Up,	//上
	Down,	//下
	Left ,	//左	
	Right	//右
};
enum enObjectType
{
	Nothing,//空白
	Snake1,
	Snake2,
	Snake3,
	Snake4,
	Egg1,
	Egg2,
	Egg3,
	Egg4,
	RingOut //邊界
};


class GSWorld
{
private:
	
public:
	enObjectType *penMap;
	int miW;
	int miH;
	GSWorld(void);
	~GSWorld(void);
	bool Init(int iWidth, int iHeight);
	void Destory(void);
};


class GSEgg
{
public:
	GSEgg(void);
	~GSEgg(void);
	GSWorld *mpCMap;//地圖指標
	enObjectType enType;//類型
	int miLocation;//存在位置
	bool IsExist(void);
	bool Born(enObjectType entype,int ilocation,GSWorld *pcmap);
	bool ReBorn(enObjectType entype,int ilocation);
};