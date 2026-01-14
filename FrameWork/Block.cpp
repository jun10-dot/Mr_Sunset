#include"Include.h"

Block block;

Block::Block()
{
}
Block::~Block()
{
}

void Block::Init()
{
	m_CurrentFrame = 0;
	animTime = GetTickCount64();
	Exploded = false;
	isTNThit = false;
	Destroyed = false;
	Alpha = 255; //기본 색
	char FileName[256];
	
	// TNT 블록 이미지 로드
	sprintf_s(FileName, "./resource/Img/TNT.png");
	m_tnt.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	// 폭발 애니메이션 이미지 로드
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(FileName, "./resource/Img/explosion/frame-%04d.png",i); //파티클
		m_boom[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// TNT 블록의 충돌 영역 설정 (스테이지 4의 고정된 위치)
	m_rcObject.left = 615;
	m_rcObject.top = 580;
	m_rcObject.right = 705;
	m_rcObject.bottom = 670;
}
void Block::Update()
{
	if (map.m_Stage == 4)
	{
		if (!Destroyed) //블록이 파괴되지 않았을 때만
		{
			if (bullet.m_rc_Bullet.left < m_rcObject.right &&
				m_rcObject.left < bullet.m_rc_Bullet.right &&
				bullet.m_rc_Bullet.top < m_rcObject.bottom &&
				m_rcObject.top < bullet.m_rc_Bullet.bottom)
			{
				// 총알 위치를 플레이어(총) 위치로 리셋
				bullet.BulletX = player.pos.x;
				bullet.BulletY = player.pos.y;

				isTNThit = true; // 폭발 애니메이션 시작 플래그 true
				isFireBullet = false; //총알 리셋
				Exploded = true; // TNT가 폭발했음을 알려줌 (GameManager.cpp)
			}
		}
		if (GetTickCount64() - animTime > 100) //폭발 애니메이션 (100ms 간격)
		{
			if (isTNThit) // 폭발이 진행 중이라면
			{
				m_CurrentFrame++;
				Alpha = 0; // TNT 이미지를 투명하게 만들어 사라지게 처리
			} 

			if (m_CurrentFrame >= 7) // 폭발 애니메이션이 끝까지 재생되면
			{
				isTNThit = false; // 애니메이션 종료
				Destroyed = true; // 블록 완전 파괴 상태로 변경
				m_CurrentFrame = 0; // 프레임 초기화
			}
			animTime = GetTickCount64(); // 애니메이션 시간 갱신
		}
	}
}

void Block::Draw()
{ 
	if (map.m_Stage == 4)
	{
		// TNT 블록 렌더링 (파괴되지 않았을 때만)
		if (!Destroyed)
		{
			m_tnt.Render(map.posX + 615, map.posY + 580, 0, 1, 1, 0, D3DCOLOR_ARGB(Alpha, 255, 255, 255)); //tnt
		}
		// 폭발 애니메이션 렌더링 (폭발이 진행 중일 때만)
		if (isTNThit) 
		{
			m_boom[m_CurrentFrame].Render(map.posX + 540, map.posY + 480, 0, 5, 5);
		}
	}
}