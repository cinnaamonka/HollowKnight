#include "pch.h"

#include "BaseEnemy.h"

#include <Texture.h>

BaseEnemy::BaseEnemy(const Point2f& position, const std::string& texture) :
	BaseMovingObject(texture),
	m_BoundariesBorder{ 0,0,0,0 }
{
	SetFramesNumber(5);

	Rectf sourceRect{ 0,0,0,0 };

	sourceRect.width = GetTexture()->GetWidth() / GetFramesNumber();
	sourceRect.height = GetTexture()->GetHeight();

	SetSourceRect(sourceRect);

	Rectf shape{ 0,0,0,0 };

	shape.left = position.x;
	shape.bottom = position.y;
	shape.width = sourceRect.width;
	shape.height = sourceRect.height;

	m_BoundariesBorder.left = shape.left;
	m_BoundariesBorder.bottom = shape.bottom;

	SetBoundaries(300.0f, shape.height); // default
	SetShape(shape);
}
BaseEnemy::BaseEnemy()
{

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

	bool isColliding
	{
		rect.left < GetShape().left + GetShape().width &&
		(rect.left + rect.width > GetShape().left) &&
		(rect.bottom < GetShape().bottom + GetShape().height) &&
		rect.bottom + rect.height > GetShape().bottom
	};
	
	return isColliding;
}

void BaseEnemy::ChangeTexture()
{
	Rectf srcRect
	{
		0.0f,
		GetSourceRect().height,
		GetSourceRect().width,
		GetSourceRect().height
	};
	
	if (IsKilled())
	{
		SetFramesNumber(1);
		srcRect.left = 4 * srcRect.width;
		SetSourceRect(srcRect);
	}
	else
	{
		SetFramesNumber(4);
		srcRect.left = GetAnimationFrame() * srcRect.width;
		SetSourceRect(srcRect);
	}

	
}
bool BaseEnemy::IsOnCloseDistance(const Rectf& rect) const
{
	float distance = float(sqrt(pow(rect.left - GetShape().left, 2) + pow(rect.bottom - GetShape().bottom, 2)));

	return distance <= 40.0f;
}