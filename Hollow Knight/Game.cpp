#include "pch.h"

#include "Game.h"
#include "Hud.h"
#include "Avatar.h"
#include "PowerUpManager.h"
#include "Level.h"

#include <iostream>
#include <utils.h>

Game::Game(const Window& window)
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	ShowTestMessage();
	AddPowerUps();

	m_pAvatar = new Avatar();
	m_pPowerUpManager = new PowerUpManager();
	m_Camera = new Camera{ GetViewPort().width,GetViewPort().height };
	m_pLevel = new Level();
	m_Camera->SetLevelBoundaries(m_pLevel->GetBoundaries());
	m_Hud = new Hud{ Point2f(10.0f,200.0f),3 };
	
	m_EndReached = false;
	//m_pPowerUp = new SoundEffect{ "powerUp.mp3" };
}

void Game::Cleanup()
{
	delete m_pAvatar;
	delete m_Camera;
	delete m_Hud;
	delete m_pPowerUpManager;
	delete m_pLevel;
}

void Game::Update(float elapsedSec)
{
	// Update game objects

	if (m_EndReached) return;

	m_pAvatar->Update(elapsedSec, m_pLevel);
	m_pPowerUpManager->Update(elapsedSec);

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

	
	m_Camera->Transform(m_pAvatar->GetShape(),true);
	
	glPushMatrix();
	glTranslatef(-m_Camera->GetPosition(m_pAvatar->GetShape()).x * 0.1f, 0.0f, 0.0f);
	m_pLevel->DrawBackground();

	glPopMatrix();

	m_pLevel->DrawMiddleground();
	m_pAvatar->Draw();
	m_pLevel->DrawForeground();

	m_pPowerUpManager->Draw();

	glPopMatrix();

	//m_Hud->Draw();
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


void Game::ShowTestMessage() const
{
	std::cout << "--> Avatar test <--\n";
	std::cout << "Verify that the avatar behaves as follows.\n";
	std::cout << "- Moves along the level when the left/right arrow is pressed.\n";
	std::cout << "- Doesn't move when it is on the ground and no key is pressed.\n";
	std::cout << "- Jumps only when it is on the ground and the up arrow key is pressed.\n";
	std::cout << "- Doesn't move during 1 second when hitting a power up.\n";
	std::cout << "- Starts moving again ( e.g. falling ) after this second.\n";
	std::cout << "- The number of small rectangles in the bottom left corner is equal to the number of hit power ups.\n";
	std::cout << "- Has a red color when it is moving.\n";
	std::cout << "- Has a yellow color when it is waiting.\n";
	std::cout << "- Has a blue color when it is transforming.\n";

}

void Game::AddPowerUps()
{
	//m_PowerUpManager->AddItem(Point2f{ 2400,2100 });
	/*m_PowerUpManager.AddItem(Point2f{ 435.0f, 500 - 133.0f }, PowerUp::Type::green);
	m_PowerUpManager.AddItem(Point2f{ 685.0f, 500 - 183.0f }, PowerUp::Type::brown);*/
}

void Game::DoCollisionTests()
{
	if (m_pPowerUpManager->HitItem(m_pAvatar->GetShape()))
	{
		//m_Hud->PowerUpHit();
		//m_Avatar.PowerUpHit( );
		//m_pPowerUp->Play(0);

	}
}

