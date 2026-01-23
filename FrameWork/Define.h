#define SCREEN_WITH 1280	// 화면 가로 픽셀크기
#define SCREEN_HEIGHT 768	// 화면 세로 픽셀크기

#define FRAME 1000
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


enum gamechap
{
	LOGO = 0,
	MENU = 1, 
	GAME = 2,
	OVER = 3,
	TOTALCHAP 
};

enum alphabet
{
	A_, B_, C_, D_, E_, F_, G_, H_, I_, J_, K_, L_
};
enum gamework
{
	INIT = 0,
	WORK = 1,
	DRAW = 2
};