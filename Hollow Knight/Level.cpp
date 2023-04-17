#include "pch.h"
#include "Level.h"

#include <Texture.h>
#include "Platform.h"
#include <SVGParser.h>

Level::Level()
{
	m_pPlatform = new Platform{ Point2f(8088.0f,2070.0f) };
	m_pBackground = new Texture{ "Background Variation3.png" };
	m_pLevel = new Texture{ "HollowKnightLevel2.png" };
	m_pForeground = new Texture{ "HollowKnight LevelForeground.png" };
	m_Boundaries = Rectf(0, 0, m_pLevel->GetWidth(), m_pLevel->GetHeight());
	SVGParser::GetVerticesFromSvgFile("level1.svg", m_Vertices);
}
Level::~Level()
{
	delete m_pPlatform;
	delete m_pBackground;
	delete m_pLevel;
	delete m_pForeground;
}

void Level::DrawBackground() const
{
	m_pBackground->Draw();
}

void Level::DrawForeground() const
{
	m_pForeground->Draw();
}

void Level::DrawMiddleground() const
{
	m_pLevel->Draw();
	m_pPlatform->Draw();
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	m_pPlatform->HandleCollision(actorShape, actorVelocity);

	if (m_pPlatform->isCollidingCharacter() && IsOnGround(actorShape, actorVelocity))
		return;

	Point2f ray1(actorShape.left + actorShape.width / 2, actorShape.bottom);
	Point2f ray2(actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height);
	Point2f ray3(actorShape.left, actorShape.bottom + actorShape.height / 2);
	Point2f ray4(actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2);

	utils::HitInfo hitInfo;

	for (const std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWalls(ver, actorShape, hitInfo))
		{
			ResetHorizontalPosition(actorVelocity, actorShape, hitInfo);
			if (isCollidingGround(ver, actorShape, hitInfo))
				ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			break;
		}
		else if (isCollidingTop(ver, actorShape, hitInfo))
		{
			ResetTopPosition(actorVelocity, actorShape, hitInfo);

			break;
		}
		else if (isCollidingGround(ver, actorShape, hitInfo))
		{
			ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			break;
		}
	}
}

bool Level::IsOnGround(Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (m_pPlatform->isCharacterOnPlatform())
		return true;

	utils::HitInfo hitInfo{};

	Point2f ray1(actorShape.left + actorShape.width / 2, actorShape.bottom - 1.0f);
	Point2f ray2(actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height);

	return utils::Raycast(m_Vertices[3], ray2, ray1, hitInfo) || utils::Raycast(m_Vertices[2], ray2, ray1, hitInfo) || utils::Raycast(m_Vertices[1], ray2, ray1, hitInfo) || utils::Raycast(m_Vertices[0], ray2, ray1, hitInfo);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

bool Level::HasReachedEnd(const Rectf& actorShape) const
{
	return false;
}

bool Level::isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	Point2f ray1(actorShape.left, actorShape.bottom + actorShape.height / 2);
	Point2f ray2(actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2);

	return utils::Raycast(ver, ray1, ray2, hitInfo);
}
bool Level::isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo)
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo);
}

bool Level::isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo)
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom + actorShape.height / 2 };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height / 2 };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray5{ actorShape.left, actorShape.bottom + actorShape.height - borderDist };
	const Point2f ray6{ actorShape.left + actorShape.width,actorShape.bottom + actorShape.height - borderDist };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo) || utils::Raycast(ver, ray5, ray6, hitInfo);
}

void Level::ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
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

void Level::ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{

	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height - verticalOffset)
		return;

	actorShape.bottom = hitInfo.intersectPoint.y - verticalOffset;
	actorVelocity.y = 0.0f;
}

void Level::ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height + verticalOffset)
		return;

	actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height - verticalOffset;
	actorVelocity.y = 0.0f;
	actorVelocity.x = 0.0f;



}