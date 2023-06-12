#pragma once
class Texture;

class UI
{
public:
	UI(const Rectf& viewPort);
	~UI();

	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;
	UI(UI&&) = delete;
	UI& operator=(UI&&) = delete;

	void Draw();

	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);

	bool IsGameStarted() const;
	bool IsGameQuit() const;

private:

	Texture* m_pBackgroundTexture;
	Texture* m_pCursorTexture;
	Texture* m_StartGameTexture;
	Texture* m_OptionsTexture;
	Texture* m_QuitGameTexture;
	Texture* m_LogoTexture;
	Texture* m_SoundAdjustmentTexture;
	Texture* m_pHoveredTextureLeft;
	Texture* m_pHoveredTextureRight;

	Rectf m_ViewPort;

	Point2f m_CursorPos;

	bool m_GameIsStarted;
	bool m_StartGameHovered;
	bool m_OptionsHovered;
	bool m_QuitGameHovered;
	bool m_GameIsQuit;
};

