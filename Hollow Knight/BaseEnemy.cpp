#include "pch.h"

#include "BaseEnemy.h"

#include <Texture.h>

BaseEnemy::BaseEnemy(const Point2f& position, const std::string& texture, int framesNumber) :
	BaseMovingObject(texture, framesNumber),
	m_BoundariesBorder{ 0,0,0,0 }, m_CanSeeAvatar{ false }
{
	SetFramesNumber(framesNumber);

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
	bool isColliding
	{
		rect.left < GetShape().left + GetShape().width &&
		(rect.left + rect.width > GetShape().left) &&
		(rect.bottom < GetShape().bottom + GetShape().height) &&
		rect.bottom + rect.height > GetShape().bottom
	};

	return isColliding;
}

void BaseEnemy::ChangeTexture(int amountOfFramesIfKilled, int amountOfFramesMoving, int amountOFFramesAtacking)
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
		SetFramesNumber(amountOfFramesIfKilled);
		srcRect.left = (amountOfFramesMoving + amountOFFramesAtacking) * srcRect.width;
		SetSourceRect(srcRect);
	}
	else
	{
		SetFramesNumber(amountOfFramesMoving);
		srcRect.left = amountOFFramesAtacking * srcRect.width + GetAnimationFrame() * srcRect.width;
		SetSourceRect(srcRect);
	}


}
bool BaseEnemy::IsOnCloseDistance(const Rectf& rect) const
{
	float distance = float(sqrt(pow(rect.left - GetShape().left, 2) + pow(rect.bottom - GetShape().bottom, 2)));

	return distance <= 40.0f;
}
bool BaseEnemy::CanSeeAvatar(const Rectf& avatarRectf)const
{
	float distance = float(sqrt(pow(avatarRectf.left - GetShape().left, 2) + pow(avatarRectf.bottom - GetShape().bottom, 2)));

	const float maxDistanceWithAvatar = 300.0f;

	if (distance < maxDistanceWithAvatar) return true;

	return false;
}
void BaseEnemy::Draw() const
{

	if (m_Velocity.x < 0)
	{
		glPushMatrix();

		glTranslatef(GetShape().left, GetShape().bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-GetShape().width, 0, 0);

		GetTexture()->Draw(Point2f(0, 0), GetSourceRect());

		glPopMatrix();
	}
	else
	{
		GetTexture()->Draw(GetShape(), GetSourceRect());
	}
	
}
