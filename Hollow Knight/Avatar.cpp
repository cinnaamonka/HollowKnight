#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"

#include <chrono>
#include <thread>

Avatar::Avatar() :
	BaseMovingObject("Knight.png"),
	m_ClipHeight(0), m_ClipWidth(0), m_HorSpeed(500.0f),
	m_JumpSpeed(500.0f), m_Velocity{ 0.0f, 0.0f }, m_Acceleration{ 0, -981.0f },
	m_ActionState{ ActionState::begin }, m_AccuTransformSec{ 0.0f }, m_MaxTransformSec{ 1.0f },
	m_IsMovingRight{ true }, m_CanDoubleJump{ false },
	m_HasDoubleJumped{ false }, m_IsNovingAfterCollision{ false }
{
	SetFramesNumber(12);

	Rectf sourceRect{ 0,0,0,0 };

	sourceRect.width = GetTexture()->GetWidth() / GetFramesNumber();
	sourceRect.height = GetTexture()->GetHeight();

	SetSourceRect(sourceRect);

	m_ClipWidth = GetTexture()->GetWidth() / GetFramesNumber();
	m_ClipHeight = GetTexture()->GetHeight() / GetFramesNumber();

	SetShape(Rectf(2162, 5500, m_ClipWidth, m_ClipHeight));
}

Avatar::~Avatar()
{

}

void Avatar::Update(float elapsedSec, Level* pLevel)
{
	std::cout << GetShape().left << "," << GetShape().bottom << std::endl;
	Rectf currentShape = GetShape();

	pLevel->HandleCollision(currentShape, m_Velocity);
	SetShape(currentShape);
	CheckState(pLevel);

	UpdateFrame(elapsedSec, 9);


	ChangeTexture(pLevel);

	if (!pLevel->IsOnGround(currentShape, m_Velocity))
	{
		MoveAvatar(elapsedSec);

		return;
	}

	if (m_ActionState == ActionState::collidingEnemy && !m_IsNovingAfterCollision)
	{
		if (m_IsMovingRight)
		{
			m_Velocity.x = - 1.5f * m_HorSpeed;
		}
		else
		{
			m_Velocity.x = 1.5f * m_HorSpeed;
		}

		m_Velocity.y = m_JumpSpeed;

		m_IsNovingAfterCollision = true;
		MoveAvatar(elapsedSec);
		return;
	}


	const Rectf bounds = pLevel->GetBoundaries();

	if ((currentShape.left <= 0.0f && m_Velocity.x < 0) ||
		(currentShape.left + currentShape.width >= bounds.left + bounds.width && m_Velocity.x > 0))
	{
		m_ActionState = ActionState::waiting;

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

void Avatar::CheckState(const Level* pLevel)
{
	Rectf currentShape = GetShape();

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);


	if (m_ActionState == ActionState::begin)
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
	if (pStates[SDL_SCANCODE_UP] && !m_CanDoubleJump && pLevel->IsOnGround(currentShape, m_Velocity))
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
}

void Avatar::MoveAvatar(float elapsedSec)
{
	Rectf currentShape = GetShape();

	currentShape.bottom += m_Velocity.y * elapsedSec;

	if (m_ActionState == ActionState::moving)
	{
		currentShape.left += m_Velocity.x * elapsedSec;
	}
	if (m_ActionState == ActionState::collidingEnemy)
	{

		currentShape.left += (m_Velocity.x) * elapsedSec;
	}

	if (m_Velocity.y >= m_Acceleration.y)
	{
		m_Velocity.y += m_Acceleration.y * elapsedSec;
	}

	SetShape(currentShape);
}

void Avatar::ChangeTexture(const Level* pLevel)
{
	Rectf srcRect{ 0.0f, m_ClipHeight, m_ClipWidth, m_ClipHeight };
	Rectf currentShape = GetShape();

	srcRect.left = GetAnimationFrame() * m_ClipWidth;
	std::cout << int(m_ActionState) << std::endl;
	if (!pLevel->IsOnGround(currentShape, m_Velocity))
	{
		if (m_ActionState == ActionState::collidingEnemy)
		{
			srcRect.bottom =11 * m_ClipHeight;
			SetSourceRect(srcRect);
		}
		else
		{
			
			srcRect.bottom = 10 * m_ClipHeight;
			SetSourceRect(srcRect);
		}
		
	}
	else
	{
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

			srcRect.bottom = 10 * m_ClipHeight;
		}


		SetSourceRect(srcRect);
	}

	SetShape(currentShape);
}