#pragma once

class Texture;

class HUD
{
public:

	HUD(const Point2f& topLeft, int totalLifesAmount);
	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;
	~HUD();

	void Draw();
	void PowerUpHit();

	const int GetLeftLifes()
	{
		return m_LeftLifes;
	}
	void SetLeftLifesAmount(const int amount)
	{
		m_LeftLifes = amount;
	}
	void SetCollectedCoinsAmount(const int coinsAmount)
	{
		m_CollectedCoins = coinsAmount;
	}

private:

	Point2f m_BottomLeft;
	int m_TotalLifesAmount;
	int m_LeftLifes;

	Texture* m_pHUDTexture;
	Texture* m_pLifeTexture;
	Texture* m_pEmptyLifeTexture;
	Texture* m_CoinsNumberTexture;

	int m_CollectedCoins;
};

