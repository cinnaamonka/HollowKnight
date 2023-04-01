#pragma once
class Texture;
class Hud
{
private:
	Point2f m_BottomLeft;
	int m_TotalPowerUps;
	int m_HitPowerUps;
	Texture* m_pLeftTexture;
	Texture* m_pRightTexture;
	Texture* m_pPowerUpTexture;
	
public:
	Hud(const Point2f& topLeft, int totalPowerUps);
	void Draw();
	void PowerUpHit();
};

