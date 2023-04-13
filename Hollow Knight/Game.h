#pragma once

#include "Camera.h"
#include "Hud.h"

#include <Vector2f.h>
#include <BaseGame.h>

class Camera;
class Avatar;
class PowerUpManager;
class Level;

class Game : public BaseGame
{
public:

	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Events handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:

	// methods

	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void ShowTestMessage() const;
	void AddPowerUps();
	void DoCollisionTests();

private:

	// DATA MEMBERS

	Avatar *m_pAvatar;

	PowerUpManager * m_pPowerUpManager;
	
	Level *m_pLevel;

	Camera* m_Camera;
	Hud* m_Hud;
	
	bool m_EndReached;
	
};