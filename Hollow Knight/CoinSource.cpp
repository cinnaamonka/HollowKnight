#include "pch.h"
#include "CoinSource.h"

#include <Texture.h>

CoinSource::CoinSource(const Point2f& position) :
	m_Position{ position }, m_IsDestroyed{ false }, m_Lifes{ 0 }, m_MaxLifes{ 5 }, m_SourceRect{ 0,0,0,0 }, m_IsAtacked{false},
	m_PassedFrames{0},m_MaxFramesAmount(70)
{
	m_pTexture = new Texture{ "stone.png" };
	m_ClipWidth = m_pTexture->GetWidth()/2;
	m_ClipHeight = m_pTexture->GetHeight();
}
CoinSource::~CoinSource()
{
	delete m_pTexture;
}
void CoinSource::Draw()const
{
	utils::SetColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	utils::DrawRect(Rectf(m_Position.x, m_Position.y, m_ClipWidth, m_ClipHeight));
	
	m_pTexture->Draw(Rectf(m_Position.x, m_Position.y, m_ClipWidth, m_ClipHeight), m_SourceRect);
}
void CoinSource::Update()
{
	ChangeTexture();
}
void CoinSource::CheckIfDestroyed()
{
	if (m_PassedFrames < m_MaxFramesAmount)
	{
		m_PassedFrames++;
		if (!m_IsAtacked)
		{
			m_Lifes++;
			m_IsAtacked = true;
			if (m_Lifes > m_MaxLifes)
			{
				m_IsDestroyed = true;
			}
			Shake();
		}
	}
	else
	{
		m_PassedFrames = 0;
		m_IsAtacked = false;
	}
}
void CoinSource::Shake()
{
	const float shakingOffset = 10.0f;

	m_Position.x += shakingOffset;

	Sleep(100);
	m_Position.x -= shakingOffset;
}
void CoinSource::ChangeTexture()
{
	if (m_IsDestroyed)
	{
		m_SourceRect = Rectf(m_ClipWidth, m_ClipHeight, m_ClipWidth, m_ClipHeight);
	}
	else
	{
		m_SourceRect = Rectf(0.0f, m_ClipHeight, m_ClipWidth, m_ClipHeight);
	}
}
bool CoinSource::IsOverlapping(const Rectf& rect) const
{
	const Rectf coinSourceRect
	{
		m_Position.x,
		m_Position.y,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight()
	};

	bool isColliding
	{
		rect.left < coinSourceRect.left + coinSourceRect.width &&
		rect.left + rect.width > coinSourceRect.left &&
		rect.bottom < coinSourceRect.bottom + coinSourceRect.height &&
		rect.bottom + rect.height > coinSourceRect.bottom
	};

	return isColliding;
}