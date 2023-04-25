#pragma once

class Coin;
class Environment;

class CoinManager final
{

public:
	CoinManager();
	CoinManager(const CoinManager&) = delete;
	CoinManager& operator=(const CoinManager&) = delete;
	CoinManager(CoinManager&&) = delete;
	CoinManager& operator=(CoinManager&&) = delete;

	~CoinManager();

	
	void AddItem(Coin* pCoin);

	void Draw() const;
	void Update(float elapsedSec, Environment* pLevel);

	size_t Size() const;

	void HandleCollection(const Rectf& rect)const;

	void SetPositions(const Rectf& rect) const;

private:

	std::vector<Coin*> m_pCoins;
};


