#include "pch.h"

#include "Game.h"
#include "Level.h"
#include "UI.h"

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
	m_plevel = new Level(GetViewPort());
	m_pUI = new UI(GetViewPort());
	
	m_plevel->Initialize();

}

void Game::Cleanup()
{
	delete m_pUI;
	m_plevel->Cleanup();
	delete m_plevel;

}
void Game::Update(float elapsedSec)
{
	if (m_pUI->IsGameStarted() == true)
	{
		m_plevel->Update(elapsedSec);
	}
}

void Game::Draw() const
{
	ClearBackground();
	if (m_pUI->IsGameStarted() != true)
	{
		m_pUI->Draw();
	}
	
	if (m_pUI->IsGameStarted() == true)
	{
		m_plevel->Draw();
	}

}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (m_pUI->IsGameStarted() == true)
	{
		m_plevel->ProcessKeyDownEvent(e);
	}

}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{

}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_pUI->ProcessMouseMotionEvent(e);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	m_pUI->ProcessMouseDownEvent(e);
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}




