#include "pch.h"
#include "CoinManager.h"
#include "Coin.h"

CoinManager::CoinManager()
{

}
CoinManager::~CoinManager()
{
	for (const Coin* pCoin : m_pCoins)
	{
		delete pCoin;
	}
}
void CoinManager::AddItem(Coin* pCoin)
{
	m_pCoins.push_back(pCoin);
}

void CoinManager::Draw() const
{
	for (const Coin* pCoin : m_pCoins)
	{
		if (!pCoin->IsCollected())
		{
			pCoin->Draw();
		}

	}
}

size_t CoinManager::Size() const
{
	return m_pCoins.size();
}

void CoinManager::HandleCollection(const Rectf& rect)const
{
	for (Coin* pCoin : m_pCoins)
	{
		if (pCoin->IsOverlapping(rect))
		{
			pCoin->SetIsCollected(true);
			break;
		}
	}
}
void CoinManager::SetPositions(const Rectf& rect) const
{
	const int coinsPerKill = 3;
	const int coinsStartingOffset = -70;
	const int offsetStep = 50;

	int offset = coinsStartingOffset;

	for (int i = m_pCoins.size() - coinsPerKill; i < m_pCoins.size(); i++) {
		m_pCoins[i]->SetPosition(Point2f(rect.left + offset, rect.bottom));

		offset += offsetStep;
	}
}
