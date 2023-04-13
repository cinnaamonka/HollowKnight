#include "pch.h"
#include "Enemy.h"
#include "Texture.h"
#include "Game.h"
#include "iostream"

Enemy::Enemy(const Point2f& center) :

	m_Speed{ 200.0f },
	m_SourceRect{},
	m_Shape{ 2400, 5500,0,0 },
	m_NrOfFrames{ 4 },
	m_NrFramesPerSec{ 0 },
	m_AnimTime{ 0 },
	m_AnimFrame{ 0 },
	m_BoundariesBorder{}
{


	//int   m_NrOfFrames;
	//int   m_NrFramesPerSec;
	//float m_AnimTime;
	//int m_AnimFrame;


	m_pEnemyTexture = new Texture{ "Enemy.png" };

	m_SourceRect.left = 0.0f;
	m_SourceRect.bottom = m_pEnemyTexture->GetHeight() / 2;
	m_SourceRect.width = m_pEnemyTexture->GetWidth() / 3;
	m_SourceRect.height = m_pEnemyTexture->GetHeight() / 2;

	m_Shape.left = center.x;
	m_Shape.bottom = center.y;
	m_Shape.width = m_SourceRect.width;
	m_Shape.height = m_SourceRect.height;

	m_BoundariesBorder.left = center.x;
	m_BoundariesBorder.bottom = center.y;
	m_BoundariesBorder.width = 120.0f;
	m_BoundariesBorder.height = m_SourceRect.height;

}

Enemy::~Enemy()
{
	delete m_pEnemyTexture;
}

void Enemy::Update(float elapsedSec)
{
	UpdateFrame(elapsedSec);

	ChangePosition();

	if (m_Shape.left + m_Shape.width >= m_BoundariesBorder.left /*|| m_Shape.left <= m_Boundaries.left*/)
	{
		m_Speed *= -1;
	}

	m_Shape.left += m_Speed * elapsedSec;
}

void Enemy::Draw() const
{
	if (m_Speed < 0)
	{
		glPushMatrix();

		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-m_Shape.width, 0, 0);
		m_pEnemyTexture->Draw(Point2f(0, 0), m_SourceRect);

		glPopMatrix();

		return;
	}

	m_pEnemyTexture->Draw(Point2f(0, 0), m_SourceRect);

}

bool Enemy::IsOverlapping(const Rectf& rect) const
{
	const float left = rect.left;
	const float right = rect.left + rect.width;
	const float bottom = rect.bottom;
	const float top = rect.bottom + rect.height;


	bool isColliding
	{
		rect.left <= m_Shape.left + m_Shape.width &&
		rect.left + rect.width >= m_Shape.left
	};

	return isColliding;
}
void Enemy::UpdateFrame(float elapsedSec)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / 9)
	{
		++m_AnimFrame %= 9;

		m_AnimTime = 0.0f;
	}

}
void Enemy::ChangePosition()
{

	m_SourceRect.left = m_AnimFrame * m_SourceRect.width;

	m_SourceRect.left = 0;
	m_SourceRect.bottom = m_SourceRect.height;



}


