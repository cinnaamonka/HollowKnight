#pragma once
#include "CoinSource.h"
#include "BaseManager.h"
class Avatar;

class CoinSourceManager final :public BaseManager<CoinSource>
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



