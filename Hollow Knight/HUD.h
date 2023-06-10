#pragma once

class Texture;
class HUD
{
public:

	HUD(const Point2f& topLeft, int totalLifesAmount, CoinManager* coinManager);
	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;
	~HUD();

	void Draw();
	void PowerUpHit();

	const int GetLeftLifes() const
	{
		return int(m_LeftLifes);
	}
	void SetLeftLifesAmount(const int amount)
	{
		int(m_LeftLifes) = amount;
	}
	void SetCollectedCoinsAmount(const int coinsAmount)
	{
		m_CollectedCoins = coinsAmount;
	}

	
	void AddLife();
	bool CanAddLife();

private:
	CoinManager* m_pCoinManager;

	Point2f m_BottomLeft;
	int m_TotalLifesAmount;
	float m_LeftLifes;

	Texture* m_pHUDTexture;
	Texture* m_pLifeTexture;
	Texture* m_pEmptyLifeTexture;
	Texture* m_CoinsNumberTexture;
	Texture* m_CoinTexture;

	int m_CollectedCoins;
	int m_SavedCoins;
	int m_PreviousLifes;

};

