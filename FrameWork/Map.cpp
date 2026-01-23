#include "Include.h"

Map map;

Map::Map()
{
	m_Stage = 1; // 초기 스테이지는 1
} 

Map::~Map()
{
}

void Map::Init()
{
	char FileName[256];

	// 공통 배경 및 UI 이미지 로드 //

	sprintf_s(FileName, "./resource/Img/Background-0001.png");
	m_BackgroundImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0)); // 배경

	sprintf_s(FileName, "./resource/Img/Exit.png");
	m_Exit.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0)); // 종료 버튼

	sprintf_s(FileName, "./resource/Img/Reset.png");
	m_Reset.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0)); // 리셋 버튼

	sprintf_s(FileName, "./resource/Img/Menu.png");
	m_Menu.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0)); // 메뉴 버튼

	for (int i = 0; i < 2; i++)
	{
	    sprintf_s(FileName, "./resource/Img/Audio/Audio-%04d.png", i);
	    m_Sound[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0)); // 사운드 On/Off 버튼
    }

	// 스테이지별 맵 이미지 로드 //
	
	//맵 스테이지1
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(FileName, "./resource/Img/map1/BackgroundA-%04d.png",i+1);
		m_Stage1_Img[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	
	//맵스테이지2
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(FileName, "./resource/Img/map2/BackgroundB-%04d.png", i);
		m_Stage2_Img[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	//맵 스테이지3
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(FileName, "./resource/Img/map3/BackgroundC-%04d.png", i);
		m_Stage3_Img[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	//맵 스테이지4
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(FileName, "./resource/Img/map4/BackgroundD-%04d.png", i);
		m_Stage4_Img[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// 리소스 로드 후, 플레이어, 적 배치
	InitStage(); 
}

void Map::InitStage()  //캐릭터와 적을 맵에 배치
{
	switch (m_Stage)
	{
	case 1:
		player.pos = { 250, 200 }; // 플레이어 초기 위치 설정
		AddEnemy(950, 470); // 적 생성 및 배치
		break;
	case 2:
		player.pos = { 700, 600 };
		AddEnemy(400, 0);
		AddEnemy(600, 250);
		break;
	case 3:
		player.pos = { 150, 300 };
		AddEnemy(500, 500);
		AddEnemy(400, 500);
		AddEnemy(300, 500);
		AddEnemy(200, 500);
		AddEnemy(600, 500);
		AddEnemy(700, 500);
		AddEnemy(1000, 500);
		break;

	case 4:
		player.pos = { 310, 500 };
		AddEnemy(650, 530);
		AddEnemy(460, 530);
		break;
	}
}

//적 생성 함수
void Map::AddEnemy(int x, int y)  
{
	Enemy* e = new Enemy(x, y); // Enemy 객체 동적 할당
	e->Init(); // Enemy 객체 초기화
	Gmanager.myList.push_front(e); // 리스트의 맨 앞에 추가
}

void Map::Draw()
{
	// 공통 배경 이미지 렌더링
	if (m_Stage >= 1 && m_Stage <= 4)
	{
		m_BackgroundImg.Render(posX, posY, 0, 1, 1);
	}

	// 스테이지별 전용 이미지 렌더링
	switch (m_Stage)
	{
	case 1:
		m_Stage1_Img[0].Render(posX, posY, 0, 1, 1); // 천장
		m_Stage1_Img[1].Render(posX, posY + 605, 0, 1, 1); // 바닥
		m_Stage1_Img[2].Render(posX + 540, posY + 285, 0, 1, 1); // 중앙 벽
			break;

	case 2:
		m_Stage2_Img[0].Render(posX, posY + 670, 0, 1, 1); // 바닥
		m_Stage2_Img[1].Render(posX, posY, 0, 1, 1);  // 왼쪽 벽
		m_Stage2_Img[1].Render(posX + 1000, posY, 0, 1, 1); // 오른쪽 벽

		m_Stage2_Img[2].Render(posX + 280, posY + 420, 0, 1, 1); // 아래 가로블럭
		m_Stage2_Img[2].Render(posX + 450, posY + 150, 0, 1, 1, 0); // 위 가로블럭
			break;


	case 3:
		m_Stage3_Img[0].Render(posX, posY + 670, 0, 1, 1); // 바닥
		// Collider 클래스에서 업데이트 되는 움직이는 벽의 현재 좌표를 직접 받아 렌더링
		m_Stage3_Img[1].Render(coll.wallXleftMove, coll.wallYleftMove, 0, 1, 1); // 움직이는 왼쪽 벽
		m_Stage3_Img[1].Render(coll.wallXrightMove, coll.wallYrightMove, 0, 1, 1); // 움직이는 오른쪽 벽
			break;

	case 4:
		m_Stage4_Img[0].Render(posX, posY + 670, 0, 1, 1); // 바닥
		m_Stage4_Img[1].Render(posX - 20, posY, 0, 1, 1); // 왼쪽 구조물 벽
		m_Stage4_Img[2].Render(posX + 370, posY + 168, 0, 1, 1); // 왼쪽 작은벽
		m_Stage4_Img[4].Render(posX + 700, posY + 168, 0, 1, 1);// 오른쪽 작은벽
		m_Stage4_Img[5].Render(posX + 1000, posY, 0, 1, 1); // 오른쪽 구조물 벽
		m_Stage4_Img[3].Render(posX, posY, 0, 1, 1); // 천장
			break;
	}
	// UI 버튼 렌더링 (모든 스테이지 공통)
	if (m_Stage >= 1 && m_Stage <= 4)
	{
		m_Exit.Render(posX + 1230, posY + 720, 0, 1, 1);
		m_Reset.Render(posX + 1170, posY + 720, 0, 1, 1);
		m_Menu.Render(posX + 1110, posY + 723, 0, 1, 1); 
		int index = sound.isMuted ? 1 : 0; // 사운드 상태에 따라 렌더링
		m_Sound[index].Render(posX + 1044, posY + 721, 0, 1, 1);
	}
}