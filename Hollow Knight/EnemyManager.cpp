#include "pch.h"
#include "BaseEnemy.h"
#include "EnemyManager.h"
#include "Environment.h"

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

void EnemyManager::AddItem(BaseEnemy* enemy)
{
	m_pItems.push_back(enemy);
}

void EnemyManager::Draw() const
{
	for (const BaseEnemy* pEnemy : m_pItems)
	{
		pEnemy->Draw();
	}
}

void EnemyManager::Update(float elapsedSec, Environment* pLevel)
{
	for (BaseEnemy* Enemy : m_pItems)
	{
		Enemy->Update(elapsedSec);

		Rectf enemyShape = Rectf(Enemy->GetShape().left, Enemy->GetShape().bottom + Enemy->GetShape().width / 3, Enemy->GetShape().width, Enemy->GetShape().height);
		Vector2f enemyVelocity = Enemy->GetVelocity();
		
		if (!pLevel->IsOnGround(enemyShape,true) && Enemy->IsKilled())
		{
			Enemy->Fall(elapsedSec);
		}
	}
}

size_t EnemyManager::Size() const
{
	return m_pItems.size();
}

bool EnemyManager::HitItem(const Rectf& rect)
{
	if (m_pItems.empty())
		return false;

	for (auto& item : m_pItems)
	{
		if (item->IsOverlapping(rect) && !item->IsKilled())
		{
			std::swap(item, m_pItems.back());

			return true;
		}
	}

	return false;
}
bool EnemyManager::IsEnemyKilled(const Rectf& actor) const
{
	for (auto& item : m_pItems)
	{
		if (item->IsOnCloseDistance(actor) && !item->IsKilled())
		{
			if (item->GetLifesAmount() >= 1)
			{
				item->DecreaseLifesAmount();
			}
			else
			{
				item->SetKilled(true);
				return true;
			}
			
		}
		
	}
	return false;
}

void EnemyManager::Atack(const Rectf& actor, const Vector2f& velocity)const
{
	for (auto& item : m_pItems)
	{
		if (item->CanSeeAvatar(actor))
		{
			item->SetCanSeeAvatar(true);
			item->SetAvatarInfo(actor, velocity);
		}
		else
		{
			item->SetCanSeeAvatar(false);
		}

	}
}