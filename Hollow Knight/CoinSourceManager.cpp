#include "pch.h"
#include "CoinSourceManager.h"

CoinSourceManager::CoinSourceManager()
{

}
CoinSourceManager::~CoinSourceManager()
{

}
void CoinSourceManager::Update()
{
	for (CoinSource* pSource : GetItems())
	{
		pSource->Update();
	}
}
bool CoinSourceManager::IsCoinSourceDestroyed(const Rectf& avatar) const
{
	for (CoinSource* pSource : GetItems())
	{
		if (pSource->IsOverlapping(avatar) && !pSource->IsDestroyed())
		{
			pSource->CheckIfDestroyed();
			if (pSource->IsDestroyed())
			{
				return true;
			}
		}
	}
	return false;
}
