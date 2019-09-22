// JC_D3D.h: interface for the JC_D3D class.
//
//////////////////////////////////////////////////////////////////////
/*
	Programmer:Jiowchern Chen
	目標:實作Direct3D Class
	Update:
		2003/03/12 : 開始建立
		2003/03/24 : ViewPort Create OK
		2003/07/23 : 全螢幕設定
		2003/08/06 : 程式碼加強
	UseLib:
		d3d8.lib
*/
#if !defined(AFX_JC_D3D_H__A538D617_3C0A_4916_A82E_B6C70A3E2C7A__INCLUDED_)
#define AFX_JC_D3D_H__A538D617_3C0A_4916_A82E_B6C70A3E2C7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3dx8.h>
#include <d3d8.h>
#pragma comment (lib, "d3d8.lib")

//#include <mmsystem.h>
#define DEF_ERRMSGSIZE 256

class JC_D3D    
{

public:
	
	virtual  Render();//繪置
	void Release(void);
	
	bool InitD3D(HWND,bool bFullScreen=false,int iw=640,int ih=480);//初始化D3D
	//攝影機andViewPort
	virtual  SetupMatrices();
	void SetViewPort(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight,float fMinZ,float fMaxZ);
	//設定打光
	
	
	
	/*
		//模組控制原件	
	*/

	
	JC_D3D();
	virtual ~JC_D3D();

	char *sErrMsg;
	LPDIRECT3DDEVICE8 pd3dDevice;
private:
	LPDIRECT3D8 pD3D;
	bool iInitOK;
	
};

#endif // !defined(AFX_JC_D3D_H__A538D617_3C0A_4916_A82E_B6C70A3E2C7A__INCLUDED_)
