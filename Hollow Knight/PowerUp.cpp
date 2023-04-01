#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "Game.h"

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type) :
	m_Type{ type }, m_RotSpeed{ 360.0f }, m_TextClip{}, m_Shape{}, m_Angle{}
{
	m_pTexture = new Texture{ "PowerUp.png" };
	m_TextClip.left = 0.0f;

	m_TextClip.bottom = m_Type == Type::green ? m_TextClip.bottom = m_pTexture->GetHeight() / 2 : m_TextClip.bottom = m_pTexture->GetHeight();

	m_TextClip.width = m_pTexture->GetWidth();
	m_TextClip.height = m_pTexture->GetHeight() / 2;

	m_Shape.center = center;
	m_Shape.radius = m_pTexture->GetWidth() / 2;
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
}

void PowerUp::Draw() const
{
	glPushMatrix();

	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);

	glRotatef(m_Angle, 0, 0, 1);

	glTranslatef(-m_Shape.radius, -m_Shape.radius, 0);

	m_pTexture->Draw(Point2f(0.0f, 0.0f), m_TextClip);

	glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	const float left = rect.left;
	const float right = rect.left + rect.width;
	const float bottom = rect.bottom;
	const float top = rect.bottom + rect.height;
	const float radius = m_Shape.radius;


	const Point2f center = m_Shape.center;

	const bool isRightOfLeftEdge = right > center.x - radius;
	const bool isLeftOfRightEdge = left < center.x + radius;
	const bool isAboveBottomEdge = top > center.y - radius;
	const bool isBelowTopEdge = bottom < center.y + radius;

	return isRightOfLeftEdge && isLeftOfRightEdge && isAboveBottomEdge && isBelowTopEdge;
}


