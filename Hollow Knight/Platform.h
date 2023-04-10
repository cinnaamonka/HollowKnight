#pragma once
#include "pch.h"
#include "Texture.h"
#include "Vector2f.h"
class Texture;
class Platform
{
private:
	Rectf m_Shape;
	Texture* m_pTexture;
public:
	Platform(const Point2f& bottomLeft);
	void Draw()const;
	void HandleCollision(Rectf& actorShape,Vector2f& actorVelocity)const;
	bool IsOnPlatform(const Rectf& actorShape,const Vector2f& actorVelocity)const;
	bool IsUnderPlatform(const Rectf& actorShape, const Vector2f& actorVelocity)const;
	bool isCollidingRight(const Rectf& actorShape, const Vector2f& actorVelocity)const;
	bool isCollidingLeft(const Rectf& actorShape, const Vector2f& actorVelocity)const;
};

