// JCGraphics.cpp: implementation of the JCGraphics class.
//
//////////////////////////////////////////////////////////////////////


#include "JCGraphics.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JCGraphics::JCGraphics()
{
	pFont=NULL;
	pVB=NULL;
	fWindowWidth=0.0f; 
	fWindowHeight=0.0f;
	bInitOK=false;
}

JCGraphics::~JCGraphics()
{
	Release();
}

JCGraphics::Render()
{
	if(pd3dDevice!=NULL)
	{
		pd3dDevice->EndScene();		
		pd3dDevice->Present( NULL, NULL, NULL, NULL );		
	}
	
}

JCGraphics::SetupMatrices(float WindowWidth, float WindowHeight)
{
	fWindowWidth=WindowWidth; 
	fWindowHeight=WindowHeight;
	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	D3DXMATRIX Ortho2D;	
	D3DXMATRIX Identity;
	
	D3DXMatrixOrthoLH(&Ortho2D, WindowWidth, WindowHeight, 0.0f, 1.0f);
	D3DXMatrixIdentity(&Identity);

	pd3dDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	pd3dDevice->SetTransform(D3DTS_WORLD, &Identity);
	pd3dDevice->SetTransform(D3DTS_VIEW, &Identity);

}

JCGraphics::Release()
{
	if(pVB!=NULL)
	{
		pVB->Release();
		pVB=NULL;
	}
	if(pFont!=NULL)
	{
		pFont->Release();
		pFont=NULL;
	}
	JC_D3D::Release ();
}

//繪製函式(畫面位置x,畫面位置y,材質指標,材質寬度,材質長度,擴散色..給預設值就好,)
bool JCGraphics::Draw(int fx, int fy,LPDIRECT3DTEXTURE8 pTexture,int fWidth,int fHeight,DWORD iColorKey)
{
	if(pVB==NULL)
		return false;
	if(!bInitOK	)
		return false;
	//座標轉換
	fx-=(int)(fWindowWidth/2.0);
	fy=(int)0.0f-fy;
	fy=(int)(fy-(fWindowHeight/2.0))+(fWindowHeight- fHeight);
	
	

	//fWidth-=fWindowWidth;
	//fHeight+=fWindowHeight;
	//設定平面座標
	D3DTO2DVERTEX* pVertices;
    
    if( FAILED( pVB->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
	{
        sErrMsg="頂點緩衝區pVB鎖定失敗\0";
		return false;
	}
	pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;
	pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = iColorKey;
	
	/*
	pVertices[0].x = pVertices[3].x = fx;
	pVertices[1].x = pVertices[2].x = fWidth;

	pVertices[0].y = pVertices[1].y = fHeight;
	pVertices[2].y = pVertices[3].y = fy;
	*/

	//指定圖形位置&長寬
	pVertices[3].x=fx;
	pVertices[3].y=fy;

	pVertices[2].x=fx+fWidth;
	pVertices[2].y=fy;

	pVertices[1].x=fx+fWidth;
	pVertices[1].y=fy+fHeight;

	pVertices[0].x=fx;
	pVertices[0].y=fy+fHeight;

	/*
	pVertices[0].u=0.0f;pVertices[0].v=1.0f;
	pVertices[1].u=1.0f;pVertices[1].v=1.0f;
	pVertices[2].u=1.0f;pVertices[2].v=0.0f;
	pVertices[3].u=0.0f;pVertices[3].v=0.0f;
	*/
	//綁上材質的範圍
	
	pVertices[1].u = pVertices[2].u = 1.0f;
	pVertices[0].u = pVertices[3].u = 0.0f;
	pVertices[0].v = pVertices[1].v = 0.0f;
	pVertices[2].v = pVertices[3].v = 1.0f;
	

	
	/*
	pVertices[0].u = 0.0f; pVertices[0].v = 0.0f; // 左上點
	pVertices[1].u = 1.0f; pVertices[1].v = 0.0f; //  
	pVertices[2].u = 1.0f; pVertices[2].v = 1.0f; //
	pVertices[3].u = 0.0f; pVertices[3].v = 1.0f; //
	*/

	pVB->Unlock();	

	
	pd3dDevice->SetTexture( 0, pTexture );//設定材質

	pd3dDevice->SetVertexShader( DefD3DFVF );//設定頂點緩衝格式
	pd3dDevice->SetStreamSource( 0, pVB, sizeof(D3DTO2DVERTEX) );//設定設定頂點緩衝
    
    pd3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 2 );//繪製多少頂點 單位:1三角形
//D3DPT_TRIANGLEFAN

	
	
	return true;
}

bool JCGraphics::Init(HWND hWnd,int iw,int ih,bool bFullScreen)
{
	if(JC_D3D::InitD3D (hWnd,bFullScreen,iw,ih))//如果父類別出始成功
	{
		//建立頂點緩衝區
		if( FAILED( pd3dDevice->CreateVertexBuffer( 4*sizeof(D3DTO2DVERTEX),
                                                  D3DUSAGE_WRITEONLY , DefD3DFVF,
                                                   D3DPOOL_MANAGED, &pVB ) ) )
		{
	        sErrMsg="頂點緩衝區pVB建立失敗\0";
			return false;
		}
		SetupMatrices ((float)iw,(float)ih);
		bInitOK=true;		

	}
	return true;
}

void JCGraphics::Clear()
{
	pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0L );
}

//建立圖形(材質指標,檔名,圖形寬=NULL為預型預設格式,圖形長,圖形色素)
bool JCGraphics::CreateTexture(LPDIRECT3DTEXTURE8 *pTexture, char *cFullFileName,DWORD iColorKey,int *piWidth,int *piHeight,int *piDepth)
{
	//如果此圖形已被使用則覆蓋更新
	if((*pTexture)!=NULL)
	{
		(*pTexture)->Release();
		(*pTexture)=NULL;
	}
	D3DXIMAGE_INFO srcinfo;
	if( FAILED(D3DXCreateTextureFromFileEx(pd3dDevice, cFullFileName, 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
                            D3DX_DEFAULT , iColorKey,&srcinfo, NULL, pTexture)) )
	{
		sErrMsg="材質載入失敗\0";
        return false;
	}
	if(piWidth!=NULL)
		*piWidth=srcinfo.Width;
	if(piHeight!=NULL)
		*piHeight=srcinfo.Height;
	if(piDepth!=NULL)
		*piDepth=srcinfo.Depth;
	

	return true;
}
bool JCGraphics::CreateTexture(LPDIRECT3DTEXTURE8 *pTexture, char *cFullFileName,DWORD iColorKey,D3DXIMAGE_INFO *pDImgInfo)
{
	//如果此圖形已被使用則覆蓋更新
	if((*pTexture)!=NULL)
	{
		(*pTexture)->Release();
		(*pTexture)=NULL;
	}
	D3DXIMAGE_INFO srcinfo;
	if( FAILED(D3DXCreateTextureFromFileEx(pd3dDevice, cFullFileName, 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
                            D3DX_DEFAULT , iColorKey,&srcinfo, NULL, pTexture)) )
	{
		sErrMsg="材質載入失敗\0";
        return false;
	}
	if(pDImgInfo!=NULL)//如果需要相關資訊
	{
		::memcpy (pDImgInfo,&srcinfo,sizeof(D3DXIMAGE_INFO));
	}
	return true;
}



bool JCGraphics::Text(char *pString, float fx, float fy,DWORD dwColor)
{
	if(pFont==NULL)
		return false;
	RECT rt;
	size_t strsize=strlen(pString) ;
	rt.top =(int)fy;
	rt.left =(int)fx;
	rt.right =(int)strsize*(iFontWidth+fx);
	rt.bottom =(int)iFontHeight;
	
	//pd3dDevice->BeginScene();
	pFont->Begin ();
	pFont->DrawText (pString,strsize,&rt,DT_LEFT,dwColor);
	pFont->End ();
	//pd3dDevice->EndScene();
	return true;
}

bool JCGraphics::Text(D3DTO2DFontStruct sFont)
{
	RECT rt;
	size_t strsize=strlen(sFont.pcText) ;
	rt.top =(int)sFont.iShowTextPosY ;
	rt.left =(int)sFont.iShowTextPosX ;
	rt.right =strsize*((sFont.iFontSize /2)+sFont.iShowTextPosX );
	rt.bottom =sFont.iFontSize ;
	
	//pd3dDevice->BeginScene();
	sFont.pFont->Begin ();
	sFont.pFont->DrawText (sFont.pcText ,strsize,&rt,DT_LEFT,sFont.dwFontColor );
	sFont.pFont->End ();
	//pd3dDevice->EndScene();
	return true;
}
bool JCGraphics::SetText(D3DTO2DFontStruct* sFont)
{
	if(sFont->pFont!=NULL)
	{
		sFont->pFont->Release();
		sFont->pFont=NULL;
	}
	HFONT hFont=NULL ;
	//LPD3DXFONT pFont2=NULL;
	hFont=CreateFont
	(
		sFont->iFontSize,	// logical height of font 
		sFont->iFontSize/2,	// logical average character width 
		GM_ADVANCED,	// angle of escapement 
		0,	// base-line orientation angle 
		sFont->iFontWeight,	// font weight 
		FALSE,	// italic attribute flag 
		FALSE,	// underline attribute flag 
		FALSE,	// strikeout attribute flag 
		DEFAULT_CHARSET,	// character set identifier 
		OUT_DEFAULT_PRECIS	,	// output precision 
		CLIP_DEFAULT_PRECIS	,	// clipping precision 
		DEFAULT_QUALITY	,	// output quality 
		DEFAULT_PITCH,	// pitch and family 
		sFont->pcFontName	// pointer to typeface name string 
	);
	
	if( FAILED(D3DXCreateFont(pd3dDevice,hFont,&sFont->pFont)))
	{
		sErrMsg="Font建立失敗\0";
		return false;
	}
	//sFont->pFont= pFont2;
	return true;
}
bool JCGraphics::SetText(int iWidth, int iHeight, int iWeight,char *pcFontName)
{
	if(pFont!=NULL)
	{
		pFont->Release();
		pFont=NULL;
	}
	HFONT hFont ;
	iFontWidth=iWidth;
	iFontHeight=iHeight;
	iFontWeight=iWeight;

	hFont=CreateFont
	(
		iHeight,	// logical height of font 
		iWidth,	// logical average character width 
		GM_ADVANCED,	// angle of escapement 
		0,	// base-line orientation angle 
		iWeight,	// font weight 
		FALSE,	// italic attribute flag 
		FALSE,	// underline attribute flag 
		FALSE,	// strikeout attribute flag 
		DEFAULT_CHARSET,	// character set identifier 
		OUT_DEFAULT_PRECIS	,	// output precision 
		CLIP_DEFAULT_PRECIS	,	// clipping precision 
		DEFAULT_QUALITY	,	// output quality 
		DEFAULT_PITCH,	// pitch and family 
		pcFontName	// pointer to typeface name string 
	);

	if( FAILED(D3DXCreateFont(pd3dDevice,hFont,&pFont)))
	{
		sErrMsg="Font建立失敗\0";
		return false;
	}
	return true;
}



JCGraphics::Begin()
{
	if(pd3dDevice!=NULL)
		pd3dDevice->BeginScene();
}

bool JCGraphics::DrawRect(int fx,int fy,int fWidth,int fHeight, DWORD dwColor)
{
	if(!bInitOK	)
		return false;
	fx-=(int)(fWindowWidth/2.0);
	fy=(int)0.0f-fy;
	fy=(int)(fy-(fWindowHeight/2.0))+(fWindowHeight- fHeight);
	
	
	//fWidth-=fWindowWidth;
	//fHeight+=fWindowHeight;
	//設定平面座標
	D3DTO2DVERTEX* pVertices;
    
    if( FAILED( pVB->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
	{
        sErrMsg="頂點緩衝區pVB鎖定失敗\0";
		return false;
	}
	pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;
	pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = dwColor;
	
	/*pVertices[0].x = pVertices[3].x = fx;
	pVertices[1].x = pVertices[2].x = fWidth;

	pVertices[0].y = pVertices[1].y = fHeight;
	pVertices[2].y = pVertices[3].y = fy;*/
	
	pVertices[3].x=(float)fx;
	pVertices[3].y=(float)fy;

	pVertices[2].x=(float)fx+fWidth;
	pVertices[2].y=(float)fy;

	pVertices[1].x=(float)fx+fWidth;
	pVertices[1].y=(float)fy+fHeight;

	pVertices[0].x=(float)fx;
	pVertices[0].y=(float)fy+fHeight;


	
	
	pVertices[1].u = pVertices[2].u = 1.0f;
	pVertices[0].u = pVertices[3].u = 0.0f;
	pVertices[0].v = pVertices[1].v = 0.0f;
	pVertices[2].v = pVertices[3].v = 1.0f;

	
	pVB->Unlock();	

	
	pd3dDevice->SetTexture( 0, NULL );//設定材質

	pd3dDevice->SetVertexShader( DefD3DFVF );//設定頂點緩衝格式
	pd3dDevice->SetStreamSource( 0, pVB, sizeof(D3DTO2DVERTEX) );//設定設定頂點緩衝
    
    pd3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 2 );//繪製多少頂點 單位:1三角形
//D3DPT_TRIANGLEFAN

	
	
	return true;
}

bool JCGraphics::DrawByPart(int fx, int fy,LPDIRECT3DTEXTURE8 pTexture,POINTF fptLU,POINTF fptRU,POINTF fptLD,POINTF fptRD,int fWidth,int fHeight,DWORD iColorKey)
{
	if(pVB==NULL)
		return false;
	if(!bInitOK	)
		return false;
	//象限轉換 
	fx-=(int)(fWindowWidth/2.0);
	fy=(int)0.0f-fy;
	fy=(int)(fy-(fWindowHeight/2.0))+(fWindowHeight- fHeight);
	/*
	if(fx>=(fWindowWidth/2))
		fx-=(fWindowWidth/2);
	else
		fx+=(fWindowWidth/2);

	if(fy>=(fWindowHeight/2))
		fy-=(fWindowHeight/2);
	else
		fy+=(fWindowHeight/2);
	*/
	//fWidth-=fWindowWidth;
	//fHeight+=fWindowHeight;
	//設定平面座標
	D3DTO2DVERTEX* pVertices;
    
    if( FAILED( pVB->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
	{
        sErrMsg="頂點緩衝區pVB鎖定失敗\0";
		return false;
	}
	pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;
	pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = iColorKey;
	
	/*pVertices[0].x = pVertices[3].x = fx;
	pVertices[1].x = pVertices[2].x = fWidth;

	pVertices[0].y = pVertices[1].y = fHeight;
	pVertices[2].y = pVertices[3].y = fy;*/
	
	pVertices[3].x=(float)fx;
	pVertices[3].y=(float)fy;

	pVertices[2].x=(float)fx+fWidth;
	pVertices[2].y=(float)fy;

	pVertices[1].x=(float)fx+fWidth;
	pVertices[1].y=(float)fy+fHeight;

	pVertices[0].x=(float)fx;
	pVertices[0].y=(float)fy+fHeight;

	pVertices[0].u=(float)fptLU.x;
	pVertices[0].v=(float)fptLU.y; 

	pVertices[1].u=(float)fptRU.x;
	pVertices[1].v=(float)fptRU.y;

	pVertices[2].u=(float)fptRD.x;
	pVertices[2].v=(float)fptRD.y;

	pVertices[3].u=(float)fptLD.x;
	pVertices[3].v=(float)fptLD.y;
	
/*	pVertices[1].u = pVertices[2].u = 0.5f;
	pVertices[0].u = pVertices[3].u = 0.0f;
	pVertices[0].v = pVertices[1].v = 0.0f;
	pVertices[2].v = pVertices[3].v = 0.5f;*/

	
	pVB->Unlock();	

	
	pd3dDevice->SetTexture( 0, pTexture );//設定材質

	pd3dDevice->SetVertexShader( DefD3DFVF );//設定頂點緩衝格式
	pd3dDevice->SetStreamSource( 0, pVB, sizeof(D3DTO2DVERTEX) );//設定頂點緩衝
    
    pd3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 2 );//繪製多少頂點 單位:1三角形
//D3DPT_TRIANGLEFAN

	
	
	return true;
}



void JCGraphics::MoveTo(int iX, int iY)
{
	//象限轉換 
	//iX-=(fWindowWidth/2);
	//iY=0-iY;
	//iY=(iY-(fWindowHeight/2));
	D3DXMATRIX Position;
	D3DXMatrixTranslation(&Position, (float)iX, (float)iY, 0.0f);
	pd3dDevice->SetTransform(D3DTS_WORLD, &Position);
}

//繪製函式(畫面位置x,畫面位置y,_SD8TextureData的指標,指定大小寬,指定大小高,繪出的部分,擴散社)
bool JCGraphics::Draw(int x,int y,SD8TextureData *pSD8Tex,int iDrawWidth ,int iDrawHeight,RECT* prtDisplayRect,DWORD dwDiffuse )
{

	if(pSD8Tex!=NULL&&pSD8Tex->IsUsed)
	{
		int *piTmpWidth=NULL;
		int *piTmpHeight=NULL;
		if(iDrawWidth!=0)
			piTmpWidth= &iDrawWidth;
		else
			piTmpWidth= (int*)&pSD8Tex->info.Width;

		if(iDrawHeight!=0)
			piTmpHeight= &iDrawHeight;
		else
			piTmpHeight=(int*) &pSD8Tex->info.Height;

		if(prtDisplayRect!=NULL)
		{
			//有指定繪製區域
			//左上角座標比例
			POINTF fptLU;
			fptLU.x =(float)prtDisplayRect->left/pSD8Tex->info .Width;
			fptLU.y =(float)prtDisplayRect->top /pSD8Tex->info .Height;
			
			//右上角座標比例
			POINTF fptRU;
			fptRU.x =(float)(prtDisplayRect->right+prtDisplayRect->left)/pSD8Tex->info .Width;
			fptRU.y =(float)prtDisplayRect->top /pSD8Tex->info .Height;
			//左下角座標比例
			POINTF fptLD;
			fptLD.x =(float)prtDisplayRect->left/pSD8Tex->info .Width;
			fptLD.y =(float)(prtDisplayRect->bottom +prtDisplayRect->top )/pSD8Tex->info .Height ;
			//右下角座標比例

			POINTF fptRD;
			fptRD.x =(float)(prtDisplayRect->right+prtDisplayRect->left)/pSD8Tex->info .Width;
			fptRD.y =(float)(prtDisplayRect->bottom +prtDisplayRect->top )/pSD8Tex->info .Height ;
			return DrawByPart(x,y,pSD8Tex->pTex ,fptLU,fptRU,fptLD,fptRD,*piTmpWidth,*piTmpHeight,dwDiffuse);
		}

		return Draw(x,y,pSD8Tex->pTex,*piTmpWidth,*piTmpHeight,dwDiffuse);
	}
	return false;
}
