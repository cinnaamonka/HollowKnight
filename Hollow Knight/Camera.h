#pragma once
class Camera
{
public:
	Camera(float width, float height);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Rectf& target, bool isShortDistance);
	Point2f GetPosition(const Rectf& target);

private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const Rectf& target);
	void Clamp(Point2f& bottomLeftPos);
	
};

