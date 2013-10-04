#include	"dx8.h"

void CDirectX::DrawBegin()
{
	// シーン開始
	lpD3DDEV->BeginScene();
	SetSlideDrawScreenCenter(0,0);
}

void CDirectX::DrawEnd()
{
	// シーン終了
	lpD3DDEV->EndScene();
	// バックバッファをプライマリバッファにコピー
	if (FAILED(lpD3DDEV->Present(NULL,NULL,NULL,NULL)))
	{
		lpD3DDEV->Reset(&param);
	}
}

void CDirectX::DrawString(char *str,int x,int y)
{
	RECT rc;
	rc.bottom = 100 ;
	rc.left = x ;
	rc.right = 100 ;
	rc.top = y ;
	lpFont->DrawTextA(str, -1, &rc, DT_LEFT|DT_NOCLIP|DT_EXPANDTABS, D3DCOLOR_RGBA(strr,strg,strb,stra) );
}

void CDirectX::SetStringColor(int r,int g,int b,int a)
{
	strr=r;
	strg=g;
	strb=b;
	stra=a;
}

int CDirectX::SetStringFont(char *fontname,int size)
{
	if(fontname==NULL)
	{
		fontname="ＭＳ Ｐ明朝";
	}
	hFont = CreateFont( 
	size, 0, 0, 0,FW_REGULAR,FALSE,FALSE,FALSE,
	SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
	fontname );
	if(hFont==NULL)
	{
		return -1;
	}
	RELEASE(lpFont);
	D3DXCreateFont( lpD3DDEV , hFont , &lpFont ) ;
	DeleteObject(hFont);
	return 0;
}

void CDirectX::SetBackScreenColor(int sr,int sg,int sb)
{
	br=sr;
	bg=sg;
	bb=sb;
}

void CDirectX::SetScreenColor(float red,float green,float blue,float light)
{
	scrr=red;
	scrg=green;
	scrb=blue;
	scrl=light;
}


void CDirectX::SetColorKey(bool flag,int sr,int sg,int sb)
{
	colorkey=flag;
	r=sr;
	g=sg;
	b=sb;
}

void CDirectX::SetSlideDrawScreenCenter(int x,int y){
	scrslidex=x;
	scrslidey=y;
}

void CDirectX::DrawGraph(int x,int y,int wid,int hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number)
{
	float alpha=255;
	x+=scrslidex;
	y+=scrslidey;
	if(x>640 || y>480 || x+wid<0 || y+hei<0)return;
	if(number==-1 || number>=graph.size())
	{
		return;
	}
	// 頂点を準備
	TLVERTEX vertex[4];
	float ux,uy,uw,uh;
	ux=(float)(gx+0.5f)/graph[number]->GetWidth();
	uy=(float)(gy+0.5f)/graph[number]->GetHeight();
	uw=(float)(gx+gwid+0.5f)/graph[number]->GetWidth();
	uh=(float)(gy+ghei+0.5f)/graph[number]->GetHeight();
	if(alpha>255)alpha=255;
	if(alpha<0)alpha=0;
	if(ux<0.0f)ux=0.0f;
	if(uy<0.0f)uy=0.0f;
	if(ux>1.0f)ux=1.0f;
	if(uy>1.0f)uy=1.0f;
	vertex[0].x = x;	vertex[0].y = y;	vertex[0].z = 0.0f;vertex[0].rhw = 1.0f;vertex[0].tu = ux;	vertex[0].tv = uy;		
	vertex[0].color = D3DCOLOR_RGBA((int)(255*graph[number]->GetColorRed()*scrr),(int)(255*graph[number]->GetColorGreen()*scrg),(int)(255*graph[number]->GetColorBlue()*scrb),(int)(alpha*graph[number]->GetColorLight()*scrl)) ;
	vertex[1].x = x+wid;vertex[1].y = y;	vertex[1].z = 0.0f;vertex[1].rhw = 1.0f;vertex[1].tu = uw;	vertex[1].tv = uy;		
	vertex[1].color = D3DCOLOR_RGBA((int)(255*graph[number]->GetColorRed()*scrr),(int)(255*graph[number]->GetColorGreen()*scrg),(int)(255*graph[number]->GetColorBlue()*scrb),(int)(alpha*graph[number]->GetColorLight()*scrl)) ;
	vertex[2].x = x+wid;vertex[2].y = y+hei;vertex[2].z = 0.0f;vertex[2].rhw = 1.0f;vertex[2].tu = uw;	vertex[2].tv = uh;	
	vertex[2].color = D3DCOLOR_RGBA((int)(255*graph[number]->GetColorRed()*scrr),(int)(255*graph[number]->GetColorGreen()*scrg),(int)(255*graph[number]->GetColorBlue()*scrb),(int)(alpha*graph[number]->GetColorLight()*scrl)) ;
	vertex[3].x = x;	vertex[3].y = y+hei;vertex[3].z = 0.0f;vertex[3].rhw = 1.0f;vertex[3].tu = ux;	vertex[3].tv = uh;	
	vertex[3].color = D3DCOLOR_RGBA((int)(255*graph[number]->GetColorRed()*scrr),(int)(255*graph[number]->GetColorGreen()*scrg),(int)(255*graph[number]->GetColorBlue()*scrb),(int)(alpha*graph[number]->GetColorLight()*scrl)) ;
	RotateMatrix(vertex,rot);
	ZoomMatrix(vertex,zoom,zoom,zoom);
	// テクスチャ設定
	lpD3DDEV->SetTexture(0,graph[number]->GetBitMap());
	// 頂点フォーマットの設定
	lpD3DDEV->SetVertexShader(FVF_TLVERTEX);
	// ポリゴン描画
	lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(TLVERTEX));
}
void CDirectX::DrawGraph(float x,float y,float wid,float hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number)
{
	DrawGraph(round(x),round(y),round(wid),round(hei),gx,gy,gwid,ghei,rot,zoom,number);
}
void CDirectX::DrawGraph(float x,float y,float wid,float hei,int gx,int gy,int gwid,int ghei,unsigned int number)
{
	DrawGraph(round(x),round(y),round(wid),round(hei),gx,gy,gwid,ghei,0,1,number);
}
void CDirectX::DrawGraph(float x,float y,int wid,int hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number)
{
	DrawGraph(round(x),round(y),wid,hei,gx,gy,gwid,ghei,rot,zoom,number);
}
void CDirectX::DrawGraph(float x,float y,int wid,int hei,int gx,int gy,int gwid,int ghei,unsigned int number)
{
	DrawGraph(round(x),round(y),wid,hei,gx,gy,gwid,ghei,0,1,number);
}
void CDirectX::DrawGraph(int x,int y,int wid,int hei,int gx,int gy,int gwid,int ghei,unsigned int number)
{
	DrawGraph(x,y,wid,hei,gx,gy,gwid,ghei,0,1,number);
}

void CDirectX::DrawGraph(int x,int y,int wid,int hei,int gx,int gy,unsigned int number)
{
	DrawGraph(x,y,wid,hei,gx,gy,wid,hei,0,1,number);
}


void CDirectX::DrawGraphSprite(int x,int y,int gx,int gy,int wid,int hei,float a,float b,int rad,unsigned int number)
{
	if(number==-1 || number>=graph.size())
	{
		return;
	}
	if(x>640 || y>480 || x+wid<0 || y+hei<0)return;
	x+=scrslidex;
	y+=scrslidey;
	D3DXVECTOR2 v;
	int def_wid,def_hei;
	def_wid=graph[number]->GetWidth();
	def_hei=graph[number]->GetHeight();
	v.x = float(x);
	v.y = float(y);
	if(hei+wid == GRAPH_DEF)
	{
		hei=def_hei-gx;
		wid=def_wid-gy;
	}
	else if(hei+wid == wid)
	{
		hei=def_hei-gx;
	}
	else if(hei+wid == hei)
	{
		wid=def_wid-gy;
	}
	 RECT	Rect = { gx,gy,wid+gx,hei+gy };
	D3DXVECTOR2	Scaling( a, b );
	D3DXVECTOR2 Center( graph[number]->GetCenterX(), graph[number]->GetCenterY() );
	D3DXVECTOR2	Translation( x, y );
	int			nDegree = rad;

	lpD3DXSprite->Begin();
	lpD3DXSprite->Draw(
	graph[number]->GetBitMap(), 
	&Rect,
	&Scaling,
	&Center,
	D3DXToRadian( nDegree % 360 ),
	&Translation,
	D3DXCOLOR(graph[number]->GetColorRed()*scrr,graph[number]->GetColorGreen()*scrg,graph[number]->GetColorBlue()*scrb,graph[number]->GetColorLight()*scrl));
	lpD3DXSprite->End();
	
}

int CDirectX::LoadGraph(const char *dir)
{
	char str[256];
	sprintf(str,"  %sを画像として読み込みます",dir);
	WriteLog(str);
	graph.push_back(new Graph);
	if(graph[graph.size()-1]->LoadGraphFile(dir,lpD3DDEV,colorkey,r,g,b)==false)
	{
		sprintf(str,"  %sの読み込みに失敗しました",dir);
		MessageBox(GetWindowHandle(),str,"error",MB_OK);
		WriteLog(str);
		return -1;
	}
	graph[graph.size()-1]->SetCenter(false,0,0);
	return graph.size()-1;
}

void CDirectX::ClearScreen()
{
	// バックバッファと Z バッファをクリア
	lpD3DDEV->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(br,bg,bb),1.0f,0);
}



void CDirectX::SetGraphColor(unsigned int number,float red,float green,float blue ,float light)
{
	if(number==-1 || number>=graph.size())
	{
		return;
	}
	graph[number]->SetColor(red,blue,green,light);
}

void CDirectX::SetGraphCenter(unsigned int number,bool flag,int x,int y)
{
	if(x<0 || y<0)
	{
		return;
	}
	graph[number]->SetCenter(flag,x,y);
}