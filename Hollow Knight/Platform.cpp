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

	if (IsOnPlatform(actorShape, actorVelocity))
	{
		actorVelocity.y = 0.0f;
		actorShape.bottom = m_Shape.bottom + m_Shape.height;

		std::cout << "IsOnPlatform" << std::endl;

		return;
	}

	if (IsUnderPlatform(actorShape, actorVelocity) && actorVelocity.y > 0)
	{
		const float delta = 2.f;

		actorVelocity.y = 0.0f;
		actorShape.bottom = m_Shape.bottom - actorShape.height - delta;

		std::cout << "IsUnderPlatform" << std::endl;

		return;
	}

	if (isCollidingRight(actorShape, actorVelocity))
	{
		const float delta = 2.f;

		actorVelocity.x = 0;

		actorShape.left = m_Shape.left + m_Shape.width + delta;

		std::cout << "isCollidingRight" << std::endl;

		return;
	}
	if (isCollidingLeft(actorShape, actorVelocity))
	{
		const float delta = 2.f;

		actorVelocity.x = 0;

		actorShape.left = m_Shape.left - actorShape.width - delta;

		std::cout << "isCollidingLeft" << std::endl;

		return;
	}
}

bool Platform::IsOnPlatform(const Rectf& actorShape, const Vector2f& actorVelocity)const
{

	const float delta = 2.f;

	const bool isOnPlatform
	{
		actorShape.left + actorShape.width >= m_Shape.left &&
		actorShape.left <= m_Shape.left + m_Shape.width &&
		actorShape.bottom - m_Shape.bottom - m_Shape.height <= delta &&
		actorShape.bottom - m_Shape.bottom - m_Shape.height >= -delta
	};

	return isOnPlatform;
}
bool Platform::IsUnderPlatform(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	const float delta = 2.f;

	const bool isUnderPlatform
	{
		actorShape.left + actorShape.width >= m_Shape.left &&
		actorShape.left <= m_Shape.left + m_Shape.width &&
		m_Shape.bottom - actorShape.bottom - actorShape.height >= -delta &&
		m_Shape.bottom - actorShape.bottom - actorShape.height <= delta
	};

	return isUnderPlatform;
}
bool Platform::isCollidingRight(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	const float delta = 2.f;

	const bool isCollidingRight
	{
		actorShape.bottom <= m_Shape.bottom + m_Shape.height &&
		actorShape.bottom + actorShape.height >= m_Shape.bottom &&
		m_Shape.left + m_Shape.width - actorShape.left <= delta &&
		m_Shape.left + m_Shape.width - actorShape.left >= -delta
	};

	return isCollidingRight;
}
bool Platform::isCollidingLeft(const Rectf& actorShape, const Vector2f& actorVelocity)const
{
	const float delta = 2.f;

	const bool isCollidingLeft
	{
		actorShape.bottom <= m_Shape.bottom + m_Shape.height &&
		actorShape.bottom + actorShape.height >= m_Shape.bottom &&
		m_Shape.left - actorShape.width - actorShape.left <= delta &&
		m_Shape.left - actorShape.width - actorShape.left >= -delta
	};

	return (isCollidingLeft);
}