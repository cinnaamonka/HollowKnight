#include "pch.h"
#include "HUD.h"

#include <Texture.h>

HUD::HUD(const Point2f& topLeft, int totalLifesAmount) :
	m_BottomLeft{ topLeft }, m_TotalLifesAmount{ totalLifesAmount }, m_LeftLifes{ totalLifesAmount }, m_CollectedCoins(0)
{
	m_pHUDTexture = new Texture{ "HUD.png" };
	m_pLifeTexture = new Texture{ "Lifes.png" };
	m_pEmptyLifeTexture = new Texture{ "EmptyLife.png" };
	m_CoinsNumberTexture = nullptr;

}

HUD::~HUD()
{
	delete m_pHUDTexture;
	delete m_pLifeTexture;
	delete m_pEmptyLifeTexture;
	delete m_CoinsNumberTexture;
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
	if (m_CoinsNumberTexture)
	{
		delete m_CoinsNumberTexture;
	}
	
	m_CoinsNumberTexture = new Texture(std::to_string(m_CollectedCoins), "DIN-Light.otf", 24, Color4f{ 1.0f,1.0f,1.0f,1.0f });
	m_CoinsNumberTexture->Draw(Point2f(m_BottomLeft.x + 100.0f, m_BottomLeft.y + 10.0f));
	

}

void HUD::PowerUpHit()
{
	m_LeftLifes -= 1;
}
