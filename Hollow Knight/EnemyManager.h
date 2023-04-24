#pragma once

#include <vector>

class BaseEnemy;

class EnemyManager final
{
public:
	EnemyManager( );
	~EnemyManager( );

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;

	void AddItem(BaseEnemy *pEnemy);

	void Update( float elapsedSec );
	void Draw( ) const;

	size_t Size( ) const;
	bool HitItem( const Rectf& rect ) ;

	bool IsEnemyKilled(const Rectf& actor) const;

	void Atack(const Rectf& actor, const Vector2f& velocity);

private:

	std::vector<BaseEnemy *> m_pItems;

};
