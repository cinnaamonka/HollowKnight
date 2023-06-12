#pragma once

class Coin;
class Environment;
class SoundEffect;

#include "BaseManager.h"

class CoinManager final :public BaseManager<Coin>
{

public:
	CoinManager();
	CoinManager(const CoinManager&) = delete;
	CoinManager& operator=(const CoinManager&) = delete;
	CoinManager(CoinManager&&) = delete;
	CoinManager& operator=(CoinManager&&) = delete;

	~CoinManager();


	void Draw() const override;

	void Update(float elapsedSec, Environment* pLevel);


	void HandleCollection(const Rectf& rect);

	void SetPositions(const Rectf& rect) const;

	int GetCoinsCollectedAmount()
	{
		return m_CoinsCollectedAmount;
	}

	void setCoinsAmount(const int coins) {
		m_CoinsCollectedAmount = coins;
	}

	
private:

	int m_CoinsCollectedAmount;

	SoundEffect* m_pCoinCollectedSound;
};


