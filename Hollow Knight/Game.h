#pragma once

#include <Vector2f.h>
#include <BaseGame.h>

class Camera;
class Avatar;
class EnemyManager;
class Level;
class EnemyManager;
class CoinManager;
class Spikes;

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
	void AddEnemies();
	void AddCoins();
	void CheckAvatarCollison();

private:

	// DATA MEMBERS

	Avatar *m_pAvatar;
	EnemyManager *m_pEnemyManager;
	Level *m_pLevel;
	Camera* m_Camera;
	CoinManager* m_pCoinManager;
	Spikes* m_pSpikes;

	bool m_EndReached;
	
};