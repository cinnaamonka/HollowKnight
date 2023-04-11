#include "pch.h"
#include "Avatar.h"
#include "utils.h"
#include "iostream"
#include "Texture.h"

class Texture;

Avatar::Avatar() :
	m_ClipHeight{},
	m_ClipWidth{},
	m_Shape{ 2162, 5500, 0,0 },
	m_HorSpeed{ 600 },
	m_JumpSpeed{ 600.0f },
	m_Velocity{ 0.0f, 0.0f },
	m_Acceleration{ 0, -981.0f },
	m_ActionState{ ActionState::begin },
	m_AccuTransformSec{ 0.0f },
	m_MaxTransformSec{ 1.0f },
	m_Power{ 0 },
	m_PreviousPositionX{ m_Shape.left },
	m_NrOfFrames{ 12 },
	m_NrFramesPerSec{ 1 },
	m_AnimTime{ 0 },
	m_AnimFrame{ 0 },
	isMovingRight{ true }
	

{
	m_pSpritesTexture = new Texture{ "Knight.png" };

	m_ClipWidth = m_pSpritesTexture->GetWidth() / m_NrOfFrames;
	m_ClipHeight = m_pSpritesTexture->GetHeight() / m_NrOfFrames;

	m_Shape.width = m_ClipWidth;
	m_Shape.height = m_ClipHeight;

}

void Avatar::Update(float elapsedSec, Level& level)
{

	level.HandleCollision(m_Shape, m_Velocity);

	CheckState(level);

	UpdateFrame(elapsedSec);

	ChangePosition(level);
	
	if (!level.IsOnGround(m_Shape, m_Velocity) && ActionState::transforming != m_ActionState)
	{
		MoveAvatar(elapsedSec);

		return;
	}


	if (ActionState::transforming == m_ActionState)
	{
		m_AccuTransformSec += elapsedSec;

		if (m_AccuTransformSec >= m_MaxTransformSec)
		{
			m_AccuTransformSec = 0;
			m_ActionState = ActionState::waiting;
		}

		return;
	}

	if (!level.IsOnGround(m_Shape, m_Velocity)) return;


	if ((m_Shape.left <= 0.0f && m_Velocity.x < 0) || (m_Shape.left + m_Shape.width >= level.GetBoundaries().left + level.GetBoundaries().width && m_Velocity.x > 0))
	{
		
		m_ActionState = ActionState::waiting;

		return;
	}

	MoveAvatar(elapsedSec);

	std::cout << int(m_ActionState) << std::endl;
	m_ActionState = ActionState::waiting;
}

void Avatar::Draw() const
{
	//to make the character flip during running to the left
	if (!isMovingRight)
	{
		glPushMatrix();

		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-m_Shape.width, 0, 0);
		m_pSpritesTexture->Draw(Point2f(0, 0), m_SourceRect);

		glPopMatrix();
		utils::DrawRect(m_Shape);
		return;
	}
	float borderDist{ 5.f };

	const Point2f ray1{ m_Shape.left + borderDist, m_Shape.bottom + m_Shape.height / 2 };
	const Point2f ray2{ m_Shape.left + borderDist, m_Shape.bottom + m_Shape.height };
	const Point2f ray3{ m_Shape.left + m_Shape.width - borderDist, m_Shape.bottom + m_Shape.height / 2 };
	const Point2f ray4{ m_Shape.left + m_Shape.width - borderDist, m_Shape.bottom + m_Shape.height };
	const Point2f ray5{ m_Shape.left, m_Shape.bottom + m_Shape.height - borderDist };
	const Point2f ray6{ m_Shape.left + m_Shape.width,m_Shape.bottom + m_Shape.height - borderDist };
	utils::DrawLine(ray1, ray2);
	utils::DrawLine(ray3, ray4);
	utils::DrawLine(ray5, ray6);
	utils::DrawRect(m_Shape);
	m_pSpritesTexture->Draw(m_Shape, m_SourceRect);
}

void Avatar::PowerUpHit()
{
	m_Power++;
	//m_ActionState = ActionState::transforming;

}

Rectf Avatar::GetShape()const
{
	return m_Shape;
}

void Avatar::CheckState(Level& level)
{
	if (m_ActionState == ActionState::begin) return;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_ActionState = ActionState::moving;
		isMovingRight = true;
		m_Velocity.x = m_HorSpeed;
	}

	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_ActionState = ActionState::moving;
		isMovingRight = false;
		m_Velocity.x = -m_HorSpeed;
	}

	if (pStates[SDL_SCANCODE_UP] && level.IsOnGround(m_Shape, m_Velocity))
	{
		m_ActionState = ActionState::jumping;

		m_Velocity.y = m_JumpSpeed;
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

void Avatar::ChangePosition(Level& level)
{
	Rectf srcRect
	{
		0.0f,
		m_ClipHeight,
		m_ClipWidth,
		m_ClipHeight
	};

	srcRect.left = m_AnimFrame * m_ClipWidth;

	if (!level.IsOnGround(m_Shape, m_Velocity))
	{
		srcRect.bottom = 10 * m_ClipHeight;
		m_SourceRect = srcRect;

		return;

	}

	if (m_ActionState == ActionState::waiting)
	{
		srcRect.left = 0;
		srcRect.bottom = m_ClipHeight;
	}

	if (m_ActionState == ActionState::moving)
	{
		srcRect.bottom = m_ClipHeight;
	}

	if (m_ActionState == ActionState::begin || m_ActionState == ActionState::jumping)
	{
		srcRect.bottom = 10 * m_ClipHeight;
	}

	if (m_ActionState == ActionState::transforming)
	{
		srcRect.bottom += ((m_Power - 1) * m_ClipHeight * 3 + int(ActionState::transforming) * m_ClipHeight);
	}


	m_SourceRect = srcRect;
}