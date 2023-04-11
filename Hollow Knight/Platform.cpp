#include "pch.h"
#include "Platform.h"
#include "iostream"
#include "utils.h"

Platform::Platform(const Point2f& bottomLeft) :
	isColliding { false }
{
	m_pTexture = new Texture{ "platform.png" };

	m_Shape.left = bottomLeft.x;
	m_Shape.bottom = bottomLeft.y;
	m_Shape.width = m_pTexture->GetWidth();
	m_Shape.height = m_pTexture->GetHeight();
	SVGParser::GetVerticesFromSvgFile("platform.svg", m_PlatformVertices);
}

void Platform::Draw()const
{
	m_pTexture->Draw(m_Shape);
	utils::DrawRect(m_Shape);
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{

	float borderDist{ 5.f };
	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	utils::DrawLine(ray1, ray2);
	utils::DrawLine(ray3, ray4);
	utils::HitInfo hitInfo{};

	for (std::vector<Point2f>& ver : m_PlatformVertices)
	{
	
		if (IsOnPlatform(ver, actorShape, hitInfo))
		{
			
			ResetVerticalPosition(actorVelocity, actorShape, hitInfo);
			
			isColliding = true;
	
			return;
		}

		if (IsUnderPlatform(ver, actorShape, hitInfo))
		{
			std::cout << "isunder" << std::endl;
			ResetTopPosition(actorVelocity, actorShape, hitInfo);
			isColliding = true;
			

			return;
		}

		if (isCollidingRight(ver, actorShape, hitInfo))
		{
			const float delta = 2.f;

			actorVelocity.x = 0;

			actorShape.left = m_Shape.left + m_Shape.width + delta;

		

			isColliding = true;

			return;
		}
		if (isCollidingLeft(ver, actorShape, hitInfo))
		{
			const float delta = 2.f;

			actorVelocity.x = 0;

			actorShape.left = m_Shape.left - actorShape.width - delta;

			

			isColliding = true;

			return;
		}
	
	}
	isColliding = false;
}

bool Platform::IsOnPlatform(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const
{
	float borderDist{ 5.f };
	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	return  utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo);
}
bool Platform::IsUnderPlatform(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom};
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };


	const Point2f ray5{ actorShape.left, actorShape.bottom + actorShape.height - borderDist };
	const Point2f ray6{ actorShape.left + actorShape.width,actorShape.bottom + actorShape.height - borderDist };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo) || utils::Raycast(ver, ray5, ray6, hitInfo);
}
bool Platform::isCollidingRight(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	const float delta = 2.f;

	const float offset = 5.0f;

	const bool isCollidingRight
	{
		actorShape.bottom <= m_Shape.bottom + m_Shape.height &&
		actorShape.bottom + actorShape.height >= m_Shape.bottom &&
		m_Shape.left + m_Shape.width - actorShape.left <= delta &&
		m_Shape.left + m_Shape.width - actorShape.left >= -delta
	};

	return isCollidingRight;
}

bool Platform::isCollidingLeft(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const
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
void Platform::ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{

	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height - verticalOffset) return;
	actorShape.bottom = hitInfo.intersectPoint.y - verticalOffset;
	actorVelocity.y = 0.0f;
}
void Platform::ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	std::cout << "kjikluh" << std::endl;
	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height + verticalOffset) return;
	actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height - verticalOffset;
	actorVelocity.y = 0.0f;
	actorVelocity.x = 0.0f;
}


