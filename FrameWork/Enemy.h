#pragma once
#include "Include.h"

class Enemy
{
private:
	float gravity; // 중력 가속도 값
	bool grounded; // 바닥에 닿았는지 여부
	float x; // 생성자 초기화용 X 좌표
	float y; // 생성자 초기화용 Y 좌표

	int m_CurrentFrame; // 현재 출력할 프레임
	DWORD m_AnimTime;  // 마지막 애니메이션 프레임 변경 시간 
	DWORD m_FrameDelay; // 애니메이션 프레임 간의 지연 시간

	int Alpha; //적 이미지 투명도
	ULONGLONG AlphaTime; // 마지막 알파값 변경 시간
	bool Alphastate; // 투명화 여부
public :
	Enemy() {};
	Enemy(float _x, float _y);
	~Enemy();

	enum ENEMY_STATE 
	{
		STATE_IDLE, // 살아있는 상태
		STATE_HIT // 피격(사망) 상태
	}; ENEMY_STATE state;

	char FileName[256];
	Sprite Enemies[5]; // Idle : 2장, Hit 3장
	D3DXIMAGE_INFO imagesinfo; // 이미지 파일 해상도 정보
	RECT m_rc; // 적의 충돌 영역
	D3DXVECTOR2 pos; //적의 위치 벡터
	DWORD m_PlayTime; // 충돌 업데이트 시간 (증력 제어)
   
	bool isDead; //적이 죽었는지 여부 (GameManager, Sound 등에 사용됨)
	bool ScoreScreen; //적 모두 명중시 점수 화면 띄울지 여부
	
	bool isHit; // 적이 총알에 맞았는지 여부
	DWORD HitTime; //적 피격 후 시간 기록 (GameManager에 사용됨)

	void Init();
	void Update(); 
	void Draw();
};
extern Enemy enemy;
extern bool isFireBullet; //총알 발사 상태 플래그