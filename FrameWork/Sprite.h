class Sprite
{
public:
	Sprite(void);
	~Sprite(void);
 
	IDirect3DTexture9 *Texture;
	D3DXIMAGE_INFO imagesinfo;
	D3DCOLOR color;

	bool Create(const char* filename, bool bUseTransparency, D3DCOLOR TransparencyColor);

	void Draw( float dx , float dy , LONG sx , LONG sy , LONG sw , LONG sh, float centerX = 0, float centerY = 0 ); // #92

	void Draw(float x, float y); 
	 
	void Render(float x, float y, float radian, float sx, float sy, int pivotMode = 0, D3DCOLOR tintColor = D3DCOLOR_ARGB(255, 255, 255, 255));

	void RenderDraw( float x , float  y , LONG  sx , LONG  sy , LONG  sw , LONG  sh, float  radian, float  sl, float  st) ;

	void SetColor( int r , int g , int b , int a );

	void Destroy();
};

extern Sprite g_Load;