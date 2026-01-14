#ifndef __Over_H__
#define __Over_H__

class Over : public Chap
{
private:	
	DWORD totalTime; // 총 게임 플레이 시간
	DWORD seconds; // 초 
	DWORD minutes; // 분 
public:
	Over();
	~Over();
	Sprite overimg;  // Over 화면 배경 이미지
	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();
	virtual void OnMessage(MSG* msg); // 마우스 입력 처리
};

#endif