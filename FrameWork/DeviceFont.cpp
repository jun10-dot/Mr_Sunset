#include "Include.h"

g_DeviceFont dv_font;

g_DeviceFont::g_DeviceFont(void)
{
	AddFontResourceEx("./Typo_SsangmunDongB.ttf", FR_PRIVATE, 0);
}

g_DeviceFont::~g_DeviceFont(void)
{
}

bool g_DeviceFont::Create( HWND g_hWnd )
{

	Direct3D = Direct3DCreate9( D3D_SDK_VERSION );


	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;												// 전체 화면 모드로 생성
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				          
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ;
	d3dpp.BackBufferWidth = SCREEN_WITH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	HRESULT hr = Direct3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &Device9);


	// 알파 블렌딩 설정
	Device9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	
	// 스프라이트/폰트 그리기 위해 생성.
	D3DXCreateSprite( Device9 , &Sprite ) ;

	ZeroMemory( &fdesc , sizeof(fdesc) ) ;
	fdesc.Height = 35 ;
	fdesc.Width = 22 ;
	fdesc.Weight = 500 ;
	fdesc.Italic = FALSE ;
	fdesc.CharSet = DEFAULT_CHARSET ;
	strcpy( fdesc.FaceName, "타이포_쌍문동 B" ) ;

	D3DXCreateFontIndirect( Device9 , &fdesc , &Fonts ) ;

	return true;

}

bool g_DeviceFont::DrawString( const char* msg , int x , int y , int total, D3DCOLOR color)
{
	char buffer[256];
	if (total == 0)
		sprintf_s(buffer, "%s", msg);
	else
	sprintf_s(buffer, "%s %d", msg, total);

	RECT rect = { x, y, x + (LONG)(fdesc.Width * (int)strlen(buffer)), y + (LONG)fdesc.Height };

	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	Fonts->DrawText(Sprite, buffer, -1, &rect, DT_NOCLIP, color);
	Sprite->End();

	return true;
}