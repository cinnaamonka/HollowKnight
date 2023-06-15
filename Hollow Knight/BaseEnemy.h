#pragma once

#include "BaseMovingObject.h"

class BaseEnemy : public BaseMovingObject
{
public:

	explicit BaseEnemy(const Point2f& position, const std::string &texture, int framesNumber);

	virtual ~BaseEnemy();

	BaseEnemy(const BaseEnemy& other) = delete;
	BaseEnemy& operator=(const BaseEnemy& other) = delete;
	BaseEnemy(BaseEnemy&& other) = delete;
	BaseEnemy& operator=(BaseEnemy&& other) = delete;

	virtual void Update(float elapsedSec) = 0;

	bool IsOverlapping(const Rectf& rect) const;

	bool IsOnCloseDistance(const Rectf& rect) const;

	bool CanSeeAvatar(const Rectf& avatarRectf)const;

	bool GetCanSeeAvatar()const
	{
		return m_CanSeeAvatar;
	};

	void SetCanSeeAvatar(bool canSeeAvatar)
	{
		m_CanSeeAvatar = canSeeAvatar;
	}

	Rectf GetAvatarShape() const
	{
		return m_AvatarShape;
	}

	Vector2f GetAvatarVelocity() const
	{
		return m_AvatarVelocity;
	}

	void SetAvatarInfo(const Rectf& shape,const Vector2f& velocity)
	{
		m_AvatarShape = shape;
		m_AvatarVelocity = velocity;
	}

	void Draw() const;

	Vector2f GetVelocity() const
	{
		return m_Velocity;
	}

	void Fall(float elapsedSec);

protected:

	void ChangeTexture(int amountOfFramesIfKilled, int amountOfFramesMoving, int amountOFFramesAtacking = 0);

	void SetBoundaries(float width, float height);

	Rectf GetBoundaries() const {
		return m_BoundariesBorder;
	}

	void SetVelocity(const Vector2f& velocity)
	{
		m_Velocity = velocity;
	}

private:

	Rectf m_BoundariesBorder;
	Rectf m_AvatarShape;

	Vector2f m_AvatarVelocity;
	Vector2f m_Velocity;

	bool m_CanSeeAvatar;
};


