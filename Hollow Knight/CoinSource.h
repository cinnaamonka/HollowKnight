#pragma once
class Texture;
class Avatar;
#include "GroundObject.h"
class CoinSource final: public GroundObject
{
public:

	CoinSource(const Point2f& position, const int index);
	CoinSource(const CoinSource& other) = delete;
	CoinSource& operator=(const CoinSource& other) = delete;
	CoinSource(CoinSource&& other) = delete;
	CoinSource& operator=(CoinSource&& other) = delete;
	~CoinSource();

	void Draw()const;
	void Update(Avatar* actor);
	void CheckIfDestroyed();
	bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const;
	
	bool IsOverlapping(const Rectf& rect) const;

	bool IsDestroyed() const
	{
		return m_IsDestroyed;
	}
private:

	void ChangeTexture();

private:

	Point2f m_Position;
	Rectf m_SourceRect;
	float m_ClipWidth;
	float m_ClipHeight;

	bool m_IsDestroyed;
	bool m_IsAtacked;

	int m_Lifes;
	int m_PassedFrames;
	const int m_MaxFramesAmount;
	const int m_MaxLifes;

	std::vector<std::vector<Point2f>> m_Vertices;
	
};

