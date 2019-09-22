
#include ".\guimouse.h"

CGUIMouse::CGUIMouse(void)
{
	
}

CGUIMouse::~CGUIMouse(void)
{
}
LONG CGUIMouse::OnMOUSEMOVE(HWND hWnd,UINT Msg,WPARAM wparam,LPARAM lparam)
{
	if(IsInit()&&bIsShow)
	{
		this->x =LOWORD(lparam);
		y=HIWORD(lparam);
	}
	return 0;
}