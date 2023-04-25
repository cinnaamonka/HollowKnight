#include "pch.h"

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

Level::Level(const Rectf& viewPort) :
	m_ViewPort{ viewPort }, m_EndReached{ false }
{

	Initialize();
}

Level::~Level()
{
	Cleanup();
}

void Level::Initialize()
{

	m_pEnemyManager = new EnemyManager();
	AddEnemies();

	m_pCoinManager = new CoinManager();

	m_pAvatar = new Avatar();

	m_Camera = new Camera{ m_ViewPort.width,m_ViewPort.height };
	m_pEnvironment = new Environment();
	m_Camera->SetLevelBoundaries(m_pEnvironment->GetBoundaries());

	const Rectf spikesRect(3150.f, 3100.f, 400.0f, 100.0f);

	m_pSpikes = new Spikes(spikesRect);

}

void Level::Cleanup()
{
	delete m_pAvatar;
	delete m_Camera;
	delete m_pEnemyManager;
	delete m_pEnvironment;
	delete m_pCoinManager;
	delete m_pSpikes;

}

void Level::Update(float elapsedSec)
{
	if (m_EndReached)
		return;

	m_pCoinManager->HandleCollection(m_pAvatar->GetShape());
	m_pCoinManager->Update(elapsedSec, m_pEnvironment);
	m_pAvatar->Update(elapsedSec, m_pEnvironment);
	m_pEnemyManager->Update(elapsedSec, m_pEnvironment);

	if (m_pEnvironment->HasReachedEnd(m_pAvatar->GetShape()))
	{
		m_EndReached = true;
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
		m_Camera->Transform(m_pAvatar->GetShape(), true);

		m_pEnvironment->DrawMiddleground();

		m_pAvatar->Draw();
		m_pEnemyManager->Draw();
		m_pCoinManager->Draw();
		m_pEnvironment->DrawStaticForeground();
	}
	glPopMatrix();


	glPushMatrix();
	{
		glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 1.1f, -m_Camera->GetPosition(m_pAvatar->GetShape()).y * 1.02f, 0.0f);

		m_pEnvironment->DrawForeground();

	}
	glPopMatrix();


	if (m_EndReached)
	{
		utils::SetColor(Color4f(0.5f, 0.5f, 0.5f, 0.3f));
		utils::FillRect(m_ViewPort.left, m_ViewPort.bottom, m_ViewPort.width, m_ViewPort.height);
	}
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
	const Rectf shapeRect = m_pAvatar->GetShape();

	m_pEnemyManager->Atack(shapeRect, m_pAvatar->GetVelocity());

	if (m_pAvatar->IsAtacking())
	{
		if (m_pEnemyManager->IsEnemyKilled(shapeRect))
		{
			// pass as parameter into manager
			AddCoins();
			m_pCoinManager->SetPositions(shapeRect);

			return;
		}
	}
	else if (m_pEnemyManager->HitItem(shapeRect))
	{
		m_pAvatar->EnemyHit();
	}

	if (m_pSpikes->IsOverlapping(m_pAvatar->GetShape()))
	{
		m_pAvatar->Die();
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



