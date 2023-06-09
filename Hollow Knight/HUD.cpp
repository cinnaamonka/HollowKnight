#include "pch.h"
#include "HUD.h"

#include <Texture.h>

HUD::HUD(const Point2f& topLeft, int totalLifesAmount) :
	m_BottomLeft{ topLeft }, m_TotalLifesAmount{ totalLifesAmount }, m_LeftLifes{ float(totalLifesAmount) }, m_CollectedCoins(0),
	m_SavedCoins(0)
{
	m_pHUDTexture = new Texture{ "HUD.png" };
	m_pLifeTexture = new Texture{ "Lifes.png" };
	m_pEmptyLifeTexture = new Texture{ "EmptyLife.png" };
	m_CoinsNumberTexture = nullptr;
	m_CoinTexture = new Texture{ "Coin.png" };

}

HUD::~HUD()
{
	delete m_pHUDTexture;
	delete m_pLifeTexture;
	delete m_pEmptyLifeTexture;
	delete m_CoinsNumberTexture;
	delete m_CoinTexture;
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

	for (int i = 0; i < int(m_LeftLifes); ++i)
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

	const Point2f coinsAmountTexturePosition
	{
		m_BottomLeft.x + 100.0f,
		m_BottomLeft.y + 20.0f
	};
	const Point2f coinTexturePosition
	{
		m_BottomLeft.x + 130.0f,
		m_BottomLeft.y + 10.0f
	};

	m_CoinsNumberTexture = new Texture(std::to_string(m_CollectedCoins), "Supernatural_Knight.ttf", 20, Color4f{ 1.0f,1.0f,1.0f,1.0f });
	m_CoinsNumberTexture->Draw(coinsAmountTexturePosition);

	m_CoinTexture->Draw(coinTexturePosition);
}

void HUD::PowerUpHit()
{
	m_LeftLifes -= 1;
}
void HUD::AddLife()
{
	const float leftLifesOffset = 0.005f;
	m_LeftLifes += leftLifesOffset;
}
bool HUD::CanAddLife()
{
	if (m_CollectedCoins - m_SavedCoins >= 6 || m_CollectedCoins == m_SavedCoins)
	{
		if (m_LeftLifes < m_TotalLifesAmount)
		{
			m_SavedCoins = m_CollectedCoins;
			return true;
		}

	}

	return false;
}
