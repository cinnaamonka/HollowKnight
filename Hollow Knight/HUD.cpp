#include "pch.h"
#include "HUD.h"

#include <Texture.h>

HUD::HUD(const Point2f& topLeft, int totalLifesAmount) :
	m_BottomLeft{ topLeft }, m_TotalLifesAmount{ totalLifesAmount }, m_LeftLifes{ totalLifesAmount }
{
	m_pHUDTexture = new Texture{ "HUD.png" };
	m_pLifeTexture = new Texture{ "Lifes.png" };
	m_pEmptyLifeTexture = new Texture{ "EmptyLife.png" };
}

HUD::~HUD()
{
	delete m_pHUDTexture;
	delete m_pLifeTexture;
	delete m_pEmptyLifeTexture;
}

void HUD::Draw()
{
	m_pHUDTexture->Draw(m_BottomLeft);

	const float offset = 50.0f;

	for (int i = 0; i < m_TotalLifesAmount; ++i)
	{
		const Rectf destRect
		{
			2 * offset + m_BottomLeft.x + i * offset,
			m_BottomLeft.y + offset,
			m_pLifeTexture->GetWidth(),
			m_pLifeTexture->GetHeight()
		};

		m_pEmptyLifeTexture->Draw(destRect);
	}

	for (int i = 0; i < m_LeftLifes; ++i)
	{
		const Rectf destRect
		{
			2 * offset + m_BottomLeft.x + i * offset,
			m_BottomLeft.y + offset,
			m_pLifeTexture->GetWidth(),
			m_pLifeTexture->GetHeight()
		};

		m_pLifeTexture->Draw(destRect);
	}
}

void HUD::PowerUpHit()
{
	m_LeftLifes -= 1;
}