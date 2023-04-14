#include "pch.h"
#include "BaseEnemy.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{
	for (const BaseEnemy* Enemy : m_pItems)
	{
		delete Enemy;
	}
}

void EnemyManager::AddItem(BaseEnemy *enemy)
{
	m_pItems.push_back(enemy);
}

void EnemyManager::Draw() const
{
	for (const BaseEnemy* Enemy : m_pItems)
	{
		Enemy->Draw();
	}
}

void EnemyManager::Update(float elapsedSec)
{
	for (BaseEnemy* Enemy : m_pItems)
	{
		Enemy->Update(elapsedSec);
	}
}

size_t EnemyManager::Size() const
{
	return m_pItems.size();
}

bool EnemyManager::HitItem(const Rectf& rect)
{
	if (m_pItems.empty()) // TODO: Do I really need this check?
		return false;

	for (auto& item : m_pItems)
	{
		if (item->IsOverlapping(rect))
		{
			std::cout << "overlaps" << std::endl;
			std::swap(item, m_pItems.back());

			return true;
		}
	}

	return false;
}
