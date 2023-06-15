#include "pch.h"
#include "GroundObject.h"

#include <Texture.h>

GroundObject::GroundObject(const std::string& texture)
{
	m_pTexture = new Texture(texture);
	texturefilename = texture;

	const Rectf groundObjectShape
	(
		0.0f,
		0.0f,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight()
	);

	SetShape(groundObjectShape);
}

GroundObject::~GroundObject()
{
	delete m_pTexture;
}

bool GroundObject::isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo)
{
	float borderDist = 5.f;

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo);
}

bool GroundObject::isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo)
{
	float borderDist = 5.f;

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom + actorShape.height / 2 };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height / 2 };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray5{ actorShape.left, actorShape.bottom + actorShape.height - borderDist };
	const Point2f ray6{ actorShape.left + actorShape.width,actorShape.bottom + actorShape.height - borderDist };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo) || utils::Raycast(ver, ray5, ray6, hitInfo);
}

void GroundObject::ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{

	if (hitInfo.intersectPoint.x < actorShape.left + actorShape.width / 2)
	{
		actorShape.left = hitInfo.intersectPoint.x;
	}
	else if (hitInfo.intersectPoint.x > actorShape.left + actorShape.width / 2)
	{
		actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
	}
	actorVelocity.x = 0.0f;
}

void GroundObject::ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	const float verticalOffset = 2.0f;

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height - verticalOffset) return;

	actorShape.bottom = hitInfo.intersectPoint.y - verticalOffset;

	actorVelocity.y = 0.0f;
}

void GroundObject::ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	const float verticalOffset = 2.0f;

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height + verticalOffset) return;

	actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height - verticalOffset;

	actorVelocity.y = 0.0f;
	actorVelocity.x = 0.0f;
}

void GroundObject::Draw(const Point2f& pos)const
{
	m_pTexture->Draw(pos);
}

void GroundObject::SetShape(const Rectf& rect)
{
	m_Shape = rect;

	m_Shape.width = m_pTexture->GetWidth();
	m_Shape.height = m_pTexture->GetHeight();

}
