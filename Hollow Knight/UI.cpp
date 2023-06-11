#include "pch.h"
#include <Texture.h>

#include "UI.h"
UI::UI(const Rectf& viewPort):
	m_ViewPort{ viewPort }, m_GameIsStarted(false), m_StartGameHovered(false)
{
	m_pBackgroundTexture = new Texture("BackgroundMenu.png");
	m_pCursorTexture = new Texture("Cursor.png");
	m_StartGameTexture = new Texture("Start Game", "Supernatural_Knight.ttf",32,Color4f(1.0f,1.0f,1.0f,1.0f));
	m_OptionsTexture = new Texture("Options", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_QuitGameTexture = new Texture("Quit Game", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_LogoTexture = new Texture("Logo.png");
	m_pHoveredTextureLeft = new Texture("HoveredLeft.png");
	m_pHoveredTextureRight = new Texture("HoveredRight.png");
}
UI::~UI()
{
	delete m_pBackgroundTexture;
	delete m_pCursorTexture;
	delete m_StartGameTexture;
	delete m_OptionsTexture;
	delete m_QuitGameTexture;
	delete m_LogoTexture;
	delete m_pHoveredTextureLeft;
	delete m_pHoveredTextureRight;
}
void UI::Draw()
{
	const float verticalOffset = 50.0f;
	const float horizontalOffsetHoveredText = 30.0f;

	m_pBackgroundTexture->Draw();
	m_StartGameTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width/2 - m_StartGameTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
	m_OptionsTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset));
	m_QuitGameTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset));
	m_pCursorTexture->Draw(Point2f(m_CursorPos.x - m_pCursorTexture->GetWidth()/2, m_CursorPos.y - m_pCursorTexture->GetHeight() / 2));
	m_LogoTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_LogoTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height/2 + m_LogoTexture->GetHeight()/5 - verticalOffset));
	
	if (m_StartGameHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width/2 - m_StartGameTexture->GetWidth()/2 - horizontalOffsetHoveredText, m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_StartGameTexture->GetWidth() / 2 + horizontalOffsetHoveredText/5, m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
	}
}
void UI::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	Point2f mousePos{ float( e.x ), float(e.y ) };

	m_CursorPos = mousePos;

	const float verticalOffset = 50.0f;

	Rectf startGameTextPos
	{
		m_ViewPort.left + m_ViewPort.width / 2 - m_StartGameTexture->GetWidth() / 2,
		m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset,
		m_StartGameTexture->GetWidth(),
		m_StartGameTexture->GetHeight()
	};

	if (mousePos.x > startGameTextPos.left && mousePos.y > startGameTextPos.bottom &&
		mousePos.x < startGameTextPos.left + startGameTextPos.width &&
		mousePos.y < startGameTextPos.bottom + startGameTextPos.height)
	{
		m_StartGameHovered = true;
	}
	else
	{
		m_StartGameHovered = false;
	}
}

void UI::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	Point2f mousePos{ float(e.x), float(e.y) };

	m_CursorPos = mousePos;

	const float verticalOffset = 50.0f;

	Rectf startGameTextPos
	{
		m_ViewPort.left + m_ViewPort.width / 2 - m_StartGameTexture->GetWidth() / 2, 
		m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset,
		m_StartGameTexture->GetWidth(),
		m_StartGameTexture->GetHeight()
	};

	if (mousePos.x > startGameTextPos.left && mousePos.y > startGameTextPos.bottom &&
		mousePos.x < startGameTextPos.left + startGameTextPos.width &&
		mousePos.y < startGameTextPos.bottom + startGameTextPos.height)
	{
		m_GameIsStarted = true;
	}
}
bool UI::IsGameStarted() const
{
	return m_GameIsStarted;
}