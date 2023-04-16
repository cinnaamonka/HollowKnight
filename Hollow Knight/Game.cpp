#include "pch.h"

#include "Game.h"
#include "Hud.h"
#include "Avatar.h"
#include "EnemyManager.h"
#include "Level.h"
#include "Camera.h"
#include "EnemyCentipede.h"

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

	m_pAvatar = new Avatar();

	m_Camera = new Camera{ GetViewPort().width,GetViewPort().height };
	m_pLevel = new Level();
	m_Camera->SetLevelBoundaries(m_pLevel->GetBoundaries());
	m_Hud = new Hud{ Point2f(10.0f,200.0f),3 };


	m_EndReached = false;
}

void Game::Cleanup()
{
	delete m_pAvatar;
	delete m_Camera;
	delete m_Hud;
	delete m_pEnemyManager;
	delete m_pLevel;
}

void Game::Update(float elapsedSec)
{

	if (m_EndReached)
		return;

	m_pAvatar->Update(elapsedSec, m_pLevel);
	m_pEnemyManager->Update(elapsedSec);

	if (m_pLevel->HasReachedEnd(m_pAvatar->GetShape()))
	{
		m_EndReached = true;
	}

	DoCollisionTests();
}

void Game::Draw() const
{
	ClearBackground();

	glPushMatrix();

	m_Camera->Transform(m_pAvatar->GetShape(), true);

	glPushMatrix();
	glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 0.1f, 0.0f, 0.0f);

	m_pLevel->DrawBackground();

	glPopMatrix();

	m_pLevel->DrawMiddleground();

	m_pAvatar->Draw();
	m_pEnemyManager->Draw();

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

void Game::DoCollisionTests()
{
	if (m_pAvatar->IsAtacking())
	{
		if (m_pEnemyManager->IsEnemyKilled(m_pAvatar->GetShape()))
		{
			return;
		}
	}
	else if (m_pEnemyManager->HitItem(m_pAvatar->GetShape()))
	{
		m_pAvatar->EnemyHit();
	}

	//m_Hud->PowerUpHit();
	//m_pPowerUp->Play(0);

}


