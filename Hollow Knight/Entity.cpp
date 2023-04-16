#include "pch.h"
#include "Entity.h"
#include "Avatar.h"
#include "BaseEnemy.h"

#include <Texture.h>

Entity::Entity(const std::string& path) :
	m_AnimTime(0),
	m_NrOfFrames(0),
	m_NrFramesPerSec(0),
	m_AnimFrame(0),
	m_LifesAmount(2),
	isAlive( true )
{
	m_pTexture = new Texture{ path };
}

Entity::~Entity()
{
	delete m_pTexture;
}

void Entity::UpdateFrame(float elapsedSec, int numberFrames)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / numberFrames)
	{
		++m_AnimFrame %= numberFrames;

		m_AnimTime = 0.0f;
	}
}
bool Entity::isWithinRange(Entity entity1, Entity entity2, float range)
{
    float distance = sqrt(pow(entity1.GetShape().left - entity2.GetShape().left, 2) + pow(entity1.GetShape().bottom - entity2.GetShape().bottom, 2));
    return distance <= range;
}

bool Entity::isPlayerVisible(Avatar player, BaseEnemy enemy)
{
    // Check if player is within range and if enemy has line of sight to player
    return isWithinRange(player, enemy, 10) && true;
}

void Entity::playerAttack(Avatar player, BaseEnemy& enemy)
{
    if (isWithinRange(player, enemy, 1)) {
        enemy. -= player.damage;
        if (enemy.health <= 0) {
            enemy.isAlive = false;
        }
    }
}

void enemyAttack(Player& player, Enemy enemy) {
    if (isWithinRange(player, enemy, 1)) {
        player.health -= enemy.damage;
        if (player.health <= 0) {
            player.isAlive = false;
        }
    }
}
