#include "pch.h"

#include "Game.h"
#include "Level.h"

Game::Game(const Window& window)
	:BaseGame{ window }
{
	m_plevel = new Level(GetViewPort());
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_plevel->Initialize();
}

void Game::Cleanup()
{
	m_plevel->Cleanup();
}
void Game::Update(float elapsedSec)
{
	m_plevel->Update(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	m_plevel->Draw();
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




