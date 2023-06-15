#include "pch.h"
#include "BaseEnemy.h"
#include "EnemyManager.h"
#include "Environment.h"

#include <SoundEffect.h>

EnemyManager::EnemyManager()
{
	m_pDyingSound = new SoundEffect("EnemyDamage.wav");
}

EnemyManager::~EnemyManager()
{
	delete m_pDyingSound;
}

void EnemyManager::Update(float elapsedSec, Environment* pLevel)
{
	for (BaseEnemy* Enemy : GetItems())
	{
		Enemy->Update(elapsedSec);

		Rectf enemyShape = Rectf(Enemy->GetShape().left, Enemy->GetShape().bottom + Enemy->GetShape().width / 3, Enemy->GetShape().width, Enemy->GetShape().height);

		if (!pLevel->IsOnGround(enemyShape, true) && Enemy->IsKilled())
		{
			Enemy->Fall(elapsedSec);
		}
	}
}

bool EnemyManager::HitItem(const Rectf& rect)
{
	if (m_pItems.empty()) return false;

	for (const BaseEnemy* Enemy : m_pItems)
	{
		if (Enemy->IsOverlapping(rect) && !Enemy->IsKilled())
		{
			return true;
		}
		else if (Enemy->IsKilled())
		{
			m_pDyingSound->Stop();
		}
	}

	return false;
}

bool EnemyManager::IsEnemyKilled(const Rectf& actor) const
{
	for (BaseEnemy* Enemy : GetItems())
	{
		if (Enemy->IsOnCloseDistance(actor) && !Enemy->IsKilled())
		{
			if (Enemy->GetLifesAmount() >= 0)
			{
				m_pDyingSound->SetVolume(m_SoundVolume);
				m_pDyingSound->Play(0);

				Enemy->DecreaseLifesAmount();
			}
			else
			{
				Enemy->SetKilled(true);

				return true;
			}
		}
	}

	return false;
}

void EnemyManager::Attack(const Rectf& actor, const Vector2f& velocity)const
{

	for (BaseEnemy* Enemy : GetItems())
	{
		if (Enemy->CanSeeAvatar(actor))
		{
			Enemy->SetCanSeeAvatar(true);
			Enemy->SetAvatarInfo(actor, velocity);
		}
		else
		{
			Enemy->SetCanSeeAvatar(false);
		}

	}
}

