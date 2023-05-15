#pragma once

class Coin;
class Environment;
#include "BaseManager.h"

class CoinManager:public BaseManager<Coin>
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


	void HandleCollection(const Rectf& rect)const;

	void SetPositions(const Rectf& rect) const;
};


