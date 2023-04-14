#pragma once

#include <vector>

#include <Vector2f.h>

class Texture;
class Platform;

class Level
{
public:

	Level();
	~Level();

	void DrawBackground() const;
	void DrawForeground() const;
	void DrawMiddleground() const;

	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(Rectf&  actorShape, Vector2f& actorVelocity) const;
	Rectf GetBoundaries() const;
	bool HasReachedEnd(const Rectf& actorShape) const;

private:

	void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);

	bool isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo) const;
	bool isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo) const;
	bool isCollidingWalls(const std::vector<Point2f>& ver, const Point2f& p1, const Point2f& p2, utils::HitInfo& hitInfo) const;

	void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);

private:

	std::vector<std::vector<Point2f>> m_Vertices;

	Texture* m_pLevel;
	Texture* m_pForeground;
	Texture* m_EndSignTexture;
	Texture* m_pBackground;
	Texture* m_pMiddleGround;
	//Texture* Test;

	Point2f m_FenceBottomLeftl;

	Rectf m_Boundaries ;
	Rectf m_EndSignShape;

	Platform* m_pPlatform;
};

