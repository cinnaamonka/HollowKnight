#pragma once

#include "BaseMovingObject.h"
class Coin;

class BaseEnemy : public BaseMovingObject
{
public:

	explicit BaseEnemy(const Point2f& position, const std::string &texture);
	virtual ~BaseEnemy();

	BaseEnemy(const BaseEnemy& other) = delete;
	BaseEnemy& operator=(const BaseEnemy& other) = delete;
	BaseEnemy(BaseEnemy&& other) = delete;
	BaseEnemy& operator=(BaseEnemy&& other) = delete;

	virtual void Update(float elapsedSec);

	bool IsOverlapping(const Rectf& rect) const;

	bool IsOnCloseDistance(const Rectf& rect) const;

	void DrawCoins()const;

protected:

	void ChangeTexture();

	void SetBoundaries(float width, float height);

	Rectf GetBoundaries() const {
		return m_BoundariesBorder;
	}

private:

	Rectf m_BoundariesBorder;

	std::vector<Coin*> m_pCoins;
};


