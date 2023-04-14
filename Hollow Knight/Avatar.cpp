#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"

#include <chrono>
#include <thread>

Avatar::Avatar() :
	m_ClipHeight(0), m_ClipWidth(0), m_Shape{ 2162, 5500, 0,0 }, m_HorSpeed(500.0f),
	m_JumpSpeed(500.0f), m_Velocity{ 0.0f, 0.0f }, m_Acceleration{ 0, -981.0f },
	m_ActionState{ ActionState::begin }, m_AccuTransformSec{ 0.0f }, m_MaxTransformSec{ 1.0f },
	m_Power{ 0 }, m_PreviousPositionX{ m_Shape.left }, m_NrOfFrames{ 12 }, m_NrFramesPerSec{ 1 },
	m_AnimTime{ 0 }, m_AnimFrame{ 0 }, m_IsMovingRight{ true }, m_CanDoubleJump{ false },
	m_HasDoubleJumped{ false }
{
	m_pSpritesTexture = new Texture{ "Knight.png" };

	m_ClipWidth = m_pSpritesTexture->GetWidth() / m_NrOfFrames;
	m_ClipHeight = m_pSpritesTexture->GetHeight() / m_NrOfFrames;

	m_Shape.width = m_ClipWidth;
	m_Shape.height = m_ClipHeight;

}

Avatar::~Avatar()
{
	delete m_pSpritesTexture;
}

void Avatar::Update(float elapsedSec, Level* pLevel)
{
	pLevel->HandleCollision(m_Shape, m_Velocity);

	CheckState(pLevel);

	UpdateFrame(elapsedSec);

	ChangeTexture(pLevel);

	if (!pLevel->IsOnGround(m_Shape, m_Velocity))
	{
		MoveAvatar(elapsedSec);

		return;
	}
	if (m_ActionState == ActionState::collidingEnemy)
	{
		std::cout << "colliding enemy" << std::endl;
		m_Velocity.x = -m_HorSpeed;
		m_Velocity.y = m_JumpSpeed;
	
	}

	if (!pLevel->IsOnGround(m_Shape, m_Velocity))
		return;

	const Rectf bounds = pLevel->GetBoundaries();

	if ((m_Shape.left <= 0.0f && m_Velocity.x < 0) ||
		(m_Shape.left + m_Shape.width >= bounds.left + bounds.width && m_Velocity.x > 0))
	{
		m_ActionState = ActionState::waiting;

		return;
	}

	MoveAvatar(elapsedSec);

	m_CanDoubleJump = false;
	m_HasDoubleJumped = false;

	m_ActionState = ActionState::waiting;
}

void Avatar::Draw() const
{
	//to make the character flip during running to the left
	if (!m_IsMovingRight)
	{
		glPushMatrix();

		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-m_Shape.width, 0, 0);
		m_pSpritesTexture->Draw(Point2f(0, 0), m_SourceRect);
		utils::DrawRect(m_Shape);
		glPopMatrix();
	}
	else
	{
		utils::DrawRect(m_Shape);
		m_pSpritesTexture->Draw(m_Shape, m_SourceRect);
	}
}

void Avatar::EnemyHit()
{
	m_ActionState = ActionState::collidingEnemy;
	
}

Rectf Avatar::GetShape()const
{
	return m_Shape;
}

void Avatar::CheckState(const Level* pLevel)
{
	if (m_ActionState == ActionState::begin)
		return;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_ActionState = ActionState::moving;
		m_IsMovingRight = true;
		m_Velocity.x = m_HorSpeed;
	}

	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_ActionState = ActionState::moving;
		m_IsMovingRight = false;
		m_Velocity.x = -m_HorSpeed;
	}

	// handle single jump
	if (pStates[SDL_SCANCODE_UP] && !m_CanDoubleJump && pLevel->IsOnGround(m_Shape, m_Velocity))
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
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	if (m_ActionState == ActionState::moving)
	{

		m_PreviousPositionX = m_Shape.left;
		m_Shape.left += m_Velocity.x * elapsedSec;
	}
	if (m_ActionState == ActionState::collidingEnemy)
	{
		m_Shape.left += (m_Velocity.x) * elapsedSec;
	}

	if (m_Velocity.y >= m_Acceleration.y) {
		m_Velocity.y += m_Acceleration.y * elapsedSec;
	}
}

void Avatar::UpdateFrame(float elapsedSec)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / 9)
	{
		++m_AnimFrame %= 9;

		m_AnimTime = 0.0f;
	}

}

void Avatar::ChangeTexture(const Level* pLevel)
{
	Rectf srcRect { 0.0f, m_ClipHeight, m_ClipWidth, m_ClipHeight };

	srcRect.left = m_AnimFrame * m_ClipWidth;

	if (!pLevel->IsOnGround(m_Shape, m_Velocity))
	{
		srcRect.bottom = 10 * m_ClipHeight;
		m_SourceRect = srcRect;
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

		m_SourceRect = srcRect;
	}
}