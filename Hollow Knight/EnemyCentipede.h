#pragma once

#include "BaseEnemy.h"

class EnemyCentipede final : public BaseEnemy
{
public:

	explicit EnemyCentipede(const Point2f& position);
	EnemyCentipede(const EnemyCentipede& other) = delete;
	EnemyCentipede& operator=(const EnemyCentipede& other) = delete;
	EnemyCentipede(EnemyCentipede&& other) = delete;
	EnemyCentipede& operator=(EnemyCentipede&& other) = delete;
	~EnemyCentipede();

	virtual void Update(float elapsedSec)override;
};

