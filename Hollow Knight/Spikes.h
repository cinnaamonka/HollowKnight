#pragma once
class Spikes final
{
public:
	Spikes(const Rectf& spikesRect);

	Spikes(const Spikes& other) = delete;
	Spikes& operator=(const Spikes& other) = delete;
	Spikes(Spikes&& other) = delete;
	Spikes& operator=(Spikes&& other) = delete;
	~Spikes();

	bool IsOverlapping(const Rectf& rect) const;
private:

	Rectf m_Shape;

	
};

