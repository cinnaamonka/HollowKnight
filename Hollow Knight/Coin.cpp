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
	Rectf coinShape = GetShape();

	const float actorRight = rect.left + 2 * rect.width / 3;
	const float actorLeft = rect.left + rect.width / 3;
	const float actorBottom = rect.bottom;
	const float actorTop = rect.bottom + rect.height;


	const float coinRight = coinShape.left + coinShape.width;
	const float coinLeft = coinShape.left;
	const float coinBottom = coinShape.bottom;
	const float coinTop = coinShape.bottom + coinShape.height;


	bool isColliding
	{
		actorLeft < coinRight &&
		actorRight > coinLeft &&
		actorBottom < coinTop &&
		actorTop > coinBottom
	};

	return isColliding;
}