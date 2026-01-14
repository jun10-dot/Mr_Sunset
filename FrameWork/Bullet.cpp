#include"Include.h"

Bullet bullet;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	speed = 20.0f; // 기본 속도 설정
	BounceCount = 0; // 튕김 횟수 초기화
	delayBullet = GetTickCount64(); // 현재 시간 기록

	char FileName[256];

	//총알 이미지 로드
	sprintf_s(FileName, "./resource/Img/Bullet-0001.png");
	Bulletimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	
	// 총알 개수 UI 이미지 로드
	// 최대 6발 및 초기화
	for (int i = 0; i < 6; i++) 
	{
		sprintf_s(FileName, "./resource/Img/bulletimg/bulletimg-%04d.png", i); 
		m_BulletImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		bulletFired[i] = false;
		Alpha[i] = 255;
		bulletAlphaTime[i] = 0;
	}
}

//좌우 상하 축이 모두 존재하는 충돌체 (위치 보정 및 정교한 튕김)
bool Bullet::CheckAndResolveCollision(RECT& bullet_rc, const RECT& wall_rc)
{
	// 충돌 확인
	if (!(bullet_rc.left < wall_rc.right &&
		wall_rc.left < bullet_rc.right &&
		bullet_rc.top < wall_rc.bottom &&
		wall_rc.top < bullet_rc.bottom))
	{
		// 충돌하지 않음
		return false;
	}

	// 현재 충돌 박스들이 각 방향으로 얼마나 겹쳤는지 계산
	overlapLeft = bullet_rc.right - wall_rc.left;
	overlapRight = wall_rc.right - bullet_rc.left;
	overlapTop = bullet_rc.bottom - wall_rc.top;
	overlapBottom = wall_rc.bottom - bullet_rc.top;

	// 최소 겹침
	float minX = min(overlapLeft, overlapRight);
	float minY = min(overlapTop, overlapBottom);

	
	if (minX < minY) {
		// 좌우 충돌 발생 (X축이 최소 겹침)
		dirX = -dirX;       // X 방향 반전 (튕김)
		BulletX = prevBulletX; // 충돌 직전 위치로 복귀
		BounceCount++;      // 튕김 횟수 증가

		if (overlapLeft < overlapRight)
			BulletX -= overlapLeft + 1; // 왼쪽으로 1만큼 밀어냄
		else
			BulletX += overlapRight + 1; // 오른쪽으로 1만큼 밀어냄
	}
	else {
		// 상하 충돌 발생 (Y축이 최소 겹침)
		dirY = -dirY;       // Y 방향 반전 (튕김)
		BulletY = prevBulletY; // 충돌 직전 위치로 복귀
		BounceCount++;      // 튕김 횟수 증가

		if (overlapTop < overlapBottom)
			BulletY -= overlapTop + 1; // 위쪽으로 1만큼 밀어냄
		else
			BulletY += overlapBottom + 1; // 아래쪽으로 1만큼 밀어냄
	}

	// 충돌했음
	return true;
}

void Bullet::Update()
{
	// 총알	발사 후 종료 조건
	// 1. 6초 이상 비행 한 경우
	// 2. 20번 이상 튕겨진 경우
	// 3. 화면상 좌 우 밖으로 나갈 경우 
	if (GetTickCount64() - delayBullet >= 6000 || BounceCount >= 20 || BulletX > 1280 || BulletX < 0)
	{
		isFireBullet = false; 

		// 총알 위치를 플레이어 위치로 초기화
		BulletX = player.pos.x;  
		BulletY = player.pos.y;  
	}

	// 위치 기록
	prevBulletX = BulletX; // 현재 위치를 이전 위치로 복사 
	prevBulletY = BulletY; 

	//총알 이동
	if (isFireBullet) // 총알 발사된 상태라면
	{
		speed -= 0.02f;  // 속도 점점 줄이기

		// 새로운 위치 계산 : 방향 * 속도
		BulletX += dirX * speed;  
		BulletY += dirY * speed; 
	}
	else  // 총알이 중단된 상태라면
	{
		speed = 20.0f;  // 속도 초기화 
		BounceCount = 0;  // 튕김 횟수 초기화

		// 총알 위치를 플레이어 위치로 초기화
		BulletX = player.pos.x;  
		BulletY = player.pos.y; 
	}

	// 총알 충돌 박스 업데이트
	m_rc_Bullet.left = BulletX + map.posX ;
	m_rc_Bullet.top = BulletY + map.posY ;
	m_rc_Bullet.right = m_rc_Bullet.left ;
	m_rc_Bullet.bottom = m_rc_Bullet.top;

	if (map.m_Stage == 1)
	{
		if (m_rc_Bullet.left < coll.m_rc.right && coll.m_rc.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc.bottom && coll.m_rc.top < m_rc_Bullet.bottom)
		{
			dirY = -dirY; // 방향 반전
			BounceCount++;
		}
		if (m_rc_Bullet.left < coll.m_rc1.right && coll.m_rc1.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc1.bottom && coll.m_rc1.top < m_rc_Bullet.bottom)
		{
			dirY = -dirY;
			BounceCount++;
		}

		// 정교한 튕김 및 위치 보정 적용 함수
		CheckAndResolveCollision(m_rc_Bullet, coll.m_rc2); // 중앙 벽 (좌우, 상하)
	}

	if (map.m_Stage == 2)
	{
		if (m_rc_Bullet.left < coll.m_rc.right && coll.m_rc.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc.bottom && coll.m_rc.top < m_rc_Bullet.bottom)
		{
			dirY = -dirY;
			BounceCount++;
		}
		if (m_rc_Bullet.left < coll.m_rc2.right && coll.m_rc2.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc2.bottom && coll.m_rc2.top < m_rc_Bullet.bottom)
		{
			dirX = -dirX;
			BounceCount++;
		}
		if (m_rc_Bullet.left < coll.m_rc2_1.right && coll.m_rc2_1.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc2_1.bottom && coll.m_rc2_1.top < m_rc_Bullet.bottom)
		{
			dirX = -dirX;
			BounceCount++;
		}

		CheckAndResolveCollision(m_rc_Bullet, coll.m_rc_Under); // 아래 중앙 벽
		CheckAndResolveCollision(m_rc_Bullet, coll.m_rc_Up); // 위 중앙 벽
	}

	if (map.m_Stage == 3)
	{
		if (m_rc_Bullet.left < coll.m_rc.right && coll.m_rc.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc.bottom && coll.m_rc.top < m_rc_Bullet.bottom)
		{
			dirY = -dirY;
			BounceCount++;
		}

		CheckAndResolveCollision(m_rc_Bullet, coll.m_rc_Left); // 왼쪽 움직이는 벽
		CheckAndResolveCollision(m_rc_Bullet, coll.m_rc_Right); // 오른쪽 움직이는 벽
	}

	if (map.m_Stage == 4)
	{
		if (m_rc_Bullet.left < coll.m_rc.right && coll.m_rc.left < m_rc_Bullet.right && coll.m_rc.top < coll.m_rc.bottom && coll.m_rc.top < m_rc_Bullet.bottom)
		{
			dirY = -dirY; BounceCount++;
		}
		if (m_rc_Bullet.left < coll.m_rc2.right && coll.m_rc2.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc2.bottom && coll.m_rc2.top < m_rc_Bullet.bottom)
		{
			dirX = -dirX; BounceCount++;
		}
		if (m_rc_Bullet.left < coll.m_rc2_1.right && coll.m_rc2_1.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc2_1.bottom && coll.m_rc2_1.top < m_rc_Bullet.bottom)
		{
			dirX = -dirX; BounceCount++;
		}
		if (m_rc_Bullet.left < coll.m_rc1.right && coll.m_rc1.left < m_rc_Bullet.right && m_rc_Bullet.top < coll.m_rc1.bottom && coll.m_rc1.top < m_rc_Bullet.bottom)
		{
			dirY = -dirY; BounceCount++;
		}

		CheckAndResolveCollision(m_rc_Bullet, coll.m_rcSleft); // 왼쪽 작은 벽
		CheckAndResolveCollision(m_rc_Bullet, coll.m_rcSright); // 오른쪽 작은 벽
	}
	
	
}

void Bullet::Draw()
{
	// 게임 시작 상태에서만 렌더링
	if (Gmanager.m_GameStart == true)
	{
		Bulletimg.Render(BulletX, BulletY, 0, 1.4f, 1.4f, 1);  //총알 렌더링 (1.4 배 확대)

		// 총알 개수 UI 렌더링 
		for (int i = 0; i < 6; i++)
		{
			// X 좌표: 130 - i*30 (왼쪽으로 갈수록 간격 30씩 좁아짐)
			// 발사된 총알 UI는 투명하게 렌더링
			m_BulletImg[i].Render(map.posX + 130 - i * 30, map.posY - 15, 0, 1, 1, 0, D3DCOLOR_ARGB(Alpha[i], 255, 255, 255));
		}
	}
}

// 발사 명령
void Bullet::Fire(int targetX, int targetY) // 마우스 X좌표 Y좌표 받아오기
{
	delayBullet = GetTickCount64(); // 발사 시간 초기화
	BulletX = player.pos.x; // 총알 초기 위치를 플레이어 위치로 설정
	BulletY = player.pos.y;

	// 목표 지점까지의 벡터 계산 (외부 사이트 (수학 공식) 참고)
	float x = targetX + 20 - BulletX; // 플레이어 위치 ~ 목표 마우스 클릭 지점
	float y = targetY + 40 - BulletY;
	float len = sqrtf(x * x + y * y); // 벡터의 길이 계산

	if (len != 0) // 방향 벡터 정규화 
	{
		// 길이로 나누어 방향 벡터의 크기를 1로 만듭니다.
		dirX = x / len; 
		dirY = y / len;
	}

	// 총알 UI 슬롯 업데이트
	for (int i = 0; i < 6; i++)
    {
     	if (!bulletFired[i])
		{
			bulletFired[i] = true; // 발사 상태 ON
			Alpha[i] = 100; // 투명도 감소
			bulletAlphaTime[i] = GetTickCount64();
			break; // 슬롯 하나만 사용하고 종료
		}
    }
}