#pragma once
#include "Include.h"

class Player
{
private:
	bool grounded; // 캐릭터가 바닥에 닿았는지 여부
	int m_CurrentFrame; // 현재 출력할 애니메이션 프레임
	DWORD m_AnimTime;  // 마지막 애니메이션 프레임 변경 시간
	DWORD m_FrameDelay[2] = { 1500,100 }; // 눈 깜빡임 딜레이
	DWORD m_PlayerTime;
	float gravity;
	float angle;  // 총 이미지의 회전각도 - 마우스 위치

public :
	Player();
	~Player();
	
	Sprite playerimg[2]; // 캐릭터 2프레임 이미지
	Sprite Scope; //조준경 이미지
	Sprite Gun; // 총 이미지

	D3DXIMAGE_INFO imagesinfo;  // 해상도 및 비트맵 정보
	RECT m_rc; // 캐릭터 충돌 영역
	D3DXVECTOR2 pos; //캐릭터의 화면 상 위치 벡터

	void Init();
	void Update();
	void Draw();
};

extern Player player; 
extern float MouseX; // 마우스 커서의 X 좌표
extern float MouseY; // 마우스 커서의 Y 좌표
extern bool isFireBullet; // 총알 발사 명령 플래그
