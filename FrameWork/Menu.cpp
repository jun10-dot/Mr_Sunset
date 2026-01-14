#include "Include.h"
#include <string>

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
	// 메뉴 배경 이미지 로드
	menuimg.Create("./resource/Img/lobby/Lobby.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

// Chap, 재정의 함수 호출
void Menu::Update(double frame)
{
}

void Menu::Draw()
{
	// 배경 이미지 렌더링
	menuimg.Render(-50, 0, 0, 0.75, 0.75); 
}

void Menu::OnMessage(MSG* msg)
{
	switch (msg->message)
	{
	  case WM_LBUTTONDOWN:  // 마우스 왼쪽 버튼 클릭
	
		// 마우스 클릭 좌표
		int mouseX = LOWORD(msg->lParam);
		int mouseY = HIWORD(msg->lParam);
	  
		// 게임 시작 버튼 (충돌 영역)
		if (453 <= mouseX && 845 >= mouseX && 360 <= mouseY && 463 >= mouseY)
		{
			msg->message = 0;
			// 게임 챕터로 전환
			g_Mng.n_Chap = GAME;
			// 총알 사운드 관련 플래그 초기화
			BulletSound = false;
			// 게임 초기화
			Gmanager.GameReset();
			// 게임 시간 측정 시작 시점 기록
			Gmanager.GameTime = GetTickCount64();
			// 타이머 실행 ON
			Gmanager.m_TimerRunning = true;
		
			if(!sound.isMuted) // 음소거 상태가 아니라면
			{
				sound.soundinit = false; // 사운드 초기화, 재생 준비
			}
		}

		// 게임 종료 버튼 (충돌 영역)
		else if (450 <= mouseX && 845 >= mouseX && 545 <= mouseY && 652 >= mouseY)
		{
			PostQuitMessage(0); // 윈도우 종료 메시지
		}
	  break;
    }
}