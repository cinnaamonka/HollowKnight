#include "pch.h"
#include "Avatar.h"
#include "Environment.h"

#include <chrono>
#include <thread>
#include <Texture.h>
#include <SoundEffect.h>

Avatar::Avatar() :
	BaseMovingObject("Knight.png", 12),
	m_ClipHeight(0), m_ClipWidth(0), m_HorSpeed(500.0f),
	m_JumpSpeed(500.0f), m_Velocity{ 0.0f, 0.0f }, m_Acceleration{ 0, -981.0f },
	m_ActionState{ ActionState::begin }, m_AccuTransformSec{ 0.0f }, m_MaxTransformSec{ 1.0f },
	m_IsMovingRight{ true }, m_CanDoubleJump{ false },
	m_HasDoubleJumped{ false }, m_IsNovingAfterCollision{ false }, m_IsKilling{ false }, m_IsFocusing(false),
	isPlaying(false), m_IsOnGround(true)

{
	Rectf sourceRect{ 0,0,0,0 };

	sourceRect.width = GetTexture()->GetWidth() / GetFramesNumber();
	sourceRect.height = GetTexture()->GetHeight();

	SetSourceRect(sourceRect);

	m_ClipWidth = GetTexture()->GetWidth() / GetFramesNumber();
	m_ClipHeight = GetTexture()->GetHeight() / GetFramesNumber();

	const Point2f avatarStartPosition(2162.f, 5500.f);

	SetShape(Rectf(avatarStartPosition.x, avatarStartPosition.y, m_ClipWidth, m_ClipHeight));

	SetFramesPerSec(10);

	m_pParticleTexture = new Texture{ "ParticleEffect.png" };
	m_ParticlesShape = Rectf(0, 0, m_pParticleTexture->GetWidth(), m_pParticleTexture->GetHeight());

	m_pCharacterWalkingSound = new SoundEffect("soundWalking.wav");
	m_pKnifeInAir = new SoundEffect("KnightInAir.wav");

	m_pCollidesEnemy = new SoundEffect("EnemyDamage.wav");
}

Avatar::~Avatar()
{
	delete m_pParticleTexture;
	delete m_pCharacterWalkingSound;
	delete m_pKnifeInAir;
	delete m_pCollidesEnemy;
}
bool Avatar::isColliding() const
{
	if (m_ActionState == ActionState::collidingEnemy)
	{
		return true;
	}
	return false;
}
void Avatar::Update(float elapsedSec, Environment* pLevel, bool isFocusing)
{
	if (m_ActionState == ActionState::dying)
	{
		ChangeTexture(pLevel);
		MoveAvatar(elapsedSec);

		return;
	}
	Rectf currentShape = GetShape();

	pLevel->HandleCollision(currentShape, m_Velocity);
	SetShape(currentShape);
	CheckState(pLevel, isFocusing);

	const int movementFrames = 9;

	UpdateFrame(elapsedSec, movementFrames);

	ChangeTexture(pLevel);

	const Rectf bounds = pLevel->GetBoundaries();

	if ((currentShape.left <= 0.0f && m_Velocity.x < 0) ||
		(currentShape.left + currentShape.width >= bounds.left + bounds.width && m_Velocity.x > 0))
	{

		SetShape(Rectf(bounds.left + bounds.width - currentShape.width, currentShape.bottom, currentShape.width, currentShape.height));
	}

	if (!pLevel->IsOnGround(currentShape, false))
	{
		MoveAvatar(elapsedSec);
		m_IsOnGround = false;
		return;
	}
	else
	{
		m_IsOnGround = true;
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
	m_pCollidesEnemy->Stop();
}

void Avatar::Draw()const
{
	/*utils::SetColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	utils::DrawRect(GetShape());
	std::cout << GetShape().left <<"," << GetShape().bottom << std::endl;*/
	//to make the character flip during running to the left
	const Rectf particleShape
	{
		GetShape().left - GetShape().width / 2,
		GetShape().bottom - GetShape().height,
		GetShape().width * 2,
		GetShape().height * 2

	};
	if (m_IsFocusing)
	{
		m_pParticleTexture->Draw(particleShape, m_ParticlesShape);

	}
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

	std::cout << "On ground" << std::endl;
	m_pCollidesEnemy->Play(-1);

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
void Avatar::CheckState(const Environment* pLevel, bool isFocusing)
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

		m_pCharacterWalkingSound->Play(-1);

	}

	if (pStates[SDL_SCANCODE_LEFT] && m_ActionState != ActionState::collidingEnemy && !m_IsNovingAfterCollision)
	{
		m_ActionState = ActionState::moving;
		m_IsMovingRight = false;
		m_Velocity.x = -m_HorSpeed;

		m_pCharacterWalkingSound->Play(-1);
	}

	if (pStates[SDL_SCANCODE_X])
	{
		m_IsKilling = true;

		m_pKnifeInAir->Play(-1);
	}
	else {
		m_pKnifeInAir->Stop();
	}

	if ((!pStates[SDL_SCANCODE_RIGHT] && !pStates[SDL_SCANCODE_LEFT]) || !pLevel->IsOnGround(currentShape, false))
	{
		m_pCharacterWalkingSound->Stop();
	}

	if (pStates[SDL_SCANCODE_A] && m_ActionState != ActionState::collidingEnemy && !m_IsNovingAfterCollision && isFocusing)
	{
		m_IsFocusing = true;
	}
	else
	{
		m_IsFocusing = false;
	}

	// handle single jump
	if (pStates[SDL_SCANCODE_UP] && !m_CanDoubleJump && pLevel->IsOnGround(currentShape, false))
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
	const float maxGround_Offset = 50.0f;
	const float groundOffset = 15.0f;
	if (m_ActionState == ActionState::dying)
	{
		float test = currentShape.bottom - m_ShapeBeforeDying.bottom;
		if (currentShape.bottom - m_ShapeBeforeDying.bottom < maxGround_Offset)
		{
			currentShape.bottom += groundOffset * elapsedSec;
		}
		SetShape(currentShape);
		return;
	}

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
	if (!pLevel->IsOnGround(currentShape, false))
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
		if (m_IsFocusing)
		{
			srcRect.left = 8 * m_ClipWidth;
			srcRect.bottom = 5 * m_ClipHeight;
			m_ParticlesShape.left = GetAnimationFrame() * m_ParticlesShape.width / 5;
		}

		SetSourceRect(srcRect);
	}
}
