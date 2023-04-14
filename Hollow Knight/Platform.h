#pragma once

#include <Vector2f.h>

class Texture;

class Platform
{
public:

	Platform(const Point2f& bottomLeft);
	~Platform();

	void Draw()const;
	void HandleCollision(Rectf& actorShape,Vector2f& actorVelocity);
	bool IsOnPlatform(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const;
	bool IsUnderPlatform(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const;
	bool isCollidingWalls(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo);

	
	void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	bool isOnPlatform;
	bool isCollidingPlatform;

private:
	Rectf m_Shape;
	Texture* m_pTexture;
	std::vector<std::vector<Point2f>> m_PlatformVertices;
};

