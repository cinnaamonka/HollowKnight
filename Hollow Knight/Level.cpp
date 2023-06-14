#include "pch.h"
#include <chrono>
#include <SoundStream.h>
#include <SoundEffect.h>
#include <Texture.h>

#include "Level.h"
#include "Game.h"
#include "Avatar.h"
#include "EnemyManager.h"
#include "Environment.h"
#include "Camera.h"
#include "EnemyCentipede.h"
#include "EnemyDragonfly.h"
#include "CoinManager.h"
#include "Coin.h"
#include "Spikes.h"
#include "DoorManager.h"
#include "Door.h"
#include "CoinSource.h"
#include "CoinSourceManager.h"
#include "HUD.h"
#include "UI.h"


Level::Level(const Rectf& viewPort) :
	m_ViewPort(viewPort), m_EndReached(false), m_ZoomLevel(1.0f), m_MusicVolume(100), m_FadingScreenColor{ 0,0,0,0 }
{
	m_pAvatar = nullptr;
	m_pEnemyManager = nullptr;
	m_pEnvironment = nullptr;
	m_Camera = nullptr;
	m_pCoinManager = nullptr;
	m_pDoorManager = nullptr;
	m_pSpikes = nullptr;
	m_pCoinSourceManager = nullptr;
	m_pHUD = nullptr;
	m_pBackgroundSound = nullptr;
	m_EndText = nullptr;
}

Level::~Level()
{
}

void Level::Initialize()
{
	m_pEnemyManager = new EnemyManager();

	AddEnemies();

	m_pCoinManager = new CoinManager();

	m_pCoinSourceManager = new CoinSourceManager();

	AddCoinSources();

	m_pAvatar = new Avatar();

	const Point2f HUDPosition{ 46.0f,460.0f };

	const int livesNumber = 5;

	m_pHUD = new HUD(HUDPosition, livesNumber, m_pCoinManager);

	m_Camera = new Camera{ m_ViewPort.width,m_ViewPort.height };

	m_pEnvironment = new Environment();

	m_Camera->SetLevelBoundaries(m_pEnvironment->GetBoundaries());

	m_pBackgroundSound = new SoundStream("background_Sound.wav");

	const Rectf spikesRect(3150.f, 3100.f, 400.0f, 100.0f);

	m_pSpikes = new Spikes(spikesRect);

	m_pDoorManager = new DoorManager();

	m_EndText = new Texture("EndText.png");

	AddDoors();

	PlaySound();
}

void Level::Cleanup()
{
	delete m_pAvatar;
	delete m_Camera;
	delete m_pEnemyManager;
	delete m_pEnvironment;
	delete m_pCoinManager;
	delete m_pSpikes;
	delete m_pDoorManager;
	delete m_pCoinSourceManager;
	delete m_pHUD;
	delete m_pBackgroundSound;
	delete m_EndText;
}

void Level::Update(float elapsedSec)
{
	if (m_EndReached == true)
	{
		if (m_FadingScreenColor.a < 1)
		{
			m_FadingScreenColor.a += 0.001f;
		}

		return;
	}

	if (!m_pAvatar->isColliding())
	{
		if (m_pAvatar->isFocusing() && m_pHUD->CanAddLife())
		{
			m_ZoomLevel += 0.001f;
			m_pHUD->AddLife();
		}

		else
		{
			m_ZoomLevel = 1.0f;
		}
	}

	m_pCoinManager->HandleCollection(m_pAvatar->GetShape());
	m_pHUD->SetCollectedCoinsAmount(m_pCoinManager->GetCoinsCollectedAmount());
	m_pCoinManager->Update(elapsedSec, m_pEnvironment);

	m_pAvatar->Update(elapsedSec, m_pEnvironment, m_pHUD->CanAddLife());
	m_pEnemyManager->Update(elapsedSec, m_pEnvironment);

	m_pCoinSourceManager->Update(m_pAvatar);
	m_pDoorManager->Update(elapsedSec, m_pAvatar);

	if (m_pEnvironment->HasReachedEnd(m_pAvatar->GetShape()) == true)
	{
		m_EndReached = true;
		m_pAvatar->StopAllSounds();

	}

	CheckAvatarCollison();
}

void Level::Draw() const
{

	ClearBackground();

	
	glPushMatrix();
	{
		glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 0.5f, -m_Camera->GetPosition(m_pAvatar->GetShape()).y * 0.5f, 0.0f);

		m_pEnvironment->DrawBackground();
	}
	glPopMatrix();


	glPushMatrix();
	{

		if (m_pAvatar->isFocusing())
		{

			m_Camera->Scale(m_ZoomLevel, m_ZoomLevel, m_pAvatar->GetShape());
		}
		m_Camera->Transform(m_pAvatar->GetShape(), true);


		m_pEnvironment->DrawMiddleground();

		m_pDoorManager->Draw();
		m_pAvatar->Draw();
		m_pCoinSourceManager->Draw();
		m_pEnemyManager->Draw();
		m_pCoinManager->Draw();

		m_pEnvironment->DrawStaticForeground(m_pAvatar->GetShape());
	}
	glPopMatrix();


	glPushMatrix();
	{
		glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 1.1f, -m_Camera->GetPosition(m_pAvatar->GetShape()).y * 1.02f, 0.0f);

		m_pEnvironment->DrawForeground();

	}
	glPopMatrix();


	if (m_EndReached == true)
	{
		utils::SetColor(m_FadingScreenColor);
		utils::FillRect(m_ViewPort.left, m_ViewPort.bottom, m_ViewPort.width, m_ViewPort.height);
		m_EndText->Draw(Point2f(m_ViewPort.left + m_ViewPort.width/2 - m_EndText->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - m_EndText->GetHeight()/2));
		return;
	}
	
	m_pHUD->Draw();
}

void Level::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{

}
void Level::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{

}

void Level::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Level::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	m_pBackgroundSound->SetVolume(UI::GetMusicVolume());
	m_pEnemyManager->SetSoundVolume(UI::GetSoundVolume());
	m_pAvatar->SetSoundVolume(UI::GetSoundVolume());
	m_pCoinManager->SetSoundVolume(UI::GetSoundVolume());
	m_pDoorManager->SetSoundVolume(UI::GetSoundVolume());
}

void Level::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}

void Level::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Level::AddEnemies()
{
	BaseEnemy* enemy1 = new EnemyCentipede(Point2f{ 4100,2280 });
	BaseEnemy* enemy2 = new EnemyCentipede(Point2f{ 7932,1930 });
	BaseEnemy* enemy3 = new EnemyCentipede(Point2f{ 4304,5269 });
	BaseEnemy* enemy4 = new EnemyDragonfly(Point2f{ 5010,3261 });
	BaseEnemy* enemy5 = new EnemyDragonfly(Point2f{ 8017,5434 });

	m_pEnemyManager->AddItem(enemy1);
	m_pEnemyManager->AddItem(enemy2);
	m_pEnemyManager->AddItem(enemy3);
	m_pEnemyManager->AddItem(enemy4);
	m_pEnemyManager->AddItem(enemy5);
}

void Level::CheckAvatarCollison()
{
	if (m_EndReached)return;
	const Rectf shapeRect = m_pAvatar->GetShape();

	m_pEnemyManager->Atack(shapeRect, m_pAvatar->GetVelocity());

	if (m_pAvatar->IsAtacking())
	{
		if (m_pEnemyManager->IsEnemyKilled(shapeRect))
		{
			AddCoins();
			m_pCoinManager->SetPositions(shapeRect);

			return;
		}
		if (m_pCoinSourceManager->IsCoinSourceDestroyed(shapeRect))
		{
			AddCoins();
			m_pCoinManager->SetPositions(shapeRect);

			return;
		}
	}
	else if (m_pEnemyManager->HitItem(shapeRect))
	{
		if (!m_pAvatar->IsKilled())
		{
			if (!m_pAvatar->isColliding())
			{
				m_pHUD->PowerUpHit();
			}
			m_pAvatar->EnemyHit();
		}
	}

	if (m_pSpikes->IsOverlapping(m_pAvatar->GetShape()) || m_pHUD->GetLeftLifes() <= 0)
	{
		m_pHUD->SetLeftLifesAmount(0);

		m_pAvatar->Die();

		m_pAvatar->SetKilled(true);

	}
}
void Level::AddCoins()
{
	Coin* coin1 = new Coin();
	Coin* coin2 = new Coin();
	Coin* coin3 = new Coin();


	m_pCoinManager->AddItem(coin1);
	m_pCoinManager->AddItem(coin2);
	m_pCoinManager->AddItem(coin3);
}
void Level::AddDoors()
{
	Door* door1 = new Door(Point2f(3720.0f, 2294.0f));
	Door* door2 = new Door(Point2f(4530.0f, 2294.0f));
	Door* door3 = new Door(Point2f(5670.0f, 2294.0f));
	Door* door4 = new Door(Point2f(6620.0f, 2294.0f));

	m_pDoorManager->AddItem(door1);
	m_pDoorManager->AddItem(door2);
	m_pDoorManager->AddItem(door3);
	m_pDoorManager->AddItem(door4);
}
void Level::AddCoinSources()
{
	CoinSource* coinSource1 = new CoinSource(Point2f{ 9698,2500 }, 0);
	CoinSource* coinSource2 = new CoinSource(Point2f{ 3231,4319 }, 1);

	m_pCoinSourceManager->AddItem(coinSource1);
	m_pCoinSourceManager->AddItem(coinSource2);
}
void Level::PlaySound()const
{
	m_pBackgroundSound->Play(true);

}



