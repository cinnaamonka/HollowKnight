#include "pch.h"
#include "PowerUpManager.h"
PowerUpManager::PowerUpManager()
{

}

PowerUpManager::~PowerUpManager()
{

}

Enemy* PowerUpManager::AddItem(const Point2f& center)
{
	Enemy* pPowerUp = new Enemy{ center};

	m_pItems.push_back(pPowerUp);

	return pPowerUp;
}

void PowerUpManager::Draw() const
{
	for (Enemy* Enemy : m_pItems)
	{
		Enemy->Draw();
	}
}

void PowerUpManager::Update(float elapsedSec)
{
	for (Enemy* Enemy : m_pItems)
	{
		Enemy->Update(elapsedSec);
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	if (m_pItems.empty()) return false;


	for (auto& item : m_pItems)
	{
		if (item->IsOverlapping(rect))
		{
			std::swap(item, m_pItems.back());
			m_pItems.pop_back();

			return true;
		}
	}

	return false;
}
