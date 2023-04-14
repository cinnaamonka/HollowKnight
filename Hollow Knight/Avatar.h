#pragma once
#include "Level.h"
#include "Enemy.h"

class Avatar
{
public:

	Avatar();
	~Avatar();

	Avatar(const Avatar& other) = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar(Avatar&& other) = delete;
	Avatar& operator=(Avatar&& other) = delete;

	void Update(float elapsedSec, Level* pLevel);
	void Draw() const;
	void EnemyHit();
	Rectf GetShape() const;

private:

	void CheckState(const Level* pLevel);
	void MoveAvatar(float elapsedSec);
	void UpdateFrame(float elapsedSec);
	void ChangePosition(const Level* pLevel);

private:

	enum class ActionState
	{
		waiting,
		moving,
		collidingEnemy,
		jumping,
		begin
	};

	ActionState m_ActionState;

	Rectf m_Shape;
	Rectf m_SourceRect;

	Vector2f m_Velocity;
	Vector2f m_Acceleration;

	float m_HorSpeed;
	float m_JumpSpeed;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	float m_ClipHeight;
	float m_ClipWidth;
	float m_AnimTime;
	float m_PreviousPositionX;

	Texture* m_pSpritesTexture;
	
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	int m_AnimFrame;
	int m_Power;
	
	bool m_IsMovingRight;
	bool m_CanDoubleJump;
	bool m_HasDoubleJumped;
};
