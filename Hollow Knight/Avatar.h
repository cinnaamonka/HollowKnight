#pragma once

class Environment;

#include "BaseMovingObject.h"

class Avatar final : public BaseMovingObject 
{
public:

	Avatar();
	~Avatar();

	Avatar(const Avatar& other) = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar(Avatar&& other) = delete;
	Avatar& operator=(Avatar&& other) = delete;

	void Update(float elapsedSec, Environment* pLevel, bool isFocusing);
	void Draw() const override;
	void EnemyHit();
	bool IsAtacking()const;
	void Die();

	const Vector2f& GetVelocity()const
	{
		return m_Velocity;
	}
	bool isColliding() const
	{
		if (m_ActionState == ActionState::collidingEnemy)
		{
			return true;
		}
		return false;
	}

	bool isFocusing()
	{
		return m_IsFocusing;
	}

private:

	void CheckState(const Environment* pLevel, bool isFocusing);
	void MoveAvatar(float elapsedSec);
	void ChangeTexture(const Environment* pLevel);

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

	Rectf m_ShapeBeforeDying;
	Rectf m_ParticlesShape;

	Texture* m_pParticleTexture;

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
	bool m_IsFocusing;
};
