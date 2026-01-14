
#include "Include.h" 
HWND g_hWnd = NULL;
const int TICKS_PER_SECOND = 60; 
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND; 
const int MAX_FRAMESKIP = 5; 
int loops;
float interpolation;

/// 사용자 정의 ///
float MouseX = 0; // 현재 마우스 X 좌표
float MouseY = 0; // 현재 마우스 Y 좌표

int BulletCount = 0; // 사용된 총알 개수
bool isFireBullet = false; // 총알이 현재 발사되어 날아가는지에 대한 여부
bool BulletSound = false; // 총알 발사 사운드 재생 플래그
/// ///////////////

LRESULT CALLBACK WndProc( HWND g_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSEX wc ;
	  
	wc.hInstance = GetModuleHandle( NULL ) ;
	wc.cbSize = sizeof( wc ) ;
	wc.style = CS_CLASSDC ;
	wc.cbClsExtra = NULL ;
	wc.cbWndExtra = NULL ;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH) ;
	wc.hCursor = LoadCursor( wc.hInstance, IDC_ARROW ) ;
	wc.hIcon = LoadIcon( wc.hInstance, IDI_APPLICATION ) ;
	wc.hIconSm = LoadIcon( wc.hInstance, IDI_APPLICATION ) ;
	wc.lpfnWndProc = WndProc ;
	wc.lpszClassName ="Game" ;
	wc.lpszMenuName = NULL ;

	RegisterClassEx( &wc ) ;

	
	RECT rt = {0, 0, SCREEN_WITH, SCREEN_HEIGHT};
	int W = rt.right - rt.left;
	int H = rt.bottom - rt.top;
	int X = (GetSystemMetrics(SM_CXSCREEN)/2) - SCREEN_WITH/2;
	int Y = ( (GetSystemMetrics(SM_CYSCREEN)/2) - SCREEN_HEIGHT/2 );
	


	// WS_POPUP 빼면 테투리가 생긴다
	g_hWnd = CreateWindowEx( NULL, wc.lpszClassName, 
		"Game", 
		WS_EX_TOPMOST, 
		X, Y, W, H,
		NULL, NULL, wc.hInstance, NULL ) ;


	dv_font.Create(g_hWnd) ;
	sound.g_pSoundManager = new CSoundManager();
	sound.g_pSoundManager->Initialize(g_hWnd, DSSCL_PRIORITY);
	sound.g_pSoundManager->SetPrimaryBufferFormat(2,22050,16);
	
	ShowWindow( g_hWnd, SW_SHOW ) ;
	UpdateWindow( g_hWnd ) ;
	Gmanager.SetCursorVisible(FALSE);

	///////////////////////////////////////////////////////////////////
	ZeroMemory(&msg, sizeof(MSG));
	g_Mng.chap[LOGO] = new Logo;
	g_Mng.chap[MENU] = new Menu;
	g_Mng.chap[GAME] = new Game;
	g_Mng.chap[OVER] = new Over;
	/////////////////////////////////////////

	for(int i=0; i<TOTALCHAP; i++)
		g_Mng.chap[i]->Init();
	    
	while( msg.message != WM_QUIT )
	{
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if(GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			static DWORD next_game_tick = GetTickCount();
			loops = 0;

			while( GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP) 
			{
				interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick ) / float( SKIP_TICKS );
			    g_Mng.chap[g_Mng.n_Chap]->Update(interpolation);
				g_Mng.chap[g_Mng.n_Chap]->OnMessage(&msg);
				next_game_tick += SKIP_TICKS;
				loops++;
			}

			dv_font.Device9->BeginScene();
			dv_font.Device9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 0, 0);

			g_Mng.chap[g_Mng.n_Chap]->Draw();

			dv_font.Device9->EndScene();
			dv_font.Device9->Present(NULL, NULL, NULL, NULL);
		}
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc( HWND g_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{

	case WM_DESTROY:
         PostQuitMessage( 0 );
         return 0;
	case WM_CREATE:
		Gmanager.SetCursorVisible(FALSE);
		break;
    
	////// 사용자 정의 //////
 	case WM_MOUSEMOVE:
		MouseX = LOWORD(lParam); // 마우스 X 좌표 받아오기
		MouseY = HIWORD(lParam); // 마우스 Y 좌표 받아오기
		break;
    
	case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼 눌림 이벤트
		// 사운드 버튼 충돌 영역
		 if (1032 <= MouseX && 1067 >= MouseX && 690 <= MouseY && 722 >= MouseY)
		 {
			 sound.isMuted = !sound.isMuted; // 음소거 상태 반전

			 if (sound.isMuted)
			 {
				 sound.StopAll(); // 모든 사운드 중지
			 }
			 else
			 {
				 sound.soundinit = false; // 사운드 초기화
			 }
			 break;
		 }
		if (1158 <= MouseX && MouseX <= 1200 && 687 <= MouseY && MouseY <= 723) 
			break; // 특정 영역 클릭시 이벤트 무시 
		if (1094 <= MouseX && 1135 >= MouseX && 685 <= MouseY && 722 >= MouseY)
			break; // 특정 영역 클릭시 이벤트 무시
		
		if (isFireBullet) //만약 총알 발사중일때
			break; // 연속 발사 방지
		   
		if (BulletCount >= 6) // 총알 6발을 모두 사용했을 때 
			break; // 발사 제한
		
		if (Gmanager.myList.empty()) //적이 모두 죽었다면
		{
			isFireBullet = false; //총알 발사 멈춤
			break; // 발사 제한
		}
		   
		

		isFireBullet = true; // 총알 발사 시작
		if (!sound.isMuted)
		BulletSound = true; // 사운드 재생 플래그 ON

		bullet.Fire(MouseX, MouseY); // 총알 발사 함수 호출

		BulletCount++; // 사용된 총알 개수 증가
		break;
	}
	//////////////////////////
	return DefWindowProc( g_hWnd, uMsg, wParam, lParam ) ;
}