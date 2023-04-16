#pragma once

class Level;

#include "BaseMovingObject.h"

class Avatar : public BaseMovingObject
{
public:

	Avatar();
	~Avatar();

	Avatar(const Avatar& other) = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar(Avatar&& other) = delete;
	Avatar& operator=(Avatar&& other) = delete;

	void Update(float elapsedSec, Level* pLevel);
	void Draw() const override;
	void EnemyHit();
	bool IsAtacking();
	void Die();

private:

	void CheckState(const Level* pLevel);
	void MoveAvatar(float elapsedSec);
	void ChangeTexture(const Level* pLevel);

private:

	enum class ActionState
	{
		waiting,
		moving,
		collidingEnemy,
		jumping,
		begin,
		dying
	};

	ActionState m_ActionState;

	Vector2f m_Velocity;
	Vector2f m_Acceleration;

	float m_HorSpeed;
	float m_JumpSpeed;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	float m_ClipHeight;
	float m_ClipWidth;

	bool m_IsMovingRight;
	bool m_CanDoubleJump;
	bool m_HasDoubleJumped;
	bool m_IsNovingAfterCollision;
	bool m_IsKilling;
};
