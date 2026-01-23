#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"

GameManager Gmanager;

GameManager::GameManager(void)
{
	m_SysTem.m_Save1 = 100;

	m_GameStart = true; // 게임 시작 플래그 설정

	GameTime=0;
    m_GamePlayTime=0;
	m_TimerRunning = false;
}

GameManager::~GameManager(void)
{
}

void GameManager::Init()
{
	canShowScore = false;
	timerStarted = false;
	conditionStartTime = 0;

	wallSpeedLeft = 1;
	wallSpeedRight = 1;
	tntHit = false;

	// 기계어 버전
	FILE* fp = fopen("./Save/save.fss", "rb");
	if (fp != NULL)
	{
		fread(&m_SysTem, sizeof(SysTem), 1, fp);
		fclose(fp);  // 파일이 열렸을 때만 닫기
	}
	
}

void GameManager::Update()
{
	// 스테이지 클리어, 종료 조건 확인
	bool aliveEnemyExists = false;
	for (auto enemy : myList)
	{
		if (!enemy->isDead)
		{
			aliveEnemyExists = true; // 살아있는 적이 하나라도 있으면 true
			break;
		}
	}
	// 다음 맵/점수 전환 타이머 시작 조건
	if (!timerStarted)
	{
		// 적이 모두 죽거나 없고, 총알이 모두 소진된 경우 (성공 조건)
		if ((myList.empty() || !aliveEnemyExists) && !isFireBullet)
		{
			conditionStartTime = GetTickCount64();
			timerStarted = true;
		}
		// 적이 남아있는데 (aliveEnemyExists), 총알을 6발 다 쓰고 (BulletCount == 6), 
		// 현재 발사된 총알이 없는 경우 (!isFireBullet) (실패/재도전 조건)
		else if (aliveEnemyExists && BulletCount == 6 && !isFireBullet)
		{
			conditionStartTime = GetTickCount64();
			timerStarted = true;
		}
	}

	// 적 업데이트
	for (auto Iter = myList.begin(); Iter != myList.end(); Iter++)
	{
		(*Iter)->Update();
	}
	// 죽은 적 처리 및 제거 (리스트 관리)
	for (auto iter = myList.begin(); iter != myList.end();)
	{
		Enemy* pEnemy = *iter;
		// 적이 총알에 맞았거나 TNT가 폭발한 경우 ( 거리탐색 X )
		if ((*pEnemy).isHit || block.Exploded)
		{
			if (pEnemy->HitTime == 0) // 처음 맞은 시간 기록
			{
				pEnemy->HitTime = GetTickCount64();
				pEnemy->isDead = true;
			}
			// 맞은 후 1초가 지나면 리스트에서 제거
			if (GetTickCount64() - pEnemy->HitTime >= 1000)
			{
				delete pEnemy; // 메모리 해제
				iter = myList.erase(iter);  // 리스트에서 제거
				continue;
			}		
		}
     	++iter; // 죽지 않았다면 다음 요소로 이동
		
	}
	ObstacleUpdate(); // 스테이지 3 전용 움직이는 벽(장애물) 업데이트
}

// 설정 저장 (수업 제공 함수)
void GameManager::Save() 
{
	// "wb"로 파일 열기
	if ((fp = fopen("./Save/save.fss", "wb")) == NULL)
	{
		return; // 파일 열기 실패 시 종료
	}
	fwrite(&m_SysTem, sizeof(SysTem), 1, fp); // 구조체 데이터를 파일에 쓰기
	fclose(fp);

}

// 다음 맵으로 전환 또는 게임 종료
void GameManager::Nextmap()
{
	if (result.Nextmap == true) // 다음 맵 버튼이 눌렸다면
	{
		// 총알 남은 개수에 따른 점수 계산 그리고 합산
		if (BulletCount <= 2) //총알 6발중 2발 이하 사용
		{
			DrawTotal += 3; // 스코어 3점
		}
		else if (BulletCount <= 4)
		{
			DrawTotal += 2; // 스코어 2점
		}
		else if (BulletCount <= 6)
		{
			DrawTotal += 1; // 스코어 1점
		}
		if (map.m_Stage >= 4)  // 스테이지4 클리어 시 게임 오버
		{
			g_Mng.n_Chap = OVER; // 챕터를 게임 오버로 설정  
			if (m_TimerRunning) {
				// 타이머를 중지하고 경과 시간을 누적 시간에 합산
				m_GamePlayTime += GetTickCount64() - GameTime;
				m_TimerRunning = false;
			}
		}
		// 다음 스테이지로 전환
		else
		{
			SetCursorVisible(FALSE); // 커서 숨김
			map.m_Stage++; // 스테이지 번호 증가
			map.Init(); // 맵 초기화
			GameReset(); // 게임 요소 초기화
		}
	}
}

// 스테이지 전환 시 게임 요소 초기화
void GameManager::GameReset(void) 
{
	// 적 리스트 메모리 해제 및 클리어
	for (auto it = myList.begin(); it != myList.end(); ++it) {
		delete* it;
	}
	myList.clear();

	SetCursorVisible(FALSE); // 커서 숨김
	BulletCount = 0; // 총알 사용 횟수 초기화
	game.Init(); // 다른 게임 관련 객체 초기화
}

void GameManager::ObstacleUpdate()
{
	if (map.m_Stage == 3)     
	{
		// 왼쪽 벽 이동 (Y축)
		coll.wallYleftMove += wallSpeedLeft;
		// 벽이 해당 좌표까지 도달하면 속도 반전 
		if (coll.wallYleftMove <=350 || coll.wallYleftMove + 200 >= 870)  //y축
			wallSpeedLeft *= -1;
		

		// 오른쪽 벽 이동 (Y축)         
		coll.wallYrightMove -= wallSpeedRight;
		// " "
		if (coll.wallYrightMove >=670 || coll.wallYrightMove + 200 <=550)
			wallSpeedRight *= -1;
		
	}
}

void GameManager::Draw()
{
	// 적 렌더링
	for (auto Iter = myList.begin(); Iter != myList.end(); Iter++)
		(*Iter)->Draw();
	
	// 점수 화면 전환 타이머 체크 (3초 대기)
	if (timerStarted && GetTickCount64() - conditionStartTime >= 3000)
	{
		canShowScore = true;
		SetCursorVisible(TRUE); // 커서 표시
	}
	
	result.SetShowFlag(canShowScore); // result.canShow = true
	result.Draw(); // result.canShow가 true이면 로직 실행
}

// 메뉴 화면으로 돌아가기
void  GameManager::Prvchap()
{
	if (canShowScore)
	{
		SetCursorVisible(FALSE); // 점수 화면을 닫기 위해 커서 숨김
	} 
	SetCursorVisible(TRUE); // 커서 표시
	DrawTotal = 0; // 누적 점수 초기화
	g_Mng.n_Chap = MENU; // 메뉴로 전환
	sound.m_Bk1->Stop(); // 배경음악 중지
	map.m_Stage = 1; // 스테이지 초기화
}

// 마우스 커서 표시/숨김 제어
void GameManager::SetCursorVisible(bool visible)
{
	int count;
	if (visible) 
		while ((count = ShowCursor(TRUE)) < 0);  // 커서가 보일 때까지 반복 (카운트 0 이상)
	
	else 
		while ((count = ShowCursor(FALSE)) >= 0); // 커서가 숨겨질 때까지 반복 (카운트 -1 미만)
	
}
