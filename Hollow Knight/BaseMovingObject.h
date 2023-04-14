#pragma once

class Texture;

class BaseMovingObject
{
public:

	BaseMovingObject(const std::string &path);
	virtual ~BaseMovingObject();

	const Texture* GetTexture() const {
		return m_pTexture;
	}

	Rectf GetShape()const
	{
		return m_Shape;
	}

	virtual void Draw() const = 0;
	
	void UpdateFrame(float elapsedSec, int numberFrames);

protected:

	void SetFramesNumber(const int framesAmount) {
		m_NrOfFrames = framesAmount;
	}

	int GetFramesNumber() const {
		return m_NrOfFrames;
	}

	float GetAnimationTime() const {
		return m_AnimTime;
	}

	void SetAnimationTime(const float &time) {
		m_AnimTime = time;
	}

	int GetAnimationFrame() const {
		return m_AnimFrame;
	}

	void SetAnimationFrame(const int &currentFrame) {
		m_AnimFrame = currentFrame;
	}

	void SetShape(const Rectf& shape) {
		m_Shape = shape;
	}
	
	void SetSourceRect(const Rectf& shape) {
		m_SourceRect = shape;
	}

	Rectf GetSourceRect() const {
		return m_SourceRect;
	}

private:

	Texture* m_pTexture;

	float m_AnimTime = 0.0f;

	int m_NrOfFrames = 0;
	int m_NrFramesPerSec = 1;
	int m_AnimFrame = 0;

	Rectf m_Shape;
	Rectf m_SourceRect;
};