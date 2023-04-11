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
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(Rectf&  actorShape, Vector2f& actorVelocity)const;
	Rectf GetBoundaries()const;
	bool HasReachedEnd(const Rectf& actorShape);
	bool isCollidingWalls(std::vector<Point2f>& ver, Point2f& p1, const Point2f& p2, utils::HitInfo& hitInfo);
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
	Texture* Test;
	
	
	void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);

	bool isCollidingGround(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo);
	bool isCollidingTop(std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo);
	
	void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
};

