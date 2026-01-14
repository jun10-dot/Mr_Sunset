#include "Include.h"

Enemy enemy;

Enemy::Enemy(float _x, float _y) :x(_x), y(_y)
{
	pos.x = _x; // 위치 벡터 초기화
	pos.y = _y;
}

Enemy::~Enemy()
{
	for (int i = 0; i <2; i++)
	{
		Enemies[i].Destroy(); // 스프라이트 해제
	}
}

void Enemy::Init()
{
	gravity = 5.75f;
	grounded = false;

	m_CurrentFrame = 0;
	m_AnimTime = GetTickCount64();
	m_FrameDelay = 200;

	ScoreScreen = false;
	isHit = false;
	HitTime = 0;
	state = STATE_IDLE;
	isDead = false;

	Alpha = 255;
	AlphaTime = 0;
	Alphastate = false;

	// 적 스프라이트 로드
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(FileName, "./resource/Img/Enemy/Enemy-%04d.png", i);
		Enemies[i].Create(FileName, false, D3DCOLOR_XRGB(255, 0, 255));
		if (i == 0)
		{
			// 첫 프레임의 이미지 정보만 저장
			D3DXGetImageInfoFromFile(FileName, &imagesinfo);
		}
	}
	// 충돌 영역 설정
	m_rc.left = pos.x;
	m_rc.top = pos.y;
	m_rc.right = pos.x + imagesinfo.Width ;
	m_rc.bottom = pos.y + imagesinfo.Height ;

}

void Enemy::Update()
{
	// 충돌 업데이트 (10ms 간격으로 제어)
	if (GetTickCount64() - m_PlayTime > 10)
	{
		if (!grounded) pos.y += gravity; // 중력 적용
		// 바닥 충돌
		if (m_rc.left < coll.m_rc.right && coll.m_rc.left < m_rc.right && m_rc.top < coll.m_rc.bottom && coll.m_rc.top < m_rc.bottom) grounded = true;
		if (map.m_Stage == 4) // 스테이지 4
		{
			if (m_rc.left < coll.m_rc.right && coll.m_rc.left < m_rc.right && m_rc.top < coll.m_rc.bottom && coll.m_rc.top-10 < m_rc.bottom) grounded = true;
		}
		if (map.m_Stage == 2) // 스테이지 2
		{
			if (m_rc.left < coll.m_rc_Up.right && coll.m_rc_Up.left < m_rc.right && m_rc.top < coll.m_rc_Up.bottom && coll.m_rc_Up.top  < m_rc.bottom) grounded = true;
			if (m_rc.left < coll.m_rc_Under.right && coll.m_rc_Under.left < m_rc.right && m_rc.top < coll.m_rc_Under.bottom && coll.m_rc_Under.top  < m_rc.bottom) grounded = true;
		}


		// 적의 충돌영역과 총알 충돌 검사
		if (m_rc.left+60  < bullet.m_rc_Bullet.right && bullet.m_rc_Bullet.left < m_rc.right+20 && m_rc.top+40  < bullet.m_rc_Bullet.bottom && bullet.m_rc_Bullet.top < m_rc.bottom)
		{
			ScoreScreen = true; // 점수 화면 표시
			isHit = true; // 피격
			state = STATE_HIT;
			m_CurrentFrame = 2; // HIT 애니메이션 시작 

			Alphastate = true; //투명도 효과 시작
			AlphaTime = GetTickCount64();// 투명도 효과 시작 시간 기록
		}

		// 충돌 영역 업데이트
		m_rc.left = pos.x;
		m_rc.top = pos.y;
		m_rc.right = pos.x + imagesinfo.Width + 10;
		m_rc.bottom = pos.y + imagesinfo.Height+30;

		m_PlayTime = GetTickCount64(); 
	}

	// 애니메이션 프레임 변경 (m_FrameDelay 간격)
	if (GetTickCount64() - m_AnimTime > m_FrameDelay)
	{
		if (state == STATE_IDLE) // Idle 상태 애니메이션, 반복
		{
			m_CurrentFrame++;
			if (m_CurrentFrame > 1) m_CurrentFrame = 0; 
		}
		else if (state == STATE_HIT) // Hit 상태 애니메이션, 반복
		{
			m_CurrentFrame++;
			if (m_CurrentFrame > 4) m_CurrentFrame = 2;
		}
		m_AnimTime = GetTickCount64(); // 애니메이션 시간 업데이트
	}

	// 피격 후 투명도 감소 
	if (Alphastate && GetTickCount64() - AlphaTime > 100)
	{
		Alpha -= 25;
		if (Alpha <= 0)
		{
			Alpha = 0;
			Alphastate = false;
		}
		AlphaTime = GetTickCount64(); 
	}

	// TNT 폭발에 의한 피격 처리
	if (block.isTNThit && state != STATE_HIT) // TNT가 폭발했고, 아직 죽지 않았다면
	{
		state = STATE_HIT;
		m_CurrentFrame = 2;
		Alphastate = true;
		AlphaTime = GetTickCount64();
	}
}

void Enemy::Draw()
{
	// 게임 시작 상태일 때만 렌더링
	if (Gmanager.m_GameStart)
	{
		// 피격 후 Alpha 값 감소
		Enemies[m_CurrentFrame].Render(pos.x, pos.y, 0, 2, 2, 0, D3DCOLOR_ARGB(Alpha, 255, 255, 255) );
	}
}