#pragma once

#include "guibase.h"
#include "..\..\Base\FileAccress.h"
/*

	�ƹ����йϧ�
*/
/*
	�w�q�@�ӷƹ����Ъ����c
*/
#include "Animate.h"


class CGUIMouse :
	public CAnimate
{
private:
	
	
public:
	virtual LONG OnMOUSEMOVE(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam);
	CGUIMouse(void);
	~CGUIMouse(void);
	
};
