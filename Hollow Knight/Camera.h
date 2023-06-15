#pragma once

class Camera final
{
public:

	Camera(float width, float height);
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;

	~Camera();

	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Rectf& target, bool isShortDistance) const;

	Point2f GetPosition(const Rectf& target) const
	{
		return Track(target);
	}

	void Scale(const float scaleX, const float scaleY, const Rectf& target) const;

private:

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;

private:

	float m_Width;
	float m_Height;

	Rectf m_LevelBoundaries;
};

