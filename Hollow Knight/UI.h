#pragma once

class Texture;
class SoundEffect;

class UI final
{
public:
	UI(const Rectf& viewPort);
	~UI();

	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;
	UI(UI&&) = delete;
	UI& operator=(UI&&) = delete;

	void Draw() const;

	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	bool IsGameStarted() const;
	bool IsGameQuit() const;

	static const int GetMusicVolume()
	{
		return m_MusicVolume;
	}

	static const int GetSoundVolume()
	{
		return m_SoundVolume;
	}

private:
	void DrawSoundMusicBars(const float verticalOffset, const float horizontalOffset) const;
	void DrawFirstScreen(const float verticalOffset, const float horizontalOffset) const;
	void DrawAudioScreen(const float verticalOffset, const float horizontalOffset) const;

private:

	Texture* m_pBackgroundTexture;
	Texture* m_pCursorTexture;
	Texture* m_StartGameTexture;
	Texture* m_OptionsTexture;
	Texture* m_QuitGameTexture;
	Texture* m_LogoTexture;
	Texture* m_SoundBar;
	Texture* m_pHoveredTextureLeft;
	Texture* m_pHoveredTextureRight;
	Texture* m_pAudioTexture;
	Texture* m_pDecorationTexture;
	Texture* m_pMusicAdjustmentTexture;
	Texture* m_pSoundAdjustmentTexture;
	SoundEffect* m_pSelectSound;
	Texture* m_pBackTexture;


	Rectf m_ViewPort;
	Rectf m_StartGameTextShape;
	Rectf m_OptionsTextShape;
	Rectf m_QuitTextShape;
	Rectf m_BackTextShape;

	Point2f m_BarAdjustementMusicRight;
	Point2f m_BarAdjustementMusicLeft;
	Point2f m_BarAdjustementSoundRight;
	Point2f m_BarAdjustementSoundLeft;

	Point2f m_pMusicAdjustmentPos;
	Point2f m_pSoundAdjustmentPos;
	Point2f m_LogoStartScreenPos;

	Point2f m_CursorPos;

	bool m_GameIsStarted;
	bool m_StartGameHovered;
	bool m_OptionsHovered;
	bool m_QuitGameHovered;
	bool m_GameIsQuit;
	bool m_OptionsClicked;
	bool m_BackHovered;

	static int m_MusicVolume;
	static int m_SoundVolume;
};

