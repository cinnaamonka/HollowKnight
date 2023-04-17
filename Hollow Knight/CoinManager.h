#pragma once

class Coin;

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

	size_t Size() const;

	void HandleCollection(const Rectf& rect);

	void SetPositions(const Rectf& rect) const;

private:

	std::vector<Coin*> m_pCoins;
};


