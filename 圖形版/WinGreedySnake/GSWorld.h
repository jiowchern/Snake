#pragma once
/*
	�g�Y�D���@��
*/
enum enDirection
{
	No ,	//�S��V
	Up,	//�W
	Down,	//�U
	Left ,	//��	
	Right	//�k
};
enum enObjectType
{
	Nothing,//�ť�
	Snake1,
	Snake2,
	Snake3,
	Snake4,
	Egg1,
	Egg2,
	Egg3,
	Egg4,
	RingOut //���
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
	GSWorld *mpCMap;//�a�ϫ���
	enObjectType enType;//����
	int miLocation;//�s�b��m
	bool IsExist(void);
	bool Born(enObjectType entype,int ilocation,GSWorld *pcmap);
	bool ReBorn(enObjectType entype,int ilocation);
};