#ifndef __Logo_H__
#define __Logo_H__

class Logo : public Chap
{
private:
	int currentFrame = 0; // 현재 출력할 프레임
	float frameTime = 0; // 프레임 누적 시간
	float frameDelay = 0.1f; // 다음 프레임으로 전환할 시간 간격
public:
	Logo();
	~Logo();

	Sprite loadimg[4];
	 
	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);
};
#endif