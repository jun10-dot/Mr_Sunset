#include "Include.h"


Collider coll;


Collider::Collider()
{

}

Collider::~Collider()
{
}

void Collider::Init()
{
	
	switch (map.m_Stage) //스테이지별 충돌 영역 초기 값 설정
	{
	case 1:
		//맵 스테이지1
			m_rc.left = 0;  // 바닥 충돌 영역 (좌측 X)
			m_rc.top = 590; // 바닥 충돌 영역 (상단 Y)
			m_rc.right = 1280; // 바닥 충돌 영역 (우측 X) 
			m_rc.bottom = 757; // 바닥 충돌 영역 (하단 Y)


			m_rc1.left = 0; // 천장 충돌 영역 (좌측 X)
			m_rc1.top = 0;  // 천장 충돌 영역 (상단 Y)
			m_rc1.right = 1280; // 천장 충돌 영역 (우측 X)
			m_rc1.bottom = 70; // 천장 충돌 영역 (하단 Y)

			m_rc2.left = 530; // 중앙 벽 충돌 영역 (좌측 X)
			m_rc2.top = 285;  // 중앙 벽 충돌 영역 (상단 Y)
			m_rc2.right = 680; // 중앙 벽 충돌 영역 (우측 X)
			m_rc2.bottom = 605; // 중앙 벽 충돌 영역 (하단 Y)
			break;

	case 2:
		//맵 스테이지2
			m_rc.left = 0;  // 바닥
			m_rc.top = 670; 
			m_rc.right = 1280; 
			m_rc.bottom = 770;

			m_rc2.left = 0; // 왼쪽 경계 벽
			m_rc2.top = 0; 
			m_rc2.right = 280; 
			m_rc2.bottom = 668; 

			m_rc2_1.left = 1000; // 오른쪽 경계 벽
			m_rc2_1.top = 0;  
			m_rc2_1.right = 1280; 
			m_rc2_1.bottom = 668; 

			m_rc_Under.left = 270; // 중앙 아래쪽 가로 벽 
			m_rc_Under.top = 420;
			m_rc_Under.right = 820;
			m_rc_Under.bottom = 500;

			m_rc_Up.left = 450; // 중앙 위쪽 가로 벽
			m_rc_Up.top = 150;
			m_rc_Up.right = 1030;
			m_rc_Up.bottom = 230;
			break;

	case 3:
		//맵 스테이지3
			m_rc.left = 0;  //바닥 
			m_rc.top = 670; 
			m_rc.right = 1280; 
			m_rc.bottom = 770; 

			// 움직이는 벽(Stage 3 벽)의 초기 위치 설정
			wallXleftMove = 412; // 왼쪽 벽
			wallYleftMove = 350;

			wallXrightMove = 696; // 오른쪽 벽
			wallYrightMove = 670;
			break;
		
	case 4:
		//맵 스테이지4
			m_rc.left = 0; // 바닥
			m_rc.top = 660; 
			m_rc.right = 1280; 
			m_rc.bottom = 770; 

			m_rc1.left = 0; // 천장
			m_rc1.top = 0;  
			m_rc1.right = 1280;
			m_rc1.bottom = 70; 

			m_rc2.left = 0; //왼쪽 경계 구조물
			m_rc2.top = 0;  
			m_rc2.right = 260; 
			m_rc2.bottom = 668; 

			m_rc2_1.left = 995; // 오른쪽 경계 구조물
			m_rc2_1.top = 0;  
			m_rc2_1.right = 1280; 
			m_rc2_1.bottom = 668; 

			m_rcSleft.left = 370; // 작은 내부 벽 (왼쪽)
			m_rcSleft.top = 172;
			m_rcSleft.right = 620;
			m_rcSleft.bottom = 680;

			m_rcSright.left = 700; // 작은 내부 벽 (오른쪽)
			m_rcSright.top = 172;
			m_rcSright.right = 1100;
			m_rcSright.bottom = 668;
			break;
	}
}

void Collider::Update()
{
	if (map.m_Stage == 3) 
	{   
		// Update()에 충돌체를 업데이트하는 이유:
		// Init()은 스테이지 시작 시 한 번만 호출되지만, Update()는 매 프레임 호출되므로
		// wallXleftMove, wallYleftMove 등의 변수값이 움직이는 로직에 의해 값이 변경될 때마다
		// 충돌 영역을 실시간으로 업데이트하여 충돌 영역을 보장함.
		
		// 움직이는 왼쪽 벽 충돌 영역 업데이트
		m_rc_Left.left = wallXleftMove;   
		m_rc_Left.top = wallYleftMove;
		m_rc_Left.right = wallXleftMove + 113; // 해당 오프셋은 벽 이미지의 고정 너비
		m_rc_Left.bottom = wallYleftMove + 200; // 고정 높이

		// 움직이는 오른쪽 벽 충돌 영역 업데이트
		m_rc_Right.left = wallXrightMove;
		m_rc_Right.top = wallYrightMove;
		m_rc_Right.right = wallXrightMove + 113;
		m_rc_Right.bottom = wallYrightMove + 200;
	}
}