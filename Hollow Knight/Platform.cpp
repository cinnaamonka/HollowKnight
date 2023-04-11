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
		std::cout << m_PlatformVertices[0].
		if (isCollidingWalls(ver, actorShape, hitInfo))
		{
			std::cout << "isCollidingWall" << std::endl;
			ResetHorizontalPosition(actorVelocity, actorShape, hitInfo);
			isColliding = true;

			if (IsOnPlatform(ver, actorShape, hitInfo)) ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			return;
		}

		if (IsUnderPlatform(ver, actorShape, hitInfo) && actorVelocity.y > 0)
		{
			std::cout << "IsUnderPlatform" << std::endl;
			ResetTopPosition(actorVelocity, actorShape, hitInfo);

			isColliding = true;


			return;
		}

		if (IsOnPlatform(ver, actorShape, hitInfo) && actorVelocity.y < 0)
		{
			std::cout << "IsOnPlatform" << std::endl;
			ResetVerticalPosition(actorVelocity, actorShape, hitInfo);
			
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

	return utils::Raycast(ver, ray2, ray1, hitInfo) || utils::Raycast(ver, ray4, ray3, hitInfo);
}
bool Platform::isCollidingWalls(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)
{

	float borderDist{ 5.f };
	const Point2f ray1{ actorShape.left, actorShape.bottom + borderDist };
	const Point2f ray2{ actorShape.left + actorShape.width, actorShape.bottom + borderDist };

	const Point2f ray3{ actorShape.left , actorShape.bottom + actorShape.height - borderDist };
	const Point2f ray4{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height - borderDist };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo);
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
	std::cout << actorShape.bottom + actorShape.height << ", " << hitInfo.intersectPoint.y << std::endl;
	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height + verticalOffset) return;
	actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height - verticalOffset;
	actorVelocity.y = 0.0f;
	
}
void Platform::ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	if (actorVelocity.x >= 0)
	{

		std::cout << "Logs: collision with a right wall" << std::endl;
		actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
	}
	else {
		std::cout << "Logs: collision with a left wall" << std::endl;
		actorShape.left = hitInfo.intersectPoint.x;
	}

}


