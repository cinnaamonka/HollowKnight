#pragma once

#include "BaseMovingObject.h"

class BaseEnemy : public BaseMovingObject
{
public:

	explicit BaseEnemy(const Point2f& position, const std::string &texture);
	explicit BaseEnemy();
	virtual ~BaseEnemy();

	BaseEnemy(const BaseEnemy& other) = delete;
	BaseEnemy& operator=(const BaseEnemy& other) = delete;
	BaseEnemy(BaseEnemy&& other) = delete;
	BaseEnemy& operator=(BaseEnemy&& other) = delete;

	virtual void Update(float elapsedSec) = 0;

	bool IsOverlapping(const Rectf& rect) const;

	bool IsOnCloseDistance(const Rectf& rect) const;

protected:

	void ChangeTexture();

	void SetBoundaries(float width, float height);

	Rectf GetBoundaries() const {
		return m_BoundariesBorder;
	}

private:

	Rectf m_BoundariesBorder;

};


