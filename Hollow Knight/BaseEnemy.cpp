#include "pch.h"

#include "BaseEnemy.h"
#include "Game.h"

#include <Texture.h>

BaseEnemy::BaseEnemy(const Point2f& position, const std::string& texture) :
	BaseMovingObject(texture),
	m_SourceRect {0,0,0,0},
	m_Shape{ 2400, 5500,0,0 }, m_NrOfFrames( 4 ),
	m_AnimTime(0), m_AnimFrame(0), m_BoundariesBorder{0,0,0,0}, m_NrFramesPerSec(1)
{
	m_SourceRect.width = GetTexture()->GetWidth() / m_NrOfFrames;
	m_SourceRect.height = GetTexture()->GetHeight();

	m_Shape.left = position.x;
	m_Shape.bottom = position.y;
	m_Shape.width = m_SourceRect.width;
	m_Shape.height = m_SourceRect.height;

	m_BoundariesBorder.left = m_Shape.left;
	m_BoundariesBorder.bottom = m_Shape.bottom;

	SetBoundaries(300.0f, m_Shape.height); // default
}

BaseEnemy::~BaseEnemy()
{

}

void BaseEnemy::SetBoundaries(float width, float height)
{
	m_BoundariesBorder.width = width;
	m_BoundariesBorder.height = height;
}

bool BaseEnemy::IsOverlapping(const Rectf& rect) const
{
    // for avatar rectf
	const float left = rect.left;
	const float right = rect.left + rect.width;
	const float bottom = rect.bottom;
	const float top = rect.bottom + rect.height;

	bool isCollidingRight
	{
		right >= m_Shape.left &&
		left <= m_Shape.left &&
		top >= m_Shape.bottom &&
		bottom <= m_Shape.bottom + m_Shape.height
	};

	if (right >= m_Shape.left)
	{
		std::cout <<"Shape Left" << m_Shape.left << std::endl;
		std::cout << "Character left" << left << std::endl;

	}
	bool isCollidingLeft
	{
		left <= m_Shape.left + m_Shape.width &&
		right >= m_Shape.left + m_Shape.width &&
		bottom <= m_Shape.bottom + m_Shape.height &&
		top >= m_Shape.bottom 
	};
	
	if (isCollidingLeft)
	{
		std::cout << "colldiding left";
	}

	if (isCollidingRight)
	{
		std::cout << "colldiding right";
	}

	return isCollidingLeft || isCollidingRight;
}

void BaseEnemy::UpdateFrame(float elapsedSec)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / m_NrOfFrames)
	{
		++m_AnimFrame %= m_NrOfFrames;

		m_AnimTime = 0.0f;
	}
}

void BaseEnemy::ChangeTexture()
{
	Rectf srcRect
	{
		0.0f,
		m_SourceRect.height,
		m_SourceRect.width,
		m_SourceRect.height
	};

	srcRect.left = m_AnimFrame * srcRect.width;
	
	m_SourceRect = srcRect;
}