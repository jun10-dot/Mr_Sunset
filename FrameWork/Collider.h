#pragma once
#include "Include.h"

class Collider
{


public :
	Collider();
	~Collider();
	int wallXleftMove; // 맵 3 스테이지에서 움직이는 왼쪽 벽의 X 좌표
	int wallYleftMove; // " " 왼쪽 벽의 Y 좌표
	int wallXrightMove; // " " 오른쪽 벽의 X 좌표
	int wallYrightMove; // " " 오른쪽 벽의 Y 좌표

	// 스테이지 1
	RECT m_rc; //바닥 충돌 영역 (바닥 있는 모든 스테이지에 적용)
	RECT m_rc1; //천장 충돌 영역 (스테이지 1, 4)
	RECT m_rc2; //중앙 벽 충돌 영역 (스테이지 1, 2, 4)

	// 스테이지 2 
	RECT m_rc2_1; //맵 스테이지2 벽 (스테이지 2, 4)
	RECT m_rc_Under; //아래 가로블럭
	RECT m_rc_Up; //위 가로 블럭

	// 스테이지 3 
	RECT m_rc_Left; //맵 스테이지3
	RECT m_rc_Right;//맵 스테이지3

	//스테이지 4 
	RECT m_rcSleft; //작은 왼쪽 중앙 벽
	RECT m_rcSright; //작은 오른쪽 중앙 벽
	void Init();
	void Update();
};

extern Collider coll;