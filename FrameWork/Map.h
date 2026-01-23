#pragma once
#include "Include.h"

class Map
{

public :
	Map();
	~Map();
	
	Sprite m_BackgroundImg; // 공통 배경 이미지
	Sprite m_Stage1_Img[3]; //스테이지1
	Sprite m_Stage2_Img[3]; //스테이지2
	Sprite m_Stage3_Img[2]; //스테이지3
	Sprite m_Stage4_Img[6]; //스테이지4
	Sprite m_Exit; //종료 버튼 이미지 
	Sprite m_Reset; //리셋 버튼 이미지
	Sprite m_Menu; //메뉴 버튼 이미지
	Sprite m_Sound[2]; //사운드 On/Off 이미지

	int m_Stage; // 현재 스테이지 번호

	float posX, posY; // 맵의 전체 오프셋

	void Init();
	void InitStage();
	void AddEnemy(int x, int y); // 특정 좌표에 적을 생성하고 리스트에 추가 
	void Draw();
};

extern Map map;