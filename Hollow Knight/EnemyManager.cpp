#include "pch.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{

}

Enemy* EnemyManager::AddItem(const Point2f& center)
{
	Enemy* pPowerUp = new Enemy{ center};

	m_pItems.push_back(pPowerUp);

	return pPowerUp;
}

void EnemyManager::Draw() const
{

	for (Enemy* Enemy : m_pItems)
	{
		
		Enemy->Draw();
	}
}

void EnemyManager::Update(float elapsedSec)
{
	for (Enemy* Enemy : m_pItems)
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
	if (m_pItems.empty()) return false;

	
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
