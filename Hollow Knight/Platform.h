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

	void Draw() const;
	void HandleCollision(Rectf& actorShape,Vector2f& actorVelocity);
	
	bool isCollidingCharacter() const 
	{
		return m_IsCollidingCharacter;
	}

	bool isCharacterOnPlatform() const
	{
		return m_isCharacterOnPlatform;
	}
	virtual bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) override;
private:
	

	Rectf m_Shape;
	Texture* m_pTexture;

	std::vector<std::vector<Point2f>> m_PlatformVertices;

	bool m_isCharacterOnPlatform = false;
	bool m_IsCollidingCharacter = false;
};

