#pragma once
class GroundObject
{
public:
	GroundObject();

	virtual ~GroundObject();

	static bool isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo);
	static bool isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo);
	virtual bool isCollidingWalls(const std::vector<Point2f>& ver,Rectf& actorShape, utils::HitInfo& hitInfo) = 0;

	static void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	static void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	static void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
};

