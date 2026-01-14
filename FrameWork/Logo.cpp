#define _CRT_NONSTDC_NO_DEPRECATE

#include "Include.h"

Logo::Logo()
{
}

Logo::~Logo()
{
}

void Logo::Init()
{
	char filename[256];
	
	// 4개의 이미지 로드
	for (int i = 0; i < 4; i++)
	{
		sprintf(filename, "./resource/Img/Load/Sp-%04d.png", i);
		loadimg[i].Create(filename, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Logo::Update(double frame)
{
	// 프레임 시간 누적 
	frameTime += frame / 1300.0f;

	//0.1초 경과하면 다음 프레임으로 전환
	if (frameTime >= frameDelay)
	{
		frameTime = 0.0f;
		currentFrame++;

		// 프레임 0, 1, 2 일 때 사운드 재생
		if (currentFrame <= 3)
		{
			sound.PlayGunShot();
		}
		// 마지막 프레임이면
		else if (currentFrame >= 4)
		{
			currentFrame = 3; // 정지 상태 유지
		}
	}
}


void Logo::Draw()
{
	// 현재 프레임 이미지 색상/알파 값 설정
	loadimg[currentFrame].SetColor(255, 255, 255, 0);  
	// 이미지 렌더링
	loadimg[currentFrame].Render(0, -30, 0.0f, 1.0f, 1.0f);
}

void Logo::OnMessage( MSG* msg )
{
	switch(msg->message)
	{
	case WM_LBUTTONDOWN : // 마우스 왼쪽 버튼 클릭
		// 애니메이션이 마지막 프레임일 때만 클릭 처리
		if (currentFrame == 3) 
		{
			msg->message = 0;
			g_Mng.n_Chap = MENU; // 메인 메뉴로 전환
			Gmanager.SetCursorVisible(TRUE); // 커서 표시
		}
		break;
	}
}