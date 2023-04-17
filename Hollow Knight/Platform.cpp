#include "pch.h"
#include "Platform.h"

#include <SVGParser.h>
#include <Texture.h>

Platform::Platform(const Point2f& bottomLeft) :
	GroundObject("platform.png")

{


	SVGParser::GetVerticesFromSvgFile("platform.svg", m_Vertices);

	Rectf platfromRect
	{
		bottomLeft.x - 130.0f,
		bottomLeft.y + 30.0f,
		0.0f,
		0.f
	};

	SetShape(platfromRect);

	Point2f pos = Point2f(platfromRect.left, platfromRect.bottom);

	SetPosition(pos);

}

Platform::~Platform()
{

}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	utils::HitInfo hitInfo{};

	m_isCharacterOnPlatform = false;
	m_IsCollidingCharacter = false;

	for (std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWalls(ver, actorShape, hitInfo))
		{
			ResetHorizontalPosition(actorVelocity, actorShape, hitInfo);
			m_IsCollidingCharacter = true;

			if (isCollidingGround(ver, actorShape, hitInfo))
				ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			break;
		}
		else if (isCollidingTop(ver, actorShape, hitInfo) && actorVelocity.y > 0)
		{
			ResetTopPosition(actorVelocity, actorShape, hitInfo);
			m_IsCollidingCharacter = true;

			break;
		}
		else if (isCollidingGround(ver, actorShape, hitInfo) && actorVelocity.y < 0)
		{

			ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			m_isCharacterOnPlatform = true;
			m_IsCollidingCharacter = true;

			break;
		}
	}
}
 bool Platform::isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const
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



