#pragma once

#include "BaseEnemy.h"
	
class EnemyDragonfly : public BaseEnemy
{
public:
	explicit EnemyDragonfly(const Point2f& position);

	EnemyDragonfly(const EnemyDragonfly& other) = delete;
	EnemyDragonfly& operator=(const EnemyDragonfly& other) = delete;
	EnemyDragonfly(EnemyDragonfly&& other) = delete;
	EnemyDragonfly& operator=(EnemyDragonfly&& other) = delete;
	~EnemyDragonfly();

	virtual void Update(float elapsedSec)override;

};

