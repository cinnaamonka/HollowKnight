#include "pch.h"
#include "Hud.h"
#include "Texture.h"
Hud::Hud(const Point2f& topLeft, int totalPowerUps) :
	m_BottomLeft{ topLeft }, m_TotalPowerUps{ totalPowerUps }, m_HitPowerUps{ 0 }
{

	m_pLeftTexture = new Texture{ "HudLeft.png" };
	m_pRightTexture = new Texture{ "HudRight.png" };
	m_pPowerUpTexture = new Texture{ "HudPowerUp.png" };
}
void Hud::Draw()
{
	m_pLeftTexture->Draw(m_BottomLeft);

	for (int i = 0; i < m_TotalPowerUps; ++i)
	{
		Rectf destRect
		{
			m_BottomLeft.x + m_pLeftTexture->GetWidth() + i * m_pPowerUpTexture->GetWidth() / 2,
			m_BottomLeft.y,
			m_pPowerUpTexture->GetWidth() / 2,
			m_pPowerUpTexture->GetHeight()
		};
		Rectf sourceRect
		{
			m_pPowerUpTexture->GetWidth() / 2,
			0.0f,
			m_pPowerUpTexture->GetWidth() / 2,
			m_pPowerUpTexture->GetHeight()
		};

		m_pPowerUpTexture->Draw(destRect, sourceRect);

	}

	for (int i = 0; i < m_HitPowerUps; ++i)
	{
		Rectf destRect
		{
			m_BottomLeft.x + m_pLeftTexture->GetWidth() + i * m_pPowerUpTexture->GetWidth() / 2,
			m_BottomLeft.y,
			m_pPowerUpTexture->GetWidth() / 2,
			m_pPowerUpTexture->GetHeight()
		};
		Rectf sourceRect
		{
			0.0f,
			0.0f,
			m_pPowerUpTexture->GetWidth() / 2,
			m_pPowerUpTexture->GetHeight()
		};
		m_pPowerUpTexture->Draw(destRect, sourceRect);
	}



	Rectf destRect
	{
		m_BottomLeft.x + m_pLeftTexture->GetWidth() + 3 * m_pPowerUpTexture->GetWidth() / 2,
		m_BottomLeft.y,
		m_pRightTexture->GetWidth(),
		m_pRightTexture->GetHeight()
	};

	m_pRightTexture->Draw(destRect);
}

void Hud::PowerUpHit()
{
	m_HitPowerUps += 1;
}