// JC_D3D.cpp: implementation of the JC_D3D class.
//
//////////////////////////////////////////////////////////////////////


#include "JC_D3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


JC_D3D::JC_D3D()
{
	iInitOK=false;
	sErrMsg=new char[DEF_ERRMSGSIZE];
	::memset(sErrMsg,0,DEF_ERRMSGSIZE);
}

JC_D3D::~JC_D3D()
{
	//Release();
}
void JC_D3D::SetViewPort(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight,float fMinZ,float fMaxZ)
{
	if(iInitOK)
	{
		D3DVIEWPORT8 d3dVp8;
		::memset(&d3dVp8,0,sizeof(D3DVIEWPORT8));
		d3dVp8.X=dwX;
		d3dVp8.Y=dwY;
	
		d3dVp8.Width=dwWidth;
		d3dVp8.Height=dwHeight;
		d3dVp8.MinZ=fMinZ;
		d3dVp8.MaxZ=fMaxZ;
		pd3dDevice->SetViewport(&d3dVp8);
	}
}

bool JC_D3D::InitD3D(HWND hWnd,bool bFullScreen,int iw,int ih)
{

	if(iInitOK)
	{
		sErrMsg="已經出始化\0";
		return false;		
	}
	// Create the D3D object.
	//建立D3D物件
    if( NULL == ( pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
	{
		sErrMsg="D3D Object建立失敗\0";
        return false;
	}

    // Get the current desktop display mode, so we can set up a back
    // buffer of the same format
	//取得顯示模式 
    D3DDISPLAYMODE d3ddm;
    if( FAILED( pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		sErrMsg="pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ,顯示模式失敗\0";
        return false;
	}

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	if(bFullScreen)
	{
		d3dpp.Windowed=FALSE; 
		d3dpp.BackBufferCount=1; //全螢幕時設 
		d3dpp.BackBufferWidth=iw; //全螢幕時設 
		d3dpp.BackBufferHeight=ih;//全螢幕時設
	}
	else
	{
		d3dpp.Windowed = TRUE;
	}
    
	
	
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
    //d3dpp.EnableAutoDepthStencil = TRUE;
    //d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT //主要顯示卡
								  , D3DDEVTYPE_HAL //取得硬體抽象層裝置類型
								  , hWnd //所要顯示的介面handle
								  , D3DCREATE_SOFTWARE_VERTEXPROCESSING
								  , &d3dpp
								  , &pd3dDevice ) ) )
    {
		sErrMsg="pD3D->CreateDevice建立失敗\0";
        return false;
    }

	// Turn off D3D lighting 預設為不打光源
    //pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	iInitOK=true;
	return true;
}

void JC_D3D::Release()
{
	if( pd3dDevice != NULL )
	{
        pd3dDevice->Release();
		pd3dDevice=NULL;
	}

    if( pD3D != NULL )
	{
        pD3D->Release();
		pD3D=NULL;
	}
}

JC_D3D::Render()
{
	if(iInitOK)
	{
		pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0L );
		pd3dDevice->Present( NULL, NULL, NULL, NULL );
	}
}

JC_D3D::SetupMatrices()
{
	if(iInitOK)
	{

	}
}
