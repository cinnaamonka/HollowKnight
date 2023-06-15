#pragma once

#include <vector>
#include <Vector2f.h>

class Texture;
class Platform;
class GroundObject;

class Environment final
{
public:

	Environment();
	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) = delete;
	Environment& operator=(Environment&& other) = delete;
	~Environment();

	void DrawBackground() const;
	void DrawForeground() const;
	void DrawMiddleground() const;
	void DrawStaticForeground(const Rectf& shape) const;


	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);

	bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) const;
	bool IsOnGround(Rectf& actorShape, bool isKilled) const;
	bool HasReachedEnd(const Rectf& actorShape) const;

	Rectf GetBoundaries() const;

	bool isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo) const;
	bool isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo) const;


	void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo) const;
	void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo) const;
	void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo) const;

	void BlackRectDisappear(const Rectf& actorShape) const;

private:

	void ChangeBoldCapacity(const Rectf shapeActor);

private:

	std::vector<std::vector<Point2f>> m_Vertices;

	Texture* m_EndSignTexture;
	Texture* m_pBackground;

	Rectf m_Boundaries;
	Rectf m_EndSignShape;
	Rectf m_pDarkRect;

	Platform* m_pPlatform;

	GroundObject* m_pGround;
	GroundObject* m_pForeground;
	GroundObject* m_pStaticForeground;
	GroundObject* m_pBaseBold;
	GroundObject* m_pBold;

	float m_BoldOpacity;

};

