#pragma once

#include "guibase.h"
#include "..\..\Base\FileAccress.h"
/*

	滑鼠指標圖形
*/
/*
	定義一個滑鼠指標的結構
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
