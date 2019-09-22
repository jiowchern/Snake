// JCGraphics.h: interface for the JCGraphics class.
//
//////////////////////////////////////////////////////////////////////
/*
	Programmer:Jiowchern Chen
	程式目的:實作D3D轉成2D的介面程式

	更新日誌:
		2004/09/01 : 修改Draw方法,新增控制貼圖範圍
*/
#if !defined(AFX_JCGRAPHICS_H__243B6587_9C6B_4194_B192_FF339448A07D__INCLUDED_)
#define AFX_JCGRAPHICS_H__243B6587_9C6B_4194_B192_FF339448A07D__INCLUDED_

#if _MSC_VER > 1000
//#pragma once
#endif // _MSC_VER > 1000
#include <ocidl.h>
#include "..\BASED3D\JC_D3D.h"
#include "TexManager.h"
#define DefStringLen 255
#pragma comment (lib, "d3dx8.lib")
// Our custom FVF, which describes our custom vertex structure
#define DefD3DFVF D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1
// A structure for our custom vertex type. We added texture coordinates

struct D3DTO2DVERTEX
{
    float x,y,z;//畫面位置
	//float rhw;//rhw
	DWORD color;
	float u,v;//材質座標
	
} ;

//typedef *D3DTO2DVERTEX lpD3DTO2DVertex;
/*



*/
struct D3DTO2DFontStruct 
{
	DWORD dwFontColor;
	int iFontSize;
	int iFontWeight;
	char pcFontName[DefStringLen];
	int iShowTextPosX;
	int iShowTextPosY;
	char pcText[DefStringLen];

	LPD3DXFONT pFont;	
};//文字結構

class JCGraphics : public JC_D3D  
{
public:
	//Function

	//繪製函式 (遊戲畫面x,遊戲畫面y,圖形指標,透明度,指定大小寬,指定大小高,繪出的部分)
	bool Draw(int x,int y,SD8TextureData *pSD8Tex,int iDrawWidth=0 ,int iDrawHeight=0,RECT* prtDisplayRect =NULL,DWORD dwDiffuse=0xffffffff); 

	
	//bool Draw(int fx,int fy,LPDIRECT3DTEXTURE8 pSurface,int fWidth,int fHeight,DWORD iColorKey=0xffffffff,RECT rtDisplayRect = {0,0,0,0});//繪製函式(畫面位置x,y,材質指標,材質寬度,材質長度,透明,顯示的範圍)
	
	//bool Draw(int x,int y,SD8TextureData *pSD8Tex,RECT rtDisplayRect = {0,0,0,0} );//顯示位置x ,顯示位置y ,SD8TextureData* 圖形指標,顯示的範圍
	
	void MoveTo(int iX,int iY);

	bool DrawByPart(int fx, int fy,LPDIRECT3DTEXTURE8 pTexture,POINTF fptLU,POINTF fptRU,POINTF fptLD,POINTF fptRD,int fWidth,int fHeight,DWORD dwDiffuse);//繪製部分材質
	bool DrawRect(int fx,int fy,int fWidth,int fHeight, DWORD dwColor);//話框框
	Begin();
	bool bInitOK;
	bool SetText(int iWidth,int iHeight,int iWeight,char *pcFontName=NULL);
	bool SetText(D3DTO2DFontStruct* sFont);

	bool Text(char* pString,float fx,float fy,DWORD dwFontColor);
	bool Text(D3DTO2DFontStruct sFont);
	
	bool CreateTexture(LPDIRECT3DTEXTURE8 *pTexture,char* cFullFileName,DWORD iColorKey,int *piWidth=NULL,int *piHeight=NULL,int *piDepth=NULL);//建立圖形(材質指標,檔名,圖形寬=NULL為預型預設格式,圖形長,圖形色素)
	bool CreateTexture(LPDIRECT3DTEXTURE8 *pTexture,char* cFullFileName,DWORD iColorKey,D3DXIMAGE_INFO* pDImgInfo=NULL);//建立圖形(材質指標,檔名,圖形寬=NULL為預型預設格式,圖形長,圖形色素)
	void Clear(void);
	bool Init(HWND hWnd,int iw,int ih,bool bFullScreen=false);
	bool Draw(int fx,int fy,LPDIRECT3DTEXTURE8 pSurface,int fWidth,int fHeight,DWORD dwDiffuse=0xffffffff );//繪製函式(畫面位置,,材質指標,材質寬度,材質長度,透明)
	Release();
	
	SetupMatrices(float fw,float fh);
	Render();//繪製
	JCGraphics();
	virtual ~JCGraphics();
private:
	//Data
	int iFontWidth;
	int iFontHeight;
	int iFontWeight;
	char* pcFontName;

	float fWindowWidth; //視窗寬高
	float fWindowHeight;
	LPD3DXFONT pFont; //文字
	LPDIRECT3DVERTEXBUFFER8 pVB;//平面頂點
	
};

#endif // !defined(AFX_JCGRAPHICS_H__243B6587_9C6B_4194_B192_FF339448A07D__INCLUDED_)
