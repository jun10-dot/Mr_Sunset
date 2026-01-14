class CMng
{
public:
	CMng();
	~CMng();


	///////////////////////// 스프라이트 객체 ///////////////////

	//////////////////////////////////////////////////////////////

	Chap *chap[TOTALCHAP];
	int n_Chap;
	 
	HWND hWnd;
	HINSTANCE hInstance;

};

extern CMng g_Mng;