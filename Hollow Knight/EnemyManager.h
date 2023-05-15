#pragma once

#include <vector>
#include "BaseManager.h"
class BaseEnemy;
class Environment;

class EnemyManager final :public BaseManager<BaseEnemy>
{
public:
	EnemyManager( );
	~EnemyManager( );

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;


	void Update( float elapsedSec, Environment* pLevel);

	bool HitItem( const Rectf& rect );

	bool IsEnemyKilled(const Rectf& actor) const;

	void Atack(const Rectf& actor, const Vector2f& velocity)const;

};
