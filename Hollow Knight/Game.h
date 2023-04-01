#pragma once
#include "Level.h"
#include "PowerUpManager.h"
#include "Avatar.h"
#include "Vector2f.h"
#include "BaseGame.h"
#include "Camera.h"
#include "Hud.h"
#include "SoundEffect.h"
class Camera;
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

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS

	Level m_Level;
	PowerUpManager m_PowerUpManager;
	Avatar m_Avatar;
	Camera* m_Camera;
	bool m_EndReached;
	Hud* m_Hud;
	SoundEffect* m_pPowerUp;
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void ShowTestMessage( ) const;
	void AddPowerUps( );
	void DoCollisionTests( );
};