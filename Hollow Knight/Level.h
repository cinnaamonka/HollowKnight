#pragma once

#include <vector>
#include <Vector2f.h>

#include "GroundObject.h"

class Texture;
class Platform;

class Level:public GroundObject
{
public:

	Level();
	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(Level&& other) = delete;
	~Level();

	void DrawBackground() const;
	void DrawForeground() const;
	void DrawMiddleground() const;

	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(Rectf&  actorShape, Vector2f& actorVelocity) const;
	Rectf GetBoundaries() const;
	bool HasReachedEnd(const Rectf& actorShape) const;

private:

	virtual bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) override;

	std::vector<std::vector<Point2f>> m_Vertices;

	Texture* m_pLevel;
	Texture* m_pForeground;
	Texture* m_EndSignTexture;
	Texture* m_pBackground;

	Rectf m_Boundaries ;
	Rectf m_EndSignShape;

	Platform* m_pPlatform;
};

