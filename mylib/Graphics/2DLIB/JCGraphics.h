// JCGraphics.h: interface for the JCGraphics class.
//
//////////////////////////////////////////////////////////////////////
/*
	Programmer:Jiowchern Chen
	�{���ت�:��@D3D�ন2D�������{��

	��s��x:
		2004/09/01 : �ק�Draw��k,�s�W����K�Ͻd��
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
    float x,y,z;//�e����m
	//float rhw;//rhw
	DWORD color;
	float u,v;//����y��
	
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
};//��r���c

class JCGraphics : public JC_D3D  
{
public:
	//Function

	//ø�s�禡 (�C���e��x,�C���e��y,�ϧΫ���,�z����,���w�j�p�e,���w�j�p��,ø�X������)
	bool Draw(int x,int y,SD8TextureData *pSD8Tex,int iDrawWidth=0 ,int iDrawHeight=0,RECT* prtDisplayRect =NULL,DWORD dwDiffuse=0xffffffff); 

	
	//bool Draw(int fx,int fy,LPDIRECT3DTEXTURE8 pSurface,int fWidth,int fHeight,DWORD iColorKey=0xffffffff,RECT rtDisplayRect = {0,0,0,0});//ø�s�禡(�e����mx,y,�������,����e��,�������,�z��,��ܪ��d��)
	
	//bool Draw(int x,int y,SD8TextureData *pSD8Tex,RECT rtDisplayRect = {0,0,0,0} );//��ܦ�mx ,��ܦ�my ,SD8TextureData* �ϧΫ���,��ܪ��d��
	
	void MoveTo(int iX,int iY);

	bool DrawByPart(int fx, int fy,LPDIRECT3DTEXTURE8 pTexture,POINTF fptLU,POINTF fptRU,POINTF fptLD,POINTF fptRD,int fWidth,int fHeight,DWORD dwDiffuse);//ø�s��������
	bool DrawRect(int fx,int fy,int fWidth,int fHeight, DWORD dwColor);//�ܮخ�
	Begin();
	bool bInitOK;
	bool SetText(int iWidth,int iHeight,int iWeight,char *pcFontName=NULL);
	bool SetText(D3DTO2DFontStruct* sFont);

	bool Text(char* pString,float fx,float fy,DWORD dwFontColor);
	bool Text(D3DTO2DFontStruct sFont);
	
	bool CreateTexture(LPDIRECT3DTEXTURE8 *pTexture,char* cFullFileName,DWORD iColorKey,int *piWidth=NULL,int *piHeight=NULL,int *piDepth=NULL);//�إ߹ϧ�(�������,�ɦW,�ϧμe=NULL���w���w�]�榡,�ϧΪ�,�ϧΦ��)
	bool CreateTexture(LPDIRECT3DTEXTURE8 *pTexture,char* cFullFileName,DWORD iColorKey,D3DXIMAGE_INFO* pDImgInfo=NULL);//�إ߹ϧ�(�������,�ɦW,�ϧμe=NULL���w���w�]�榡,�ϧΪ�,�ϧΦ��)
	void Clear(void);
	bool Init(HWND hWnd,int iw,int ih,bool bFullScreen=false);
	bool Draw(int fx,int fy,LPDIRECT3DTEXTURE8 pSurface,int fWidth,int fHeight,DWORD dwDiffuse=0xffffffff );//ø�s�禡(�e����m,,�������,����e��,�������,�z��)
	Release();
	
	SetupMatrices(float fw,float fh);
	Render();//ø�s
	JCGraphics();
	virtual ~JCGraphics();
private:
	//Data
	int iFontWidth;
	int iFontHeight;
	int iFontWeight;
	char* pcFontName;

	float fWindowWidth; //�����e��
	float fWindowHeight;
	LPD3DXFONT pFont; //��r
	LPDIRECT3DVERTEXBUFFER8 pVB;//�������I
	
};

#endif // !defined(AFX_JCGRAPHICS_H__243B6587_9C6B_4194_B192_FF339448A07D__INCLUDED_)
