
#ifndef DefJCCOUNTER 
#define DefJCCOUNTER 001
#define DefTIMESCALE	1000 //�C��ɶ����
#include <windows.h>
class JCCounter
{
private:
	//�]�w�p��
	LARGE_INTEGER LintTC;	//�C��p�Ʀ���
	LARGE_INTEGER LintBegin;//�}�l�ֿn����
	LARGE_INTEGER LintEnd;	//�����ֿn����
	bool bBegin;
	int iTimer;
public:

	JCCounter(void);
	~JCCounter(void);

	// �ǤJĲ�o�ɶ�,��쬰 1ms//�]�wĲ�o�ɶ�
	int SetTimer(int iTime);

	//�p�ɶ}�l
	// �}�l�p��
	int Begin(void);
	//�ˬd
	// �ˬd�ɶ�,�ɶ���۰ʰ���p�� out:�u�N��ɶ��� in:�W�L�h�֮ɶ�
	bool IsTimeUp(int* piOverTime);
};
#endif