#pragma once
#include "GroundObject.h"

#include <Vector2f.h>

class Texture;

class Platform:public GroundObject
{
public:

	Platform(const Point2f& bottomLeft);
	Platform(const Platform& other) = delete;
	Platform& operator=(const Platform& other) = delete;
	Platform(Platform&& other) = delete;
	Platform& operator=(Platform&& other) = delete;
	~Platform();

	void HandleCollision(Rectf& actorShape,Vector2f& actorVelocity);
	bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) const;
	bool isCollidingCharacter() const 
	{
		return m_IsCollidingCharacter;
	}

	bool isCharacterOnPlatform() const
	{
		return m_isCharacterOnPlatform;
	}

	Point2f GetPosition() const
	{
		return m_Position;
	}

	void SetPosition(Point2f& pos)
	{
		m_Position = pos;
	}
private:
	
	bool m_isCharacterOnPlatform = false;
	bool m_IsCollidingCharacter = false;

	Point2f m_Position;
};

