#pragma once

#include <BaseGame.h>

class Camera;
class Avatar;
class EnemyManager;
class Environment;
class CoinManager;
class Spikes;
class EnemyDragonfly;
class DoorManager;
class CoinSource;
class CoinSourceManager;
class HUD;
class SoundStream;
class SoundEffect;
class UI;
class Texture;

class Level final
{

public:

	explicit Level(const Rectf& viewPort);
	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(Level&& other) = delete;
	~Level();

	void Update(float elapsedSec);
	void Draw() const;

	// Events handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void AddEnemies();
	void AddCoins();
	void AddDoors();
	void AddCoinSources();
	void CheckAvatarCollison();
	void PlaySound() const;

private:

	Avatar* m_pAvatar;
	EnemyManager* m_pEnemyManager;
	Environment* m_pEnvironment;
	Camera* m_Camera;
	CoinManager* m_pCoinManager;
	DoorManager* m_pDoorManager;
	Spikes* m_pSpikes;
	CoinSourceManager* m_pCoinSourceManager;
	HUD* m_pHUD;
	SoundStream* m_pBackgroundSound;

	Texture* m_EndText;

	bool m_EndReached;

	Rectf m_ViewPort;
	Point2f m_EndSignShape;
	Color4f m_FadingScreenColor;

	float m_ZoomLevel;

	int m_MusicVolume;
};


