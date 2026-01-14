#include "Include.h"


Over::Over()
{
}

Over::~Over()
{
}

void Over::Init()
{
	// 게임 오버 배경 이미지 로드
	overimg.Create("./resource/Img/over.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

void Over::Update(double frame)
{

}

void Over::Draw()
{
	// 배경 이미지 렌더링 (0.75배 축소)
	overimg.Render(-50, 0, 0, 0.75, 0.75);
	// 최종 점수 출력
	dv_font.DrawString("SCORE :", 530, 550, Gmanager.DrawTotal); 
	// 커서 표시
	Gmanager.SetCursorVisible(TRUE);
	// 총 플레이 시간 
    totalTime = Gmanager.m_GamePlayTime;
	// 만약 타이머가 아직 작동 중이었다면
	if (Gmanager.m_TimerRunning) {
		totalTime += GetTickCount64() - Gmanager.GameTime; // 현재까지의 경과 시간을 누적
	}
    seconds = totalTime / 1000;  // 밀리초(ms)이기때문에 초 단위로 변환
	char timeText[64];
	
	// 시간을 분 : 초 형태로 세팅
	if (seconds >= 60)
	{
	    minutes = seconds / 60;  // 분 단위로 변환	
		seconds %= 60;  // 나머지 초 계산
		sprintf(timeText, "TIME : %d분 %u초",minutes,seconds);
	}
	else
	{
		sprintf(timeText, "TIME : %u초", seconds); // 60초 미만이면 초만 출력 
	}
	// 플레이 시간 출력
	dv_font.DrawString(timeText, 530, 600);
	// 메뉴로 돌아가는 버튼 이미지 렌더링
	map.m_Menu.Render(map.posX + 1230,map. posY + 720, 0, 1, 1);
}

void Over::OnMessage( MSG* msg )
{
	switch (msg->message)
	{
	case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼 클릭
		// 메뉴 버튼 (충돌 영역)
		if (1217 <= MouseX && 1262 >= MouseX && 684 <= MouseY && 726 >= MouseY)
		{
			msg->message = 0; 
			// 게임 상태 초기화
			Gmanager.DrawTotal = 0;
			Gmanager.m_GamePlayTime = 0;
			// 메뉴 화면으로 전환
			Gmanager.Prvchap();
		}
		break;
	}
}