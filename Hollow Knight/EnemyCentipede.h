#pragma once

#include "BaseEnemy.h"

class EnemyCentipede : public BaseEnemy
{
public:

	explicit EnemyCentipede(const Point2f& position);

	void Update(float elapsedSec);
	void Draw() const;

private:

	float m_SpeedX;
};

