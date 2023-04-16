#pragma once
class GroundObject
{
public:
	GroundObject();

	virtual ~GroundObject();

	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) = 0;
	virtual bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) = 0;

protected:

	std::vector<std::vector<Point2f>> m_Vertices;

	static bool isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo);
	static bool isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo);
	

	static void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	static void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	static void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
};

