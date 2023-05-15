#include "pch.h"
#include "CoinSource.h"
#include "Avatar.h"
#include <Texture.h>
#include <SVGParser.h>

CoinSource::CoinSource(const Point2f& position) :
	GroundObject{ "stone.png" },
	m_Position{ position }, m_IsDestroyed{ false }, m_Lifes{ 0 }, m_MaxLifes{ 5 }, m_SourceRect{ 0,0,0,0 }, m_IsAtacked{ false },
	m_PassedFrames{ 0 }, m_MaxFramesAmount(70)
{
	SVGParser::GetVerticesFromSvgFile("coinSource.svg", m_Vertices);

	m_ClipWidth = GetTexture()->GetWidth() / 2;
	m_ClipHeight = GetTexture()->GetHeight();
}
CoinSource::~CoinSource()
{
}
void CoinSource::Draw()const
{
	GetTexture()->Draw(Rectf(m_Position.x, m_Position.y, m_ClipWidth, m_ClipHeight), m_SourceRect);
}
void CoinSource::Update(Avatar* actor)
{
	ChangeTexture();

	Rectf actorShape = actor->GetShape();
	Vector2f vector = actor->GetVelocity();
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	utils::HitInfo hitInfo{};

	for (std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWalls(ver, actorShape, hitInfo))
		{
			ResetHorizontalPosition(vector, actorShape, hitInfo);
			break;
		}
		
	}
	actor->SetShape(actorShape);
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
			//Shake();
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
		m_ClipWidth,
		m_ClipHeight
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
bool CoinSource::isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left, actorShape.bottom + borderDist };
	const Point2f ray2{ actorShape.left + actorShape.width, actorShape.bottom + borderDist };

	const Point2f ray3{ actorShape.left , actorShape.bottom + actorShape.height - borderDist };
	const Point2f ray4{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height - borderDist };

	const Point2f ray5{ actorShape.left , actorShape.bottom + actorShape.height / 2 };
	const Point2f ray6{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2 };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo) || utils::Raycast(ver, ray5, ray6, hitInfo);
}