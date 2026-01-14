#include "Include.h"

Result result;

Result::Result()
{

}
Result::~Result()
{

}

void Result::Init()
{
	char FileName[256];
	canShow = false;
	aliveEnemyExists = false;
	Nextmap = false;
	Again = false;

	// 점수 이미지 리소스 4개를 로드합니다.
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(FileName, "./resource/Img/scorescreen/ScoreScreen-%04d.png",i);
		Score[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}


void Result::Draw()
{
	// 점수 화면을 표시할 준비가 안 되었으면 함수 종료
	if (!canShow) return;
	
	//적 리스트를 순회하며 살아있는 적이 있는지 확인합니다.
	for (auto enemy : Gmanager.myList)
	{
		if (!enemy->isDead)  // 죽지 않은 적 발견 시
		{
			aliveEnemyExists = true; // 살아있는 적 존재 플래그 설정
			break;
		}
	}

	//---------------------------------------------------------------------
	// 승리 조건 검사 로직
	// 1. 적 리스트가 비어있고 
	// 2. 살아있는 적이 없는 경우 
	if (Gmanager.myList.empty() || !aliveEnemyExists)  // 적 다 죽었거나
	{
		if (BulletCount <= 2)
		{
			Score[0].Render(posX + 300, posY, 0, 1, 1); //스코어 3점 (만점)
		}
		else if (BulletCount <= 4)
		{
			Score[1].Render(posX + 300, posY, 0, 1, 1); //스코어 2점
		}
		else if (BulletCount <= 6)
		{
			Score[2].Render(posX + 300, posY, 0, 1, 1); //스코어 1점
		}
		Nextmap = true; // 다음맵으로 이동하도록 플래그 설정
	}
	//---------------------------------------------------------------------
	// 실패 조건 검사 로직
	// 1. 총알 6발 모두 사용했고
	// 2. 살아있는 적이 남아 있으며 
	// 3. 현재 총알을 발사 중이 아닌 경우 
	else if (BulletCount == 6 && aliveEnemyExists && !isFireBullet)  // 적 남았고 6발 다 쓴 경우
	{
		Score[3].Render(posX + 300, posY, 0, 1, 1); // 실패 화면 표시
		
		Again = true;
	}
}






