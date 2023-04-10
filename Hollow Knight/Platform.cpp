#include "pch.h"
#include "Platform.h"
#include "iostream"
#include "utils.h"

Platform::Platform(const Point2f& bottomLeft)
{
	m_pTexture = new Texture{ "platform.png" };

	m_Shape.left = bottomLeft.x;
	m_Shape.bottom = bottomLeft.y;
	m_Shape.width = m_pTexture->GetWidth();
	m_Shape.height = m_pTexture->GetHeight();
	
}

void Platform::Draw()const
{
	m_pTexture->Draw(m_Shape);
    utils::DrawRect(m_Shape);
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)const
{

	if (IsUnderPlatform(actorShape, actorVelocity) && actorVelocity.y > 0)
	{
		actorVelocity.y = 0.0f;
		actorShape.bottom = m_Shape.bottom - actorShape.height;
		std::cout << "IsUnderPlatform" << std::endl;
		return;
	}
	if (IsOnPlatform(actorShape, actorVelocity) )
	{
		actorVelocity.y = 0.0f;
		actorShape.bottom = m_Shape.bottom + m_Shape.height;
		std::cout << "IsOnPlatform" << std::endl;
		return;
	}
	if (isCollidingRight(actorShape, actorVelocity))
	{
		actorVelocity.y = 0.0f;
		std::cout << "isCollidingRight" << std::endl;
		actorShape.left = m_Shape.left + m_Shape.width;
		return;
	}
	if (isCollidingLeft(actorShape, actorVelocity))
	{
		actorVelocity.y = 0.0f;
		std::cout << "isCollidingLeft" << std::endl;
		actorShape.left = m_Shape.left - actorShape.width;
		return;
	}
}

bool Platform::IsOnPlatform(const Rectf& actorShape, const Vector2f& actorVelocity)const
{

	bool isOnPlatform
	{
		m_Shape.bottom + m_Shape.height <= actorShape.bottom &&
		m_Shape.left <= actorShape.left + actorShape.width &&
		m_Shape.left + m_Shape.width >= actorShape.left
	};

	return (actorVelocity.y <= 0.0f && isOnPlatform);
}
bool Platform::IsUnderPlatform(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	
	bool isUnderPlatform
	{
		m_Shape.bottom >= actorShape.bottom + actorShape.height &&
		m_Shape.left <= actorShape.left	+ actorShape.width &&
        m_Shape.left + m_Shape.width >= actorShape.left
	};

	return (actorVelocity.y >= 0.0f && isUnderPlatform);
}
bool Platform::isCollidingRight(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	
	bool isCollidingRight
	{
		m_Shape.left + m_Shape.width >= actorShape.left &&
		m_Shape.bottom + m_Shape.height <= actorShape.bottom &&
		m_Shape.bottom  >= actorShape.bottom +  actorShape.height
	};

	return (isCollidingRight);
}
bool Platform::isCollidingLeft(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	//rect1.left <= rect2.right && rect1.top <= rect2.bottom && rect1.bottom >= rect2.top

	bool isCollidingLeft
	{
		actorShape.left  <= m_Shape.left + m_Shape.width &&
		actorShape.bottom + actorShape.height <= m_Shape.bottom &&
		actorShape.bottom >= m_Shape.bottom + m_Shape.height
	};

	return (isCollidingLeft);
}