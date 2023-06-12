#include "pch.h"
#include <Texture.h>

#include "UI.h"
UI::UI(const Rectf& viewPort):
	m_ViewPort{ viewPort }, m_GameIsStarted(false), m_StartGameHovered(false), m_OptionsHovered(false), m_QuitGameHovered(false),
	m_OptionsClicked(false)
{
	m_pBackgroundTexture = new Texture("BackgroundMenu.png");
	m_pCursorTexture = new Texture("Cursor.png");
	m_StartGameTexture = new Texture("Start Game", "Supernatural_Knight.ttf",32,Color4f(1.0f,1.0f,1.0f,1.0f));
	m_OptionsTexture = new Texture("Options", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_QuitGameTexture = new Texture("Quit Game", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_LogoTexture = new Texture("Logo.png");
	m_pHoveredTextureLeft = new Texture("HoveredLeft.png");
	m_pHoveredTextureRight = new Texture("HoveredRight.png");
	m_pAudioTexture = new Texture("Audio", "Supernatural_Knight.ttf", 40, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_pDecorationTexture = new Texture("DecorationUI.png");
	m_pMusicAdjustmentTexture = new Texture("Music Volume", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSoundAdjustmentTexture = new Texture("Sound Volume", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
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
	delete m_pAudioTexture;
	delete m_pDecorationTexture;
	delete m_pMusicAdjustmentTexture;
	delete m_pSoundAdjustmentTexture;
}
void UI::Draw()
{
	const float verticalOffset = 50.0f;
	const float horizontalOffsetHoveredText = 30.0f;
	
	m_pBackgroundTexture->Draw();

	if (m_OptionsClicked)
	{
		m_pAudioTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_pAudioTexture->GetWidth()/2,
									  m_ViewPort.bottom + m_ViewPort.height / 2 + 4 * verticalOffset));
		m_pDecorationTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_pDecorationTexture->GetWidth() / 2,
										   m_ViewPort.bottom + m_ViewPort.height / 2 + 2.2f * m_pDecorationTexture->GetHeight()));
		m_pMusicAdjustmentTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - 1.5f * m_pMusicAdjustmentTexture->GetWidth(),
												m_ViewPort.bottom + m_ViewPort.height / 2 + m_pDecorationTexture->GetHeight()));
		m_pSoundAdjustmentTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - 1.5f * m_pMusicAdjustmentTexture->GetWidth(),
			m_ViewPort.bottom + m_ViewPort.height / 2 - m_pSoundAdjustmentTexture->GetHeight()));
	}

	if (m_OptionsClicked)return;
	m_StartGameTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width/2 - m_StartGameTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
	m_OptionsTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset));
	m_QuitGameTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset));
	m_pCursorTexture->Draw(Point2f(m_CursorPos.x - m_pCursorTexture->GetWidth()/2, m_CursorPos.y - m_pCursorTexture->GetHeight() / 2));
	m_LogoTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_LogoTexture->GetWidth()/2, m_ViewPort.bottom + m_ViewPort.height/2 + m_LogoTexture->GetHeight()/5 - verticalOffset));
	
	
	if (m_StartGameHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width/2 - m_StartGameTexture->GetWidth()/2 - horizontalOffsetHoveredText, 
											m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_StartGameTexture->GetWidth() / 2 + horizontalOffsetHoveredText/5, 
										     m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
	}
	if (m_OptionsHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth() + horizontalOffsetHoveredText, 
											m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_OptionsTexture->GetWidth() / 2 + horizontalOffsetHoveredText/6, 
											 m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset));
	}
	if(m_QuitGameHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth()/2 - verticalOffset/1.5f,
											m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_QuitGameTexture->GetWidth() / 2 + verticalOffset/6,
											 m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset));
	}
}
void UI::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	Point2f mousePos{ float( e.x ), float(e.y ) };

	m_CursorPos = mousePos;

	const float verticalOffset = 50.0f;

	Rectf startGameTextShape
	{
		m_ViewPort.left + m_ViewPort.width / 2 - m_StartGameTexture->GetWidth() / 2,
		m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset,
		m_StartGameTexture->GetWidth(),
		m_StartGameTexture->GetHeight()
	};
	Rectf optionsTextShape
	{
		m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth() / 2,
		m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset,
		m_OptionsTexture->GetWidth(),
		m_OptionsTexture->GetHeight()
	};
	Rectf quitTextShape
	{
		m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth() / 2, 
		m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset,
		m_QuitGameTexture->GetWidth(),
		m_QuitGameTexture->GetHeight()
	};
	//Check is clicked StartGame
	if (mousePos.x > startGameTextShape.left && mousePos.y > startGameTextShape.bottom &&
		mousePos.x < startGameTextShape.left + startGameTextShape.width &&
		mousePos.y < startGameTextShape.bottom + startGameTextShape.height)
	{
		m_StartGameHovered = true;
	}
	else
	{
		m_StartGameHovered = false;
	}
	//Check is clicked Options
	if (mousePos.x > optionsTextShape.left && mousePos.y > optionsTextShape.bottom &&
		mousePos.x < optionsTextShape.left + optionsTextShape.width &&
		mousePos.y < optionsTextShape.bottom + optionsTextShape.height)
	{
		m_OptionsHovered = true;
	}
	else
	{
		m_OptionsHovered = false;
	}
	//Check is clicked QuitGame
	if (mousePos.x > quitTextShape.left && mousePos.y > quitTextShape.bottom &&
		mousePos.x < quitTextShape.left + quitTextShape.width &&
		mousePos.y < quitTextShape.bottom + quitTextShape.height)
	{
		m_QuitGameHovered = true;
	}
	else
	{
		m_QuitGameHovered = false;
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

	Rectf quitTextShape
	{
		m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth() / 2,
		m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset,
		m_QuitGameTexture->GetWidth(),
		m_QuitGameTexture->GetHeight()
	};
	Rectf optionsTextShape
	{
	    m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth() / 2,
		m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset,
		m_OptionsTexture->GetWidth(),
		m_OptionsTexture->GetHeight()
	};
	

	//Check if startGame clicked
	if (mousePos.x > startGameTextPos.left && mousePos.y > startGameTextPos.bottom &&
		mousePos.x < startGameTextPos.left + startGameTextPos.width &&
		mousePos.y < startGameTextPos.bottom + startGameTextPos.height)
	{
		m_GameIsStarted = true;
	}

	if (mousePos.x > quitTextShape.left && mousePos.y > quitTextShape.bottom &&
		mousePos.x < quitTextShape.left + quitTextShape.width &&
		mousePos.y < quitTextShape.bottom + quitTextShape.height)
	{
		m_GameIsQuit = true;
		
	}
	else
	{
		m_GameIsQuit = false;
	}
	
	if (mousePos.x > optionsTextShape.left && mousePos.y > optionsTextShape.bottom &&
		mousePos.x < optionsTextShape.left + optionsTextShape.width &&
		mousePos.y < optionsTextShape.bottom + optionsTextShape.height)
	{
		m_OptionsClicked = true;

	}
	else
	{
		m_OptionsClicked = false;
	}
}
bool UI::IsGameStarted() const
{
	return m_GameIsStarted;
}
bool UI::IsGameQuit() const
{
	return m_GameIsQuit;
}