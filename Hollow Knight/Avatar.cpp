#include "pch.h"
#include "Avatar.h"
#include "Environment.h"

#include <chrono>
#include <thread>
#include <Texture.h>

Avatar::Avatar() :
	BaseMovingObject("Knight.png", 12),
	m_ClipHeight(0), m_ClipWidth(0), m_HorSpeed(500.0f),
	m_JumpSpeed(500.0f), m_Velocity{ 0.0f, 0.0f }, m_Acceleration{ 0, -981.0f },
	m_ActionState{ ActionState::begin }, m_AccuTransformSec{ 0.0f }, m_MaxTransformSec{ 1.0f },
	m_IsMovingRight{ true }, m_CanDoubleJump{ false },
	m_HasDoubleJumped{ false }, m_IsNovingAfterCollision{ false }, m_IsKilling{ false }
{

	Rectf sourceRect{ 0,0,0,0 };

	sourceRect.width = GetTexture()->GetWidth() / GetFramesNumber();
	sourceRect.height = GetTexture()->GetHeight();

	SetSourceRect(sourceRect);

	m_ClipWidth = GetTexture()->GetWidth() / GetFramesNumber();
	m_ClipHeight = GetTexture()->GetHeight() / GetFramesNumber();

	const Point2f avatar_Start_Position(2162.f, 5500.f);

	SetShape(Rectf(avatar_Start_Position.x, avatar_Start_Position.y, m_ClipWidth, m_ClipHeight));
}

Avatar::~Avatar()
{

}

void Avatar::Update(float elapsedSec, Environment* pLevel)
{
	Rectf currentShape = GetShape();

	pLevel->HandleCollision(currentShape, m_Velocity);
	SetShape(currentShape);
	CheckState(pLevel);

	const int movementFrames = 9;

	UpdateFrame(elapsedSec, movementFrames);

	ChangeTexture(pLevel);

	const Rectf bounds = pLevel->GetBoundaries();

	if ((currentShape.left <= 0.0f && m_Velocity.x < 0) ||
		(currentShape.left + currentShape.width >= bounds.left + bounds.width && m_Velocity.x > 0))
	{

		SetShape(Rectf(bounds.left + bounds.width - currentShape.width, currentShape.bottom, currentShape.width, currentShape.height));
	}

	if (!pLevel->IsOnGround(currentShape))
	{
		MoveAvatar(elapsedSec);

		return;
	}

	if (m_ActionState == ActionState::collidingEnemy && !m_IsNovingAfterCollision && !m_IsKilling)
	{
		if (m_IsMovingRight)
		{
			m_Velocity.x = -m_HorSpeed;

			SetShape(currentShape);
		}
		else
		{
			m_Velocity.x = m_HorSpeed;
		}

		m_Velocity.y = m_JumpSpeed;

		m_IsNovingAfterCollision = true;
		MoveAvatar(elapsedSec);
		return;
	}

	MoveAvatar(elapsedSec);

	m_CanDoubleJump = false;
	m_HasDoubleJumped = false;

	if (m_ActionState != ActionState::collidingEnemy && m_IsNovingAfterCollision)
	{
		m_IsNovingAfterCollision = false;
	}

	m_ActionState = ActionState::waiting;

}

void Avatar::Draw()const
{
	std::cout << GetShape().left << "," << GetShape().bottom << std::endl;
	//to make the character flip during running to the left
	if (!m_IsMovingRight)
	{
		glPushMatrix();

		glTranslatef(GetShape().left, GetShape().bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-GetShape().width, 0, 0);
		GetTexture()->Draw(Point2f(0, 0), GetSourceRect());
		glPopMatrix();
	}
	else
	{
		GetTexture()->Draw(GetShape(), GetSourceRect());
	}
}

void Avatar::EnemyHit()
{

	m_ActionState = ActionState::collidingEnemy;

}
void Avatar::Die()
{
	m_ActionState = ActionState::dying;
	m_ShapeBeforeDying = GetShape();
}
bool Avatar::IsAtacking()const
{
	return m_IsKilling;
}


void Avatar::CheckState(const Environment* pLevel)
{
	Rectf currentShape = GetShape();

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);


	if (m_ActionState == ActionState::begin || m_ActionState == ActionState::dying)
		return;

	if (pStates[SDL_SCANCODE_RIGHT] && m_ActionState != ActionState::collidingEnemy && !m_IsNovingAfterCollision)
	{
		m_ActionState = ActionState::moving;
		m_IsMovingRight = true;
		m_Velocity.x = m_HorSpeed;
	}

	if (pStates[SDL_SCANCODE_LEFT] && m_ActionState != ActionState::collidingEnemy && !m_IsNovingAfterCollision)
	{
		m_ActionState = ActionState::moving;
		m_IsMovingRight = false;
		m_Velocity.x = -m_HorSpeed;
	}

	// handle single jump
	if (pStates[SDL_SCANCODE_UP] && !m_CanDoubleJump && pLevel->IsOnGround(currentShape))
	{
		m_ActionState = ActionState::jumping;
		m_Velocity.y = m_JumpSpeed;

		std::thread timer([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			m_CanDoubleJump = true;
			});

		timer.detach();
	}
	// handle double jump
	else if (pStates[SDL_SCANCODE_UP] && m_CanDoubleJump && !m_HasDoubleJumped)
	{
		m_ActionState = ActionState::jumping;
		m_Velocity.y = m_JumpSpeed;

		m_HasDoubleJumped = true;
		m_CanDoubleJump = false;
	}

	if (pStates[SDL_SCANCODE_X])
	{
		m_IsKilling = true;
	}
}

void Avatar::MoveAvatar(float elapsedSec)
{
	Rectf currentShape = GetShape();
	const float maxGround_Offset = 70.0f;
	const float groundOffset = 15.0f;

	if (m_ActionState != ActionState::dying)
	{
		currentShape.bottom += m_Velocity.y * elapsedSec;
	}


	if (m_ActionState == ActionState::moving)
	{
		currentShape.left += m_Velocity.x * elapsedSec;
	}
	if (m_ActionState == ActionState::collidingEnemy)
	{
		currentShape.left += (m_Velocity.x) * elapsedSec;
	}

	if (m_Velocity.y >= m_Acceleration.y && m_ActionState != ActionState::dying)
	{
		m_Velocity.y += m_Acceleration.y * elapsedSec;
	}
	if (m_ActionState == ActionState::dying)
	{

		if (currentShape.bottom - m_ShapeBeforeDying.bottom < maxGround_Offset)
		{
			currentShape.bottom += groundOffset * elapsedSec;
		}

	}

	SetShape(currentShape);
}

void Avatar::ChangeTexture(const Environment* pLevel)
{
	Rectf srcRect{ 0.0f, m_ClipHeight, m_ClipWidth, m_ClipHeight };
	Rectf currentShape = GetShape();

	const int dyingTextureHorizontalOffset = 3;
	const int dyingTextureVerticalOffset = 12;
	const int collidingEnemyTextureVerticalOffset = 11;
	const int dyingTextureAmount = 1;
	const int killingTextureVerticalOffset = 4;
	const int jumpingTextureVerticalOffset = 10;

	srcRect.left = GetAnimationFrame() * m_ClipWidth;

	if (m_ActionState == ActionState::dying)
	{
		SetAnimationFrame(dyingTextureAmount);
		srcRect.left = dyingTextureHorizontalOffset * m_ClipWidth;
		srcRect.bottom = dyingTextureVerticalOffset * m_ClipHeight;
		SetSourceRect(srcRect);
		return;
	}
	if (!pLevel->IsOnGround(currentShape))
	{
		if (m_ActionState == ActionState::collidingEnemy)
		{
			srcRect.bottom = collidingEnemyTextureVerticalOffset * m_ClipHeight;
			SetSourceRect(srcRect);
		}
		else
		{
			srcRect.bottom = (collidingEnemyTextureVerticalOffset - 1) * m_ClipHeight;
			SetSourceRect(srcRect);
		}

	}
	else
	{
		if (m_IsKilling)
		{
			if (GetAnimationFrame() != killingTextureVerticalOffset)
			{
				srcRect.bottom = (killingTextureVerticalOffset + 1) * m_ClipHeight;
			}
			else
			{
				m_IsKilling = false;
			}

			SetSourceRect(srcRect);
			return;
		}

		if (m_ActionState == ActionState::waiting)
		{
			srcRect.left = 0;
			srcRect.bottom = m_ClipHeight;
		}

		else if (m_ActionState == ActionState::moving)
		{
			srcRect.bottom = m_ClipHeight;
		}
		else if (m_ActionState == ActionState::begin || m_ActionState == ActionState::jumping)
		{

			srcRect.bottom = jumpingTextureVerticalOffset * m_ClipHeight;
		}

		SetSourceRect(srcRect);
	}
}
