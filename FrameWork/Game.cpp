#include "Include.h"

Game game;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	map.Init();
	player.Init();
	bullet.Init();
	coll.Init();
	block.Init();
	sound.Init();
	Gmanager.Init();
	result.Init();
}

void Game::Draw()
{
	map.Draw();
	bullet.Draw();
	player.Draw();
	block.Draw();
	Gmanager.Draw();
}

// Chap, 재정의 함수 호출
void Game::Update(double frame)
{
	static DWORD a = 0;
	sound.Update();
	if (GetTickCount64() - a > frame)
	{
		coll.Update();
		player.Update();
		bullet.Update();
		block.Update();
		Gmanager.Update();
		a = GetTickCount64();
	}
}

void Game::OnMessage( MSG* msg )
{
	switch (msg->message)
	{
	case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼 클릭

		// 인게임 UI 버튼 충돌 영역 설정
		if (1217 <= MouseX && 1262 >= MouseX && 684 <= MouseY && 726 >= MouseY)
			PostQuitMessage(0); // 게임 종료 버튼
		
		else if (1158 <= MouseX && 1200 >= MouseX && 687 <= MouseY && 723 >= MouseY)
			Gmanager.GameReset();// 리셋 버튼
		
		else if (1094 <= MouseX && 1135 >= MouseX && 685 <= MouseY && 722 >= MouseY)
		{
			msg->message = 0;
			Gmanager.Prvchap(); // 메인화면 전환 버튼
		}
		if (result.Nextmap && 449 <= MouseX && 791 >= MouseX && 385 <= MouseY && 500 >= MouseY)//좌표 변경시켜주기
			Gmanager.Nextmap(); // 점수 화면 중앙 다음라운드 진행 버튼

		if (result.Again && 449 <= MouseX && 791 >= MouseX && 385 <= MouseY && 500 >= MouseY)//좌표 변경시켜주기
			Gmanager.GameReset();// 점수 화면 중앙 리셋 버튼 

		break;
	}
}