#include "pch.h"
#include "PowerUpManager.h"
PowerUpManager::PowerUpManager()
{

}
PowerUpManager::~PowerUpManager()
{

}
PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	PowerUp* pPowerUp = new PowerUp{ center,type };

	m_pItems.push_back(pPowerUp);

	return pPowerUp;
}
void PowerUpManager::Draw() const
{
	for (PowerUp* pPowerUp : m_pItems)
	{
		pPowerUp->Draw();
	}
}
void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* pPowerUp : m_pItems)
	{
		pPowerUp->Update(elapsedSec);
	}
}
size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}
bool PowerUpManager::HitItem(const Rectf& rect)
{
	if (m_pItems.size() == 0)return false;;
	PowerUp* pNewPowerUp = m_pItems.back();

	for (int i = 0;i < m_pItems.size();++i)
	{
		if (m_pItems[i]->IsOverlapping(rect))
		{
			m_pItems.back() = m_pItems[i];
			m_pItems[i] = pNewPowerUp;
			m_pItems.pop_back();

			return true;
		}
	}

	return false;
}