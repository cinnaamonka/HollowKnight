#include "pch.h"
#include "CoinSourceManager.h"

CoinSourceManager::CoinSourceManager()
{

}
CoinSourceManager::~CoinSourceManager()
{

}
void CoinSourceManager::Update(Avatar* pAvatar)
{
	for (CoinSource* pSource : GetItems())
	{
		pSource->Update(pAvatar);
	}
}
bool CoinSourceManager::IsCoinSourceDestroyed(const Rectf& avatar) const
{
	bool isDestroyed = false;

	std::vector<CoinSource*> temp = GetItems();
	for (CoinSource* pSource : temp)
	{
		if (pSource->IsOverlapping(avatar) && !pSource->IsDestroyed())
		{
			pSource->CheckIfDestroyed();
			if (pSource->IsDestroyed())
			{
				isDestroyed =  true;
			}
		}
	}
	return isDestroyed;
}
