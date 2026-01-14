class Bullet
{
   
public:
		Bullet();
	~Bullet();
	float speed; // 총알 현재 속도
	float prevBulletX; // 이전 프레임의 총알 x 좌표
	float prevBulletY; // 이전 프레임의 총알 y 좌표
	float dirX;  //총알의 X축 이동 방향 벡터
	float dirY;  //총알의 Y축 이동 방향 벡터
	float BulletX; //총알의 현재 X 좌표
	float BulletY; //총알의 현재 Y 좌표
	ULONGLONG delayBullet; //총알 발사 후 시간 기록

	bool bulletFired[6]; // 총알 UI 슬롯 발사 상태
	int Alpha[6]; // 총알 UI 투명도
	Sprite m_BulletImg[6]; // 총알 개수 UI 이미지
	ULONGLONG bulletAlphaTime[6]; // 총알 UI 투명도 업데이트 시간 기록

	// 충돌 계산 변수
	float overlapLeft; 
	float overlapRight;
	float overlapTop;
	float overlapBottom;

	Sprite Bulletimg; // 총알 본체 이미지
	int BounceCount; // 충돌체에 튕긴 횟수
	//D3DXIMAGE_INFO  bulletInfo; //총알 이미지 해상도 정보
	
	RECT m_rc_Bullet; // 총알의 충돌 박스

	void Init();
	void Update();
	void Draw();
	bool CheckAndResolveCollision(RECT& bullet_rc, const RECT& wall_rc);
	void Fire(int targetX, int targetY); // 발사 시 방향 벡터 계산 및 초기 위치 설정

}; 
extern Bullet bullet;
extern bool isFireBullet; // 총알 발사 요청 플래그 (마우스 클릭 시)