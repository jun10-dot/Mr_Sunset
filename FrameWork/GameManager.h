#pragma once
#include "Include.h"
struct SysTem
{
	int m_Save1;
};

class GameManager
{
private:
	FILE* fp; // 파일 포인터 (저장/로드용)
	bool timerStarted; // 다음 스테이지 시작 여부
	int wallSpeedLeft; //왼쪽 벽의 이동 속도
	int wallSpeedRight; //오른쪽 벽의 이동 속도
public:
	GameManager(void);
	~GameManager(void);

	SysTem m_SysTem;

	int DrawTotal; // 스테이지 클리어 점수 누적 합산
	DWORD GameTime; // 타이머 시작 시간
	DWORD m_GamePlayTime; // 누적 게임 플레이 시간
	bool m_TimerRunning; // 게임 시간 측정 중인지 여부

	bool m_GameStart; // 게임이 시작되었는지 여부
	bool canShowScore; // 점수 화면을 보여줄 수 있는지 여부
	bool tntHit; // TNT 블록이 총알에 맞았는지 여부

	std::list<Enemy*>	myList; // 스테이지에 존재하는 적 목록
	
	ULONGLONG conditionStartTime; // 스테이지 종료 조건 만족 시 시간 기록
	
	void GameReset(void); // // 스테이지별 초기화
	void Init();
	void Update();
	void Draw();
	void Save(); // 시스템 설정 저장
	void Nextmap(); // 다음 맵으로 전환하거나 게임을 종료
	void Prvchap(); // 이전 챕터 (메뉴)로 돌아가기
	void ObstacleUpdate(); // 스테이지3/벽(장애물) 이동 업데이트
	void SetCursorVisible(bool visible); // 마우스 커서 활성화/비활성화
};

extern GameManager Gmanager;
extern bool isFireBullet; // 총알 발사 요청 플래그
extern int BulletCount; // 총알 사용 횟수
