#pragma once

#include "Enemy.h"
#include <vector>

#include <structs.h>

class EnemyManager final
{
public:
	EnemyManager( );
	~EnemyManager( );

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;

	Enemy* AddItem( const Point2f &center);
	void Update( float elapsedSec );
	void Draw( ) const;

	size_t Size( ) const;
	bool HitItem( const Rectf& rect ) ;

private:
	std::vector<Enemy*> m_pItems;

	// Your helper functions
};
