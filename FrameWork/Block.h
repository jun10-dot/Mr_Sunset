class Block
{
private:
	int animTime; //프레임 변경 시간
	int m_CurrentFrame; //현재 출력할 폭발 애니메이션
	int Alpha; // 폭발 시 사라지게 하는 용도
	bool Destroyed; // TNT가 완전히 파괴되어 사라졌는지 여부
public:
	Block();
	~Block();
	Sprite m_tnt; // TNT 블록 이미지
	Sprite m_boom[7]; // 폭발 애니메이션을 위한 7프레임 이미지
	RECT m_rcObject; // TNT 충돌 영역
	
	bool Exploded; //TNT가 폭발 했는지 여부
	bool isTNThit; // TNT가 총알에 맞았고, 현재 폭발 애니메이션이 진행 중인지 여부

	void Init();
	void Update();
	void Draw();
};
extern Block block; 
extern bool isFireBullet; // 총알 발사 플래그 (총알 리셋 시 사용)