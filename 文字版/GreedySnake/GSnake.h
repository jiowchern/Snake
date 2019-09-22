#pragma once
/*
	Programmer:Jiowchern Chen
	�D�����O

*/
#include "GSWorld.h"
#include "..\..\mylib\base\jccounter.h"

#define DefSNAKEMAXSPEED	200
#define DefSNAKEMINSPEED	10

#define DefSNAKE_OK		0	//���`
#define DefSNAKE_NOTAIL 1	//�S������
#define DefSNAKE_DIE	2	//���`
#define DefSNAKE_WAIT	3	//���ݤ����ʧ@

typedef struct sSnakeBody
{
	enDirection enD;//��V
	int iLocation;//�����m
	struct sSnakeBody *psNext;//�U�@�����`
	
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
	// �s��
	bool bSurvive;
	// �D���¦V��V
	enDirection menDirection;
	enDirection menTmpDirection;
	// ����
	int iLength;
	// �t��,�ȶV�j�V�C
	/*
		����ȩw�q:1=1ms
	*/
	int iSpeed;
	// �D������,������ڪ���m (��m�O�s��)
	tsSnakeBody *ptsBody;

	/*
		�]���D�����饻�����޼W�[�δ��,
		���O�q�����ܤ�,
		�ҥH������������з|��ηj�M�Ӫ��٨�...
	*/
	tsSnakeBody *ptsTail;//����
	// ����
	int iMark;
	// ���j�{��...�V���V�j
	int iHunger;
	//�a�ϫ���
	GSWorld* pCMap;
	enObjectType enID;
	int miMapWidth;//�a�ϼe��
	int miMapHeight;//�a�ϰ���
public:
	// �X��...��l��,out:���\ in1:����,in2:�t��,in3:�X�ͦ�m,in4:�@�ɫ���,in5 �a�ϼe��
	bool Born(enObjectType enid,int iLen, int ispeed, int iLocation,GSWorld* pMap);
	// �Y�F��.in:�@�ɪ���m
	void Eat(enum enObjectType enOTLocation);

	int GetMark(void){return iMark;}
	int GetLength(void){return iLength;}
	// �s��
	bool IsSurvive(void);
	// ����::out ���A�T�� 0�����`
	int Activity();
	// ���o�R�O
	void GetCommand(enDirection enCmd);
	int GetSpeed(void);
};

