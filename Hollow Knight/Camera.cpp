#include "pch.h"
#include "Camera.h"

Camera::Camera(float width, float height) :
	m_Width{ width }, m_Height{ height }, m_LevelBoundaries{ 0.0f, 0.0f, width, height }
{

}
Camera::~Camera()
{

}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target,bool isShortDistance)
{
	Point2f posCenter = Track(target);
	Clamp(posCenter);
	glTranslatef(-posCenter.x, -posCenter.y, 0);
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left + target.width / 2 - m_Width / 2,
		target.bottom + target.height / 2 - m_Height / 2);
}

void Camera::Clamp(Point2f& bottomLeftPos)
{
	bottomLeftPos.x = std::max(m_LevelBoundaries.left + 1.0f, 
		std::min(bottomLeftPos.x, m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width));

	bottomLeftPos.y = std::max(m_LevelBoundaries.bottom, 
		std::min(bottomLeftPos.y, m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height));
}

Point2f Camera::GetPosition(const Rectf& target) const
{
	return Track(target);
}
void Camera::Scale(const float scaleX, const float scaleY)
{
	glScalef(scaleX, scaleY, 0);
}

