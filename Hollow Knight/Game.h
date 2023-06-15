#pragma once

#include <Vector2f.h>
#include <BaseGame.h>

class Level;
class UI;

class Game final : public BaseGame
{
public:

	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Events handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// methods

	void Initialize();
	void Cleanup();
	void ClearBackground() const;

private:
	// DATA MEMBERS

	Level* m_plevel;
	UI* m_pUI;
};