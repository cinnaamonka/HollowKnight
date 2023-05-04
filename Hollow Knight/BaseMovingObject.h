#pragma once

class Texture;

class BaseMovingObject
{
public:

	BaseMovingObject(const std::string &path, int framesNumber);
	BaseMovingObject(const BaseMovingObject& other) = delete;
	BaseMovingObject& operator=(const BaseMovingObject& other) = delete;
	BaseMovingObject(BaseMovingObject&& other) = delete;
	BaseMovingObject& operator=(BaseMovingObject&& other) = delete;
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

	int GetLifesAmount()
	{
		return m_LifesAmount;
	}
	void DecreaseLifesAmount()
	{
		m_LifesAmount--;
	}

	bool IsKilled()
	{
		return m_IsKilled;
	}

	void SetKilled(bool isKilled)
	{
		m_IsKilled = isKilled;
	}
	void SetShape(const Rectf& shape) {
		m_Shape = shape;
	}

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
	void SetFramesPerSec(const int time) {
		m_NrFramesPerSec = time;
	}
	int GetFramesPerSec()
	{
		return m_NrFramesPerSec;
	}

	int GetAnimationFrame() const {
		return m_AnimFrame;
	}

	void SetAnimationFrame(const int &currentFrame) {
		m_AnimFrame = currentFrame;
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

	int m_LifesAmount = 2;
	bool m_IsKilled;


};