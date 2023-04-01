#include "pch.h"
#include "Camera.h"
#include "utils.h"
#include "iostream"
Camera::Camera(float width, float height) :
	m_Width{ width }, m_Height{ height }, m_LevelBoundaries{ 0,0,width,height }
{

}
void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;

}
void Camera::Transform(const Rectf& target)
{

	Point2f posCenter
	{
		Track(target)
	};
	
    Clamp(posCenter);
	glTranslatef(-posCenter.x, -posCenter.y, 0);
	
}
Point2f Camera::Track(const Rectf& target)
{
	
	return Point2f(target.left + target.width/2 - m_Width/2 ,
		target.bottom + target.height/2 - m_Height/2 );
}
void Camera::Clamp(Point2f& bottomLeftPos)
{
	
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + 1.0f;
		
	}
	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	
	}
}