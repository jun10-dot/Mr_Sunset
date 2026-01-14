
// 라운드 결과를 처리하고 점수 화면을 표시하는 클래스입니다.
class Result
{
public:
	Result();
	~Result();

	Sprite Score[4];
	float posX, posY;

	bool aliveEnemyExists; // 현재 맵에 살아있는 적 존재 여부
	bool canShow; // 점수 화면 표시 가능 여부
	bool Nextmap; // 다음 맵으로 이동할지 여부
	bool Again; // 현재 맵을 다시 시작할지 여부
	
	void SetShowFlag(bool flag)
	{ canShow = flag; }

	void Init();
	void Update();
	void Draw();
};
extern int BulletCount; 
extern Result result;