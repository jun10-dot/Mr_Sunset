#pragma once

class Sound
{
private:
	CSound* m_EnemyDieArray[4]; // 다중 재생을 위해 배열 선언

public:
	Sound(void);
	~Sound(void);
	int m_EnemyDieIndex = 0;
	
    CSoundManager* g_pSoundManager; // DirectSound 기반 사운드 관리자
    CSound*	m_Bk1; // 배경 음악
    CSound*	m_Shot; // 플레이어 총알 발사 사운드
    CSound* m_GunShot; //게임 로고 화면 발사 사운드 
    CSound* m_Boom; // 폭발 사운드

    bool soundinit; // 배경음악 초기 재생 여부 (무한 반복 재생)
    bool isMuted; // 게임 전체 음소거 상태 플래그

	void Init();
	void Update();
	void StopAll(); // 모든 사운드 재생 중지 메서드
	void PlayGunShot(); //발사 사운드 재생 메서드
}; 
extern HWND g_hWnd; // DirectSound 초기화에 필요
extern bool BulletSound; // 총알 발사 요청 플래그
extern Sound sound;