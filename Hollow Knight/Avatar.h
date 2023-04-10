#pragma once
#include "Level.h"
#include "PowerUp.h"

class Avatar
{
public:
	Avatar();
	void Update(float elapsedSec, Level& level);
	void Draw() const;
	void PowerUpHit();
	Rectf GetShape()const;


private:
	enum class ActionState
	{
		waiting,
		moving,
		transforming,
		jumping,
		begin
	};

	Rectf m_Shape;
	float m_HorSpeed;
	float m_JumpSpeed;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	int m_Power;
	Texture* m_pSpritesTexture;
	float m_ClipHeight;
	float m_ClipWidth;
	int   m_NrOfFrames;
	int   m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
	
	Rectf m_SourceRect;
	void CheckState(Level& level);
	void MoveAvatar(float elapsedSec);
	void UpdateFrame(float elapsedSec);
	void ChangePosition(Level& level);
	float m_PreviousPositionX;
	
	bool isMovingRight;
};
