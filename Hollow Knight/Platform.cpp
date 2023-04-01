#include "pch.h"
#include "Platform.h"
#include "iostream"

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
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)const
{
	if (IsOnGround(actorShape, actorVelocity) && actorVelocity.y < 0)
	{
		actorVelocity.y = 0.0f;
	}
}

bool Platform::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	bool isNotCollide
	{
		actorShape.left + actorShape.width < m_Shape.left ||
		actorShape.left > m_Shape.left + m_Shape.width ||
		actorShape.bottom + actorShape.height < m_Shape.bottom ||
		actorShape.bottom > m_Shape.bottom + m_Shape.height
	};

	return (actorVelocity.y < 0 && !isNotCollide);
}