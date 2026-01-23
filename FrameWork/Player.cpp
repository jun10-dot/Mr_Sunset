#include "Include.h"


Player player;


Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	isFireBullet = false;
	gravity = 5.75f; // 중력값 설정
	grounded = false;
	m_CurrentFrame = 0;
	m_AnimTime = GetTickCount64(); // 현재 시간으로 애니메이션 타이머 초기화

	char FileName[256];

	// 캐릭터 애니메이션 이미지 로드
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(FileName, "./resource/Img/oh/Sprite-%04d.png", i + 1); 
		playerimg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
		D3DXGetImageInfoFromFile(FileName, &imagesinfo);
	}
	// 총 이미지 로드
	sprintf_s(FileName, "./resource/Img/Gun-0001.png"); 
	Gun.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	D3DXGetImageInfoFromFile(FileName, &imagesinfo);

	// 조준경 이미지 로드
	sprintf_s(FileName, "./resource/Img/Scope-0001.png"); 
	Scope.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	D3DXGetImageInfoFromFile(FileName, &imagesinfo);

	// 초기 충돌 위치 영역 설정
	m_rcPlayer.left = pos.x;
	m_rcPlayer.top = pos.y;
	m_rcPlayer.right = pos.x + imagesinfo.Width;
	m_rcPlayer.bottom = pos.y + imagesinfo.Height;
}

void Player::Update()
{
	// 중력 및 위치 업데이트 (10ms 간격으로 제어)
	if(GetTickCount64() - m_PlayerTime > 10)
	{
		if(!grounded) pos.y += gravity; // 땅이 아니면 중력값만큼 더해 하강
		
		// 캐릭터 이미지가 어디에 위치하는지에 따라 오프셋이 달라짐
		m_rcPlayer.left = pos.x - 45;
		m_rcPlayer.top = pos.y - 50;
		m_rcPlayer.right = pos.x + imagesinfo.Width - 40;
		m_rcPlayer.bottom = pos.y + imagesinfo.Height - 55;

		//캐릭터 바닥 충돌처리
		if (map.m_Stage >= 1 && map.m_Stage <= 4)
		{
			if (m_rcPlayer.left < coll.m_rc.right 
				&& coll.m_rc.left < m_rcPlayer.right 
				&& m_rcPlayer.top < coll.m_rc.bottom 
				&& coll.m_rc.top < m_rcPlayer.bottom) 
				grounded = true;
		}
		m_PlayerTime = GetTickCount64(); // 시간 갱신
	}

    //캐릭터 프레임
	if (GetTickCount64() - m_AnimTime > m_FrameDelay[m_CurrentFrame])
	{
		// 최대 프레임에 도달하면 다시 첫 프레임으로
		m_CurrentFrame = (m_CurrentFrame + 1) % 2;

		m_AnimTime = GetTickCount64(); // 시간 갱신
	}
}


void Player::Draw()
{
	// 게임이 시작 상태일 때만 그리기
	if (Gmanager.m_GameStart == true)
	{
		//총 회전 각도 계산 (외부 자료 (수학 공식) 참고하여 atan2f 함수를 적용했습니다.)
		// 마우스 커서와 캐릭터(총) 위치 사이의 벡터를 구함. 
		float dx = MouseX+20 - (pos.x);   // X 방향 차이 = 마우스x좌표 - 캐릭터 x좌표
		float dy = MouseY+45- (pos.y);   // Y 방향 차이 = 마우스y좌표 - 캐릭터 y좌표
		 angle = atan2f(dy, dx);   // 두 점 사이의 각도를 라디안으로 계산

		playerimg[m_CurrentFrame].Render(pos.x-50, pos.y-50, 0, 1, 1);//캐릭터 이미지 렌더링
		Gun.Render(pos.x, pos.y, angle, 1.5, 1.5, 1); //총 이미지 렌더링 
		Scope.Render(MouseX+20, MouseY+45, 0, 1.0f, 1.0f, 1);//조준경 이미지 렌더링
	}
}