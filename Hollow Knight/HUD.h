#pragma once

class Texture;

class Hud
{
public:

	Hud(const Point2f& topLeft, int totalPowerUps);

	~Hud();

	void Draw();
	void PowerUpHit();

private:

	Point2f m_BottomLeft;
	int m_TotalPowerUps;
	int m_HitPowerUps;

	Texture* m_pLeftTexture;
	Texture* m_pRightTexture;
	Texture* m_pPowerUpTexture;
};

