#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "utils.h"
#include "iostream"
#include "Game.h"

//isColliding Level::m_IsColliding = isColliding::none;

Level::Level()
{
	m_pPlatform = new Platform{ Point2f(8088.0f,2070.0f) };
	m_pBackground = new Texture{ "Background Variation3.png" };
	m_pLevel = new Texture{ "HollowKnightLevel2.png" };
	m_pForeground = new Texture{ "HollowKnight LevelForeground.png" };
	m_FenceBottomLeftl = Point2f(200, 190);
	m_Boundaries = Rectf(0, 0, m_pLevel->GetWidth(), m_pLevel->GetHeight());
	SVGParser::GetVerticesFromSvgFile("level1.svg", m_Vertices);

	m_EndSignTexture = new Texture{ "EndSign.png" };
	m_EndSignShape.left = 730.0f;
	m_EndSignShape.bottom = 224.0f;
	m_EndSignShape.width = m_EndSignTexture->GetWidth();
	m_EndSignShape.height = m_EndSignTexture->GetHeight();
	Test = new Texture{ "Level1.png" };
	//  Level::m_IsColliding = isColliding::none;
}
Level::~Level()
{
	delete m_pPlatform;
	delete m_pBackground;
	delete m_pLevel;
	delete m_pForeground;
	delete m_EndSignTexture;
}

void Level::DrawBackground()const
{

	m_pBackground->Draw();
	m_pLevel->Draw();

}
void Level::DrawForeground()const
{

	m_pForeground->Draw();
	m_EndSignTexture->Draw(m_EndSignShape);
	Test->Draw();
	m_pPlatform->Draw();

}
void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	m_pPlatform->HandleCollision(actorShape, actorVelocity);

	if (m_pPlatform->isCollidingPlatform && IsOnGround(actorShape, actorVelocity)) return;


	const Rectf actorShapeNextPos{
		actorShape.left + actorVelocity.x * Game::elapsedSec,
		actorShape.bottom + actorVelocity.y * Game::elapsedSec,
		actorShape.width,
		actorShape.height,
	};

	Point2f begHorizontalLeftRay(actorShapeNextPos.left + actorShapeNextPos.width / 4, actorShapeNextPos.bottom);
	Point2f endHorizontalLeftRay(actorShapeNextPos.left + actorShapeNextPos.width / 4, actorShapeNextPos.bottom + actorShapeNextPos.height);

	Point2f begHorizontalRightRay(actorShapeNextPos.left + 3 * actorShapeNextPos.width / 4, actorShapeNextPos.bottom);
	Point2f endHorizontalRightRay(actorShapeNextPos.left + 3 * actorShapeNextPos.width / 4, actorShapeNextPos.bottom + actorShapeNextPos.height);


	Point2f begVerticalBottomRay(actorShapeNextPos.left + actorShapeNextPos.width / 4, actorShapeNextPos.bottom);
	Point2f endVerticalBottomRay(actorShapeNextPos.left + 3 * actorShapeNextPos.width / 4, actorShapeNextPos.bottom);

	Point2f begVerticalTopRay(actorShapeNextPos.left + actorShapeNextPos.width / 4, actorShapeNextPos.bottom + actorShapeNextPos.height);
	Point2f endVerticalTopRay(actorShapeNextPos.left + 3 * actorShapeNextPos.width / 4, actorShapeNextPos.bottom + actorShapeNextPos.height);

	utils::HitInfo hitInfo{};

	for (std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWall(ver, begVerticalBottomRay, endVerticalBottomRay, begVerticalTopRay, endVerticalTopRay, hitInfo))
		{
			actorShape.left -= actorVelocity.x * Game::elapsedSec;
			actorVelocity.x = 0;
		}



		if (isCollidingRoofing(ver, begHorizontalLeftRay, endHorizontalLeftRay, begHorizontalRightRay, endHorizontalRightRay, hitInfo, actorVelocity.y))
		{
			actorShape.bottom -= actorVelocity.y * Game::elapsedSec;

			actorVelocity.x = 0;
			actorVelocity.y = 0;
		}

	}
}


bool Level::IsOnGround(Rectf& actorShape, Vector2f& actorVelocity)const
{

	if (m_pPlatform->isOnPlatform) 	return true;

	utils::HitInfo hitInfo{};

	const float offsetY = 2;

	const Rectf actorShapeNextPos{
		actorShape.left + actorVelocity.x * Game::elapsedSec,
		actorShape.bottom - actorVelocity.y * Game::elapsedSec,
		actorShape.width,
		actorShape.height,
	};

	Point2f begHorizontalLeftRay(actorShapeNextPos.left + actorShapeNextPos.width / 4, actorShapeNextPos.bottom - offsetY);
	Point2f endHorizontalLeftRay(actorShapeNextPos.left + actorShapeNextPos.width / 4, actorShapeNextPos.bottom + actorShapeNextPos.height);

	Point2f begHorizontalRightRay(actorShapeNextPos.left + 3 * actorShapeNextPos.width / 4, actorShapeNextPos.bottom - offsetY);
	Point2f endHorizontalRightRay(actorShapeNextPos.left + 3 * actorShapeNextPos.width / 4, actorShapeNextPos.bottom + actorShapeNextPos.height);


	bool isOnGround = false;

	for (std::vector<Point2f> verticle : m_Vertices) {
		if (utils::Raycast(verticle, begHorizontalLeftRay, endHorizontalLeftRay, hitInfo) ||
			utils::Raycast(verticle, begHorizontalRightRay, endHorizontalRightRay, hitInfo)) {
			isOnGround = true;

			break;
		}
	}

	return isOnGround;
}

Rectf Level::GetBoundaries()const
{
	return m_Boundaries;
}


bool Level::HasReachedEnd(const Rectf& actorShape)
{
	return false;
}

bool Level::isCollidingWall(std::vector<Point2f>& ver, Point2f& p1, const Point2f& p2, const Point2f& p3, const Point2f& p4, utils::HitInfo& hitInfo)
{
	const float offset = 6.f;

	return utils::Raycast(ver, Point2f(p1.x - offset, p1.y + offset), Point2f(p2.x + offset, p2.y + offset), hitInfo)
		|| utils::Raycast(ver, Point2f(p3.x - offset, p3.y + offset), Point2f(p4.x + offset, p4.y + offset), hitInfo);
}

bool Level::isCollidingRoofing(std::vector<Point2f>& ver, Point2f& p1, const Point2f& p2, const Point2f& p3, const Point2f& p4, utils::HitInfo& hitInfo, float speed)
{
	return utils::Raycast(ver, p1, p2, hitInfo)
		|| utils::Raycast(ver, p3, p4, hitInfo);
}





