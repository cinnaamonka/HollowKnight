#pragma once

#include "BaseManager.h"

class BaseEnemy;
class Environment;
class SoundEffect;

class EnemyManager final :public BaseManager<BaseEnemy>
{
public:
	EnemyManager();
	~EnemyManager();

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;


	void Update(float elapsedSec, Environment* pLevel);

	bool HitItem(const Rectf& rect);

	bool IsEnemyKilled(const Rectf& actor) const;

	void Attack(const Rectf& actor, const Vector2f& velocity)const;

private:
	SoundEffect* m_pDyingSound;
};
