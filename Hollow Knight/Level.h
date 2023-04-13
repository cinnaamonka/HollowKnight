#pragma once
#include <vector>
#include "Vector2f.h"
#include "SVGParser.h"
#include "Platform.h"
#include "utils.h"
//enum isColliding
//{
//	none,
//	left,
//	right
//};
class SVGParser;

class Texture;
class Level
{
public:
	Level();
	~Level();
	void DrawBackground()const;
	void DrawForeground()const;
	void DrawMiddleground()const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(Rectf&  actorShape, Vector2f& actorVelocity)const;
	Rectf GetBoundaries()const;
	bool HasReachedEnd(const Rectf& actorShape);

	bool isCollidingWalls(const std::vector<Point2f>& ver, const Point2f& p1, const Point2f& p2, utils::HitInfo& hitInfo) const;
	/*static isColliding m_IsColliding;*/
private:
	std::vector<std::vector<Point2f>> m_Vertices;

	Texture* m_pLevel;
	Texture* m_pForeground;
	Point2f m_FenceBottomLeftl;
	Rectf m_Boundaries ;
	Platform* m_pPlatform;
	Texture* m_EndSignTexture;
	Rectf m_EndSignShape;
	Texture* m_pBackground;
	Texture* m_pMiddleGround;
	Texture* Test;
	
	
	void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);

	bool isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo) const;
	bool isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo) const;
	
	void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
};

