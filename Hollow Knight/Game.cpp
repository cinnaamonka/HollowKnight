#include "pch.h"

#include "Game.h"
#include "Avatar.h"
#include "EnemyManager.h"
#include "Level.h"
#include "Camera.h"
#include "EnemyCentipede.h"
#include "CoinManager.h"
#include "Coin.h"
#include "Spikes.h"

Game::Game(const Window& window)
	:BaseGame{ window }, m_EndReached(false)
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_pEnemyManager = new EnemyManager();
	AddEnemies();

	m_pCoinManager = new CoinManager();

	m_pAvatar = new Avatar();

	m_Camera = new Camera{ GetViewPort().width,GetViewPort().height };
	m_pLevel = new Level();
	m_Camera->SetLevelBoundaries(m_pLevel->GetBoundaries());

	m_pSpikes =  new Spikes(Rectf(3150.f,3100.f,400.0f,100.0f));

}

void Game::Cleanup()
{
	delete m_pAvatar;
	delete m_Camera;
	delete m_pEnemyManager;
	delete m_pLevel;
}

void Game::Update(float elapsedSec)
{
	if (m_EndReached)
		return;

	m_pCoinManager->HandleCollection(m_pAvatar->GetShape());
	m_pAvatar->Update(elapsedSec, m_pLevel);
	m_pEnemyManager->Update(elapsedSec);

	if (m_pLevel->HasReachedEnd(m_pAvatar->GetShape()))
	{
		m_EndReached = true;
	}

	CheckAvatarCollison();
}

void Game::Draw() const
{
	ClearBackground();
	
	glPushMatrix();
	glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 0.5f, -m_Camera->GetPosition(m_pAvatar->GetShape()).y * 0.5f, 0.0f);

	m_pLevel->DrawBackground();

	glPopMatrix();


	glPushMatrix();

	m_Camera->Transform(m_pAvatar->GetShape(), true);

	m_pLevel->DrawMiddleground();
	
	m_pAvatar->Draw();
	m_pEnemyManager->Draw();
	m_pCoinManager->Draw();


	glPopMatrix();


	glPushMatrix();

	glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 1.1f, -m_Camera->GetPosition(m_pAvatar->GetShape()).y * 1.02f, 0.0f);

	m_pLevel->DrawForeground();

	glPopMatrix();
	

	if (m_EndReached)
	{
		utils::SetColor(Color4f(0.5f, 0.5f, 0.5f, 0.3f));
		utils::FillRect(GetViewPort().left, GetViewPort().bottom, GetViewPort().width, GetViewPort().height);
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{

}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::AddEnemies()
{
	BaseEnemy* enemy1 = new EnemyCentipede(Point2f{ 4100,2280 });
	BaseEnemy* enemy2 = new EnemyCentipede(Point2f{ 7932,1930 });
	BaseEnemy* enemy3 = new EnemyCentipede(Point2f{ 4304,5269 });

	m_pEnemyManager->AddItem(enemy1);
	m_pEnemyManager->AddItem(enemy2);
	m_pEnemyManager->AddItem(enemy3);
}

void Game::CheckAvatarCollison()
{
	const Rectf shapeRect = m_pAvatar->GetShape();

	if (m_pAvatar->IsAtacking())
	{
		if (m_pEnemyManager->IsEnemyKilled(shapeRect))
		{
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
void Game::AddCoins()
{
	Coin* coin1 = new Coin();
	Coin* coin2 = new Coin();
	Coin* coin3 = new Coin();

	m_pCoinManager->AddItem(coin1);
	m_pCoinManager->AddItem(coin2);
	m_pCoinManager->AddItem(coin3);
}


