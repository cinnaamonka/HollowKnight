#include "pch.h"
#include <Texture.h>
#include <SoundEffect.h>

#include "UI.h"

int UI::m_MusicVolume{ 95 };
int UI::m_SoundVolume{ 95 };

UI::UI(const Rectf& viewPort) :
	m_ViewPort{ viewPort }, m_GameIsStarted(false), m_StartGameHovered(false), m_OptionsHovered(false), m_QuitGameHovered(false),
	m_OptionsClicked(false), m_GameIsQuit(false), m_BackHovered(false)
{
	m_pBackgroundTexture = new Texture("BackgroundMenu.png");
	m_pCursorTexture = new Texture("Cursor.png");
	m_StartGameTexture = new Texture("Start Game", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_OptionsTexture = new Texture("Options", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_QuitGameTexture = new Texture("Quit Game", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_LogoTexture = new Texture("Logo.png");
	m_pHoveredTextureLeft = new Texture("HoveredLeft.png");
	m_pHoveredTextureRight = new Texture("HoveredRight.png");
	m_pAudioTexture = new Texture("Audio", "Supernatural_Knight.ttf", 40, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_pDecorationTexture = new Texture("DecorationUI.png");
	m_pMusicAdjustmentTexture = new Texture("Music Volume", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSoundAdjustmentTexture = new Texture("Sound Volume", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectSound = new SoundEffect("UIOptionSelected.wav");
	m_pBackTexture = new Texture("Back", "Supernatural_Knight.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_SoundBar = new Texture("Bar.png");
	m_pChangeSound = new SoundEffect("UIHover.wav");

	const float verticalOffset = 50.0f;

	m_StartGameTextShape = Rectf{ m_ViewPort.left + m_ViewPort.width / 2 - m_StartGameTexture->GetWidth() / 2,
								  m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset,
								  m_StartGameTexture->GetWidth(),
								  m_StartGameTexture->GetHeight() };

	m_OptionsTextShape = Rectf{ m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth() / 2,
								m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset,
								m_OptionsTexture->GetWidth(),
								m_OptionsTexture->GetHeight() };

	m_QuitTextShape = Rectf{ m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth() / 2,
							 m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset,
							 m_QuitGameTexture->GetWidth(),
		m_QuitGameTexture->GetHeight() };

	m_BackTextShape = Rectf{ m_ViewPort.left + m_ViewPort.width / 2 - m_pBackTexture->GetWidth() / 2,
							 m_ViewPort.bottom + m_ViewPort.height / 2 - 4 * verticalOffset,
							 m_pBackTexture->GetWidth(),
							 m_pBackTexture->GetHeight() };

	m_BarAdjustementMusicRight = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 + 2 * m_pMusicAdjustmentTexture->GetWidth() / 1.4f,
		m_ViewPort.bottom + m_ViewPort.height / 2 + 1.4f * verticalOffset };
	m_BarAdjustementMusicLeft = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 + 3 * m_pHoveredTextureLeft->GetWidth(),
		m_ViewPort.bottom + m_ViewPort.height / 2 + 1.3f * verticalOffset };
	m_BarAdjustementSoundRight = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 + 2 * m_pMusicAdjustmentTexture->GetWidth() / 1.4f,
		m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset };
	m_BarAdjustementSoundLeft = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 + 3 * m_pHoveredTextureLeft->GetWidth(),
		m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset };

	m_pMusicAdjustmentPos = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 - 1.5f * m_pMusicAdjustmentTexture->GetWidth(),
		m_ViewPort.bottom + m_ViewPort.height / 2 + m_pDecorationTexture->GetHeight() };
	m_pSoundAdjustmentPos = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 - 1.5f * m_pMusicAdjustmentTexture->GetWidth(),
		m_ViewPort.bottom + m_ViewPort.height / 2 - m_pSoundAdjustmentTexture->GetHeight() };

	m_LogoStartScreenPos = Point2f{ m_ViewPort.left + m_ViewPort.width / 2 - m_LogoTexture->GetWidth() / 2,
		m_ViewPort.bottom + m_ViewPort.height / 2 + m_LogoTexture->GetHeight() / 5 - verticalOffset };


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
	delete m_pBackTexture;
	delete m_SoundBar;
	delete m_pSelectSound;
}
void UI::Draw() const
{
	const float verticalOffset = 50.0f;
	const float horizontalOffsetHoveredText = 30.0f;

	m_pBackgroundTexture->Draw();
	DrawAudioScreen(verticalOffset, horizontalOffsetHoveredText);

	const Point2f cursorPos
	{
		m_CursorPos.x - m_pCursorTexture->GetWidth() / 2,
		m_CursorPos.y - m_pCursorTexture->GetHeight() / 2
	};

	m_pCursorTexture->Draw(cursorPos);

	if (m_OptionsClicked)return;

	DrawFirstScreen(verticalOffset, horizontalOffsetHoveredText);

}
void UI::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{

	Point2f mousePos{ float(e.x), float(e.y) };

	m_CursorPos = mousePos;


	//Check is clicked StartGame
	if (mousePos.x > m_StartGameTextShape.left && mousePos.y > m_StartGameTextShape.bottom &&
		mousePos.x < m_StartGameTextShape.left + m_StartGameTextShape.width &&
		mousePos.y < m_StartGameTextShape.bottom + m_StartGameTextShape.height)
	{
		m_StartGameHovered = true;
		
		m_pChangeSound->Play(0);

	}
	else
	{
		m_StartGameHovered = false;
		m_pChangeSound->Stop();
	}
	//Check is clicked Options
	if (mousePos.x > m_OptionsTextShape.left && mousePos.y > m_OptionsTextShape.bottom &&
		mousePos.x < m_OptionsTextShape.left + m_OptionsTextShape.width &&
		mousePos.y < m_OptionsTextShape.bottom + m_OptionsTextShape.height)
	{
		m_OptionsHovered = true;
		m_pChangeSound->Play(0);
	}
	else
	{
		m_OptionsHovered = false;
		
	}
	//Check is clicked QuitGame
	if (mousePos.x > m_QuitTextShape.left && mousePos.y > m_QuitTextShape.bottom &&
		mousePos.x < m_QuitTextShape.left + m_QuitTextShape.width &&
		mousePos.y < m_QuitTextShape.bottom + m_QuitTextShape.height)
	{
		m_QuitGameHovered = true;
		m_pChangeSound->Play(0);
	}
	else
	{
		m_QuitGameHovered = false;
		
	}
	//Check is clicked back
	if (mousePos.x > m_BackTextShape.left && mousePos.y > m_BackTextShape.bottom &&
		mousePos.x < m_BackTextShape.left + m_BackTextShape.width &&
		mousePos.y < m_BackTextShape.bottom + m_BackTextShape.height)
	{
		m_BackHovered = true;
		m_pChangeSound->Play(0);
	}
	else
	{
		m_BackHovered = false;
		
	}
}

void UI::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{

	Point2f mousePos{ float(e.x), float(e.y) };

	m_CursorPos = mousePos;

	const float verticalOffset = 50.0f;
	const float maxMusicVolume = 171.f;
	const float musicVolumeStep = 19.f;
	
	Rectf rightArrowShapeMusic
	{
		m_BarAdjustementMusicRight.x,
		m_BarAdjustementMusicRight.y,
		2 * m_pHoveredTextureRight->GetWidth(),
		2 * m_pHoveredTextureRight->GetHeight()
	};
	Rectf leftArrowShapeMusic
	{
		m_BarAdjustementMusicLeft.x,
		m_BarAdjustementMusicLeft.y,
		2 * m_pHoveredTextureLeft->GetWidth(),
		2 * m_pHoveredTextureLeft->GetHeight()
	};
	Rectf rightArrowShapeSound
	{
		m_BarAdjustementSoundRight.x,
		m_BarAdjustementSoundRight.y,
		2 * m_pHoveredTextureRight->GetWidth(),
		2 * m_pHoveredTextureRight->GetHeight()
	};
	Rectf leftArrowShapeSound
	{
		m_BarAdjustementSoundLeft.x,
		m_BarAdjustementSoundLeft.y,
		2 * m_pHoveredTextureLeft->GetWidth(),
		2 * m_pHoveredTextureLeft->GetHeight()
	};

	if (mousePos.x > m_BackTextShape.left && mousePos.y > m_BackTextShape.bottom &&
		mousePos.x < m_BackTextShape.left + m_BackTextShape.width &&
		mousePos.y < m_BackTextShape.bottom + m_BackTextShape.height)
	{
		m_OptionsClicked = false;
		m_pChangeSound->Stop();
		m_pChangeSound->SetVolume(m_SoundVolume);
		m_pChangeSound->Play(0);
	}

	if ((mousePos.x > rightArrowShapeMusic.left && mousePos.y > rightArrowShapeMusic.bottom &&
		mousePos.x < rightArrowShapeMusic.left + rightArrowShapeMusic.width &&
		mousePos.y < rightArrowShapeMusic.bottom + rightArrowShapeMusic.height) && m_MusicVolume <= maxMusicVolume)
	{
		m_pChangeSound->Stop();
		m_pChangeSound->Play(0);
		m_MusicVolume += musicVolumeStep;
	}
	if ((mousePos.x > rightArrowShapeSound.left && mousePos.y > rightArrowShapeSound.bottom &&
		mousePos.x < rightArrowShapeSound.left + rightArrowShapeSound.width &&
		mousePos.y < rightArrowShapeSound.bottom + rightArrowShapeSound.height) && m_SoundVolume <= maxMusicVolume)
	{
		m_pChangeSound->Stop();
		m_pChangeSound->Play(0);
		m_SoundVolume += musicVolumeStep;
		m_pChangeSound->SetVolume(m_SoundVolume);
	}
	if ((mousePos.x > leftArrowShapeMusic.left && mousePos.y > leftArrowShapeMusic.bottom &&
		mousePos.x < leftArrowShapeMusic.left + leftArrowShapeMusic.width &&
		mousePos.y < leftArrowShapeMusic.bottom + leftArrowShapeMusic.height) && m_MusicVolume > 0)
	{
		m_pChangeSound->Stop();
		m_pChangeSound->Play(0);
		m_MusicVolume -= musicVolumeStep;
	}
	if ((mousePos.x > leftArrowShapeSound.left && mousePos.y > leftArrowShapeSound.bottom &&
		mousePos.x < leftArrowShapeSound.left + leftArrowShapeSound.width &&
		mousePos.y < leftArrowShapeSound.bottom + leftArrowShapeSound.height) && m_SoundVolume > 0)
	{
		m_pChangeSound->Stop();
		m_pChangeSound->Play(0);
		m_SoundVolume -= musicVolumeStep;
		m_pChangeSound->SetVolume(m_SoundVolume);
	}


	if (m_OptionsClicked)return;

	//Check if startGame clicked
	if (mousePos.x > m_StartGameTextShape.left && mousePos.y > m_StartGameTextShape.bottom &&
		mousePos.x < m_StartGameTextShape.left + m_StartGameTextShape.width &&
		mousePos.y < m_StartGameTextShape.bottom + m_StartGameTextShape.height)
	{
		m_GameIsStarted = true;
		m_pSelectSound->Stop();
		m_pSelectSound->SetVolume(m_SoundVolume);
		m_pSelectSound->Play(0);
	}

	if (mousePos.x > m_QuitTextShape.left && mousePos.y > m_QuitTextShape.bottom &&
		mousePos.x < m_QuitTextShape.left + m_QuitTextShape.width &&
		mousePos.y < m_QuitTextShape.bottom + m_QuitTextShape.height)
	{
		m_GameIsQuit = true;
	}
	else
	{
		m_GameIsQuit = false;
	}

	//check if options text clicked
	if (mousePos.x > m_OptionsTextShape.left && mousePos.y > m_OptionsTextShape.bottom &&
		mousePos.x < m_OptionsTextShape.left + m_OptionsTextShape.width &&
		mousePos.y < m_OptionsTextShape.bottom + m_OptionsTextShape.height)
	{
		m_OptionsClicked = true;
		m_pSelectSound->Stop();

		m_pSelectSound->Play(0);
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

void UI::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	const int mouseClick = 27;
	if (m_OptionsClicked)
	{
		if (e.keysym.sym == mouseClick)
		{
			m_OptionsClicked = false;
		}
	}
}
void UI::DrawSoundMusicBars(const float verticalOffset, const float horizontalOffset) const
{
	m_pHoveredTextureRight->Draw(m_BarAdjustementMusicRight);
	m_pHoveredTextureLeft->Draw(m_BarAdjustementMusicLeft);
	m_pHoveredTextureRight->Draw(m_BarAdjustementSoundRight);
	m_pHoveredTextureLeft->Draw(m_BarAdjustementSoundLeft);

	m_pMusicAdjustmentTexture->Draw(m_pMusicAdjustmentPos);
	m_pSoundAdjustmentTexture->Draw(m_pSoundAdjustmentPos);
}
void UI::DrawFirstScreen(const float verticalOffset, const float horizontalOffset) const
{
	m_StartGameTexture->Draw(m_StartGameTextShape);
	m_OptionsTexture->Draw(m_OptionsTextShape);
	m_QuitGameTexture->Draw(m_QuitTextShape);

	m_LogoTexture->Draw(m_LogoStartScreenPos);


	if (m_StartGameHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_StartGameTexture->GetWidth() / 2 - horizontalOffset,
			m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_StartGameTexture->GetWidth() / 2 + horizontalOffset / 5,
			m_ViewPort.bottom + m_ViewPort.height / 2 - verticalOffset));
	}
	if (m_OptionsHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_OptionsTexture->GetWidth() + horizontalOffset,
			m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_OptionsTexture->GetWidth() / 2 + horizontalOffset / 6,
			m_ViewPort.bottom + m_ViewPort.height / 2 - 1.5f * m_OptionsTexture->GetHeight() - verticalOffset));
	}
	if (m_QuitGameHovered)
	{
		m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_QuitGameTexture->GetWidth() / 2 - verticalOffset / 1.5f,
			m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset));
		m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_QuitGameTexture->GetWidth() / 2 + verticalOffset / 6,
			m_ViewPort.bottom + m_ViewPort.height / 2 - 3 * m_OptionsTexture->GetHeight() - verticalOffset));
	}
}
void UI::DrawAudioScreen(const float verticalOffset, const float horizontalOffset) const
{
	if (m_OptionsClicked)
	{
		m_pAudioTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_pAudioTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 + 4 * verticalOffset));
		m_pDecorationTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_pDecorationTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 + 2.2f * m_pDecorationTexture->GetHeight()));

		m_pBackTexture->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_pBackTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 - 4 * verticalOffset));

		DrawSoundMusicBars(verticalOffset, horizontalOffset);

		if (m_BackHovered)
		{
			m_pHoveredTextureLeft->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 - m_pBackTexture->GetWidth() / 2 - horizontalOffset,
				m_ViewPort.bottom + m_ViewPort.height / 2 - 4 * verticalOffset));
			m_pHoveredTextureRight->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_pBackTexture->GetWidth() / 2,
				m_ViewPort.bottom + m_ViewPort.height / 2 - 4 * verticalOffset));
		}

		m_SoundBar->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_pMusicAdjustmentTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 - m_pSoundAdjustmentTexture->GetHeight()));
		m_SoundBar->Draw(Point2f(m_ViewPort.left + m_ViewPort.width / 2 + m_pMusicAdjustmentTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 + 2 * m_pSoundAdjustmentTexture->GetHeight()));

		utils::FillRect(m_ViewPort.left + m_ViewPort.width / 2 + m_pMusicAdjustmentTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 - m_pSoundAdjustmentTexture->GetHeight(),
			m_SoundVolume,
			m_SoundBar->GetHeight());
		utils::FillRect(m_ViewPort.left + m_ViewPort.width / 2 + m_pMusicAdjustmentTexture->GetWidth() / 2,
			m_ViewPort.bottom + m_ViewPort.height / 2 + 2 * m_pSoundAdjustmentTexture->GetHeight(),
			m_MusicVolume + 6.2f,
			m_SoundBar->GetHeight());
	}
}