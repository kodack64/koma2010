#include	"graph.h"

Graph::Graph():
mybitmap(NULL),
col_blue(1.0),
col_red(1.0),
col_green(1.0),
col_light(1.0)
{
}

Graph::~Graph()
{
	RELEASE(mybitmap);
}

bool Graph::LoadGraphFile(const char *dir,LPDIRECT3DDEVICE8 lpD3DDEV,bool colorkey,int r,int g,int b)
{
	if(colorkey==true)
	{
		D3DXCreateTextureFromFileEx(lpD3DDEV,dir,0,0,0,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_ARGB(255, r, g, b),NULL,NULL,&mybitmap);
	}
	else
	{
		D3DXCreateTextureFromFileEx(lpD3DDEV,dir,0,0,0,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,0,NULL,NULL,&mybitmap);
	}
	if(mybitmap==NULL)
	{
		return false;
	}
	mybitmap->GetLevelDesc(0, &desc);

	width = desc.Width;
	height = desc.Height;

	return true;
}

LPDIRECT3DTEXTURE8	Graph::GetBitMap()
{
	return mybitmap;
}
