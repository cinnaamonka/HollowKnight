#include "pch.h"
#include "CoinManager.h"
#include "Coin.h"
#include "Environment.h"

CoinManager::CoinManager()
{

}
CoinManager::~CoinManager()
{

}


void CoinManager::Draw() const
{
	for (const Coin* pCoin : GetItems())
	{
		if (!pCoin->IsCollected())
		{
			pCoin->Draw();
		}

	}
}

void CoinManager::HandleCollection(const Rectf& rect)const
{
	for (Coin* pCoin : GetItems())
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

	for (int i = GetItems().size() - coinsPerKill; i < GetItems().size(); i++) {
		GetItems()[i]->SetPosition(Point2f(rect.left + offset, rect.bottom));

		offset += offsetStep;
	}
}
void CoinManager::Update(float elapsedSec, Environment* pLevel)
{
	for (Coin* pCoin : GetItems())
	{
		Rectf coinShape = pCoin->GetShape();

		if (!pLevel->IsOnGround(coinShape,true))
		{
			pCoin->Fall(elapsedSec);
		}
	}
}

