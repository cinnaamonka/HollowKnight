#include "pch.h"
#include "Environment.h"
#include "GroundObject.h"

#include <Texture.h>
#include "Platform.h"
#include <SVGParser.h>

Environment::Environment():
	m_pDarkRect(2782, 3000, 1080, 1300)
{
	m_pPlatform = new Platform{ Point2f(8088.0f,2070.0f) };
	m_pBackground = new Texture{ "Background Variation3.png" };
	m_pGround = new GroundObject{ "HollowKnightLevel2.png" };
	m_pForeground = new GroundObject{ "HollowKnight LevelForeground.png" };
	m_pStaticForeground = new GroundObject{ "StaticForeground.png" };
	m_Boundaries = Rectf(0, 0, m_pGround->GetShape().width, m_pGround->GetShape().height);
	SVGParser::GetVerticesFromSvgFile("level1.svg", m_Vertices);
	m_EndSignShape = Rectf(0.0f, 0.0f, 0.0f, 0.0f);
}
Environment::~Environment()
{
	delete m_pPlatform;
	delete m_pBackground;
	delete m_pGround;
	delete m_pForeground;
	delete m_pStaticForeground;
}

void Environment::DrawBackground() const
{
	m_pBackground->Draw(Point2f(0.0f, 0.f));
}

void Environment::DrawForeground() const
{
	
	m_pForeground->Draw(Point2f(0.0f, 0.f));
}

void Environment::DrawMiddleground() const
{
	m_pGround->Draw(Point2f(0.0f,0.f));
	m_pPlatform->Platform::Draw(m_pPlatform->GetPosition());
}
void Environment::DrawStaticForeground(const Rectf& shape) const
{
	m_pStaticForeground->Draw(Point2f(0.0f, 0.f));
	BlackRectDisappear(shape);
	
}
void Environment::HandleCollision(Rectf& shape, Vector2f& velocity)
{
	m_pPlatform->HandleCollision(shape, velocity);

	if (m_pPlatform->isCollidingCharacter() && IsOnGround(shape,false))
		return;

	Point2f ray1(shape.left + shape.width / 2, shape.bottom);
	Point2f ray2(shape.left + shape.width / 2, shape.bottom + shape.height);
	Point2f ray3(shape.left, shape.bottom + shape.height / 2);
	Point2f ray4(shape.left + shape.width, shape.bottom + shape.height / 2);

	utils::HitInfo hitInfo;

	for (const std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWalls(ver, shape, hitInfo))
		{
			ResetHorizontalPosition(velocity, shape, hitInfo);
			if (isCollidingGround(ver, shape, hitInfo))
				ResetVerticalPosition(velocity, shape, hitInfo);

			break;
		}
		else if (isCollidingTop(ver, shape, hitInfo))
		{
			ResetTopPosition(velocity, shape, hitInfo);

			break;
		}
		else if (isCollidingGround(ver, shape, hitInfo))
		{
			ResetVerticalPosition(velocity, shape, hitInfo);

			break;
		}
	}

	
}

bool Environment::IsOnGround(Rectf& actorShape,bool isKilled) const
{
	if (m_pPlatform->isCharacterOnPlatform() && !isKilled)
		return true;

	utils::HitInfo hitInfo{};

	Point2f ray1(actorShape.left + actorShape.width / 2, actorShape.bottom - 1.0f);
	Point2f ray2(actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height);

	return utils::Raycast(m_Vertices[3], ray2, ray1, hitInfo) || utils::Raycast(m_Vertices[2], ray2, ray1, hitInfo) || utils::Raycast(m_Vertices[1], ray2, ray1, hitInfo) || utils::Raycast(m_Vertices[0], ray2, ray1, hitInfo);
}
Rectf Environment::GetBoundaries() const
{
	return m_Boundaries;
}

bool Environment::HasReachedEnd(const Rectf& actorShape) const
{
	return false;
}

bool Environment::isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	Point2f ray1(actorShape.left, actorShape.bottom + actorShape.height / 2);
	Point2f ray2(actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2);

	return utils::Raycast(ver, ray1, ray2, hitInfo);
}
bool Environment::isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo)
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };
	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo);
}

bool Environment::isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo)
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

void Environment::ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
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

void Environment::ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{

	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height - verticalOffset)
		return;

	actorShape.bottom = hitInfo.intersectPoint.y - verticalOffset;
	actorVelocity.y = 0.0f;
}

void Environment::ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo)
{
	const float verticalOffset{ 2.0f };

	if (hitInfo.intersectPoint.y - actorShape.bottom > actorShape.height + verticalOffset)
		return;

	actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height - verticalOffset;
	actorVelocity.y = 0.0f;
	actorVelocity.x = 0.0f;
}
void Environment::BlackRectDisappear(const Rectf& actorShape) const
{
	const float borderPointX = 4040.f;
    const float difference = borderPointX - actorShape.left;

	if ((actorShape.left > borderPointX))
	{
		utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	}
	else {
		if (difference > 0)
		{
			utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f - difference/100));
		}
		
	}
	utils::FillRect(m_pDarkRect);
	utils::FillRect(Rectf(m_pDarkRect.left + m_pDarkRect.width/2, m_pDarkRect.bottom + m_pDarkRect.height/2.1f, m_pDarkRect.width/1.5f, m_pDarkRect.height));
}