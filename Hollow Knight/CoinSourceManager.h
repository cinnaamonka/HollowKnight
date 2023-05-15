#pragma once
#include <vector>

#include "CoinSource.h"
#include "BaseManager.h"
class Environment;
class Avatar;
class CoinSourceManager:public BaseManager<CoinSource>
{
public:
	CoinSourceManager();
	CoinSourceManager(const CoinSourceManager&) = delete;
	CoinSourceManager& operator=(const CoinSourceManager&) = delete;
	CoinSourceManager(CoinSourceManager&&) = delete;
	CoinSourceManager& operator=(CoinSourceManager&&) = delete;
	~CoinSourceManager();


	void Update(Avatar* pAvatar);
	bool IsCoinSourceDestroyed(const Rectf& avatar) const;

};



