#include "pch.h"
#include "Coin.h"

#include <Texture.h>

Coin::Coin() :
	m_IsCollected{ false }
{
	m_pCoinTexture = new Texture{ "Coin.png" };

	m_Shape.width = m_pCoinTexture->GetWidth();
	m_Shape.height = m_pCoinTexture->GetHeight();
}
Coin::~Coin()
{

}
void Coin::Draw() const
{
	m_pCoinTexture->Draw(m_Shape);
}

bool Coin::IsOverlapping(const Rectf& rect) const
{
	Rectf rectidsfoi = GetShape();
	bool isColliding
	{
		rect.left < GetShape().left + GetShape().width &&
		(rect.left + rect.width > GetShape().left) &&
		(rect.bottom < GetShape().bottom + GetShape().height) &&
		rect.bottom + rect.height > GetShape().bottom
	};

	return isColliding;
}