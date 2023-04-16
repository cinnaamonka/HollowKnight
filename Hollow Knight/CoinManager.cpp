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

void CoinManager::HandleCollection(const Rectf& rect)
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
	m_pCoins[0]->SetPosition(Point2f(rect.left - 70.0f, rect.bottom));
	m_pCoins[1]->SetPosition(Point2f(rect.left - 20.0f, rect.bottom));
	m_pCoins[2]->SetPosition(Point2f(rect.left + 40.0f, rect.bottom));
}
