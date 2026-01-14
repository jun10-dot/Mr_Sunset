#include "Include.h"

Sound sound;

Sound::Sound()
{
}

Sound::~Sound()
{
}
void Sound::Update()
{
	// 음소거 상태가 아니고, 사운드 객체가 로드되었으며, 총알 발사 요청이 들어왔을 경우
	if (!isMuted && m_Shot && BulletSound)
	{
		m_Shot->Play(0, 0); //총알 발사 사운드
		BulletSound = false; //플래그 초기화
	}

	// "", "", 아직 재생 시작이 안 된 경우
	if (!isMuted && m_Bk1 && !soundinit)
	{
		m_Bk1->Play(0, DSBPLAY_LOOPING); //배경음악 무한 반복 재생
		soundinit = true; 
	}
	//"", "", TNT 폭발 플래그 사용한 경우
	if (!isMuted && m_Boom && block.isTNThit)
	{
		m_Boom->Play(0, 0);
	}

	//적 리스트를 순회하며 적이 있는지 확인합니다.
	for (auto enemy : Gmanager.myList)
	{
		if (!isMuted && enemy->isDead)
		{	
			// 적 사망 사운드의 다중 재생을 위한 처리
			m_EnemyDieArray[m_EnemyDieIndex]->Play(0, 0, 0);
			// 다음 사운드 객체를 가리키도록 인덱스를 순환
			m_EnemyDieIndex = (m_EnemyDieIndex + 1) % 4;
			//중복 재생을 방지합니다.
			enemy->isDead = false;
		}
	}
}
void Sound::Init()
{
	if (m_Bk1 != nullptr) // 다음 라운드 진입 시 배경음악 또 재생되는 것을 방지하기 위해
		return;
	
	g_pSoundManager = new CSoundManager();
	g_pSoundManager->Initialize(g_hWnd, DSSCL_PRIORITY); //DSSCL_PRIORITY로 초기화
	g_pSoundManager->SetPrimaryBufferFormat(2, 22050, 16); //버퍼 설정

	// 사운드 리소스 로드
	g_pSoundManager->Create(&m_Bk1, (LPWSTR)L"./resource/Sound/BGM_0000.wav", 0, GUID_NULL);
	g_pSoundManager->Create( &m_Shot, (LPWSTR)L"./resource/Sound/shot.wav", 0, GUID_NULL ) ;
	g_pSoundManager->Create(&m_Boom, (LPWSTR)L"./resource/Sound/explosion.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_GunShot, (LPWSTR)L"./resource/Sound/Backgroundshot-0001.wav", 0, GUID_NULL);

	// 적 사망 사운드 배열 로드
	for (int i = 0; i < 4; i++)
	{
		g_pSoundManager->Create(&m_EnemyDieArray[i], L"./resource/Sound/enemydie_0001.wav", 0);
	}
}

void Sound::StopAll()
{
	if (m_Bk1) m_Bk1->Stop(); 
	isMuted = true; // 전체 음소거 상태로 전환
}

void Sound::PlayGunShot()
{
	if (m_GunShot) {
		m_GunShot->Play(0, 0);
	}
}