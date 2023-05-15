#pragma once
#include <vector>

#include "CoinSource.h"
#include "BaseManager.h"
class Environment;

class CoinSourceManager:public BaseManager<CoinSource>
{
public:
	CoinSourceManager();
	CoinSourceManager(const CoinSourceManager&) = delete;
	CoinSourceManager& operator=(const CoinSourceManager&) = delete;
	CoinSourceManager(CoinSourceManager&&) = delete;
	CoinSourceManager& operator=(CoinSourceManager&&) = delete;
	~CoinSourceManager();


	virtual void Update() override;
	bool IsCoinSourceDestroyed(const Rectf& avatar) const;

};



