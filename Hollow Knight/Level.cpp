#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "utils.h"
#include "iostream"

//isColliding Level::m_IsColliding = isColliding::none;

Level::Level()
{
	m_pPlatform = new Platform{ Point2f(8076.0f,2070.0f) };
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
	

	Point2f ray1(actorShape.left + actorShape.width / 2, actorShape.bottom);
	Point2f ray2(actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height);
	Point2f ray3(actorShape.left, actorShape.bottom + actorShape.height / 2);
	Point2f ray4(actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2);

	utils::HitInfo hitInfo{};

	for (std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWalls(ver, ray3, ray4, hitInfo))
		{
			
			ResetHorizontalPosition(actorVelocity, actorShape, hitInfo);

			if (isCollidingGround(ver, actorShape, hitInfo)) ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			return;
		}

		if (isCollidingTop(ver, actorShape, hitInfo))
		{

			ResetTopPosition(actorVelocity, actorShape, hitInfo);

			return;
		}

		if (isCollidingGround(ver, actorShape, hitInfo))
		{
			ResetVerticalPosition(actorVelocity, actorShape, hitInfo);

			return;
		}


	}
}


bool Level::IsOnGround(Rectf& actorShape, Vector2f& actorVelocity)const
{
    //std::cout << m_pPlatform->isColliding << std::endl;
	if (m_pPlatform->isOnPlatform)
	{
		return true;
	}
	
	utils::HitInfo hitInfo{};

	Point2f ray1(actorShape.left + actorShape.width / 2, actorShape.bottom - 1.0f);
	Point2f ray2(actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height);

	return utils::Raycast(m_Vertices[3], ray2, ray1, hitInfo);
}

Rectf Level::GetBoundaries()const
{
	return m_Boundaries;
}


bool Level::HasReachedEnd(const Rectf& actorShape)
{

	return false;
}

bool Level::isCollidingWalls(std::vector<Point2f>& ver, Point2f& p1, const Point2f& p2, utils::HitInfo& hitInfo)
{
    std::cout << "Level walls" << std::endl;
	return utils::Raycast(ver, p1, p2, hitInfo);
}

void Level::ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
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

bool Level::isCollidingGround(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };
	utils::DrawLine(ray1, ray2);
	utils::DrawLine(ray3, ray4);
	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo);

}

void Level::ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{

	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height - verticalOffset) return;
	actorShape.bottom = hitInfo.intersectPoint.y - verticalOffset;
	actorVelocity.y = 0.0f;
}
bool Level::isCollidingTop(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)
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
void Level::ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height + verticalOffset) return;
	actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height - verticalOffset;
	actorVelocity.y = 0.0f;
	actorVelocity.x = 0.0f;
}



