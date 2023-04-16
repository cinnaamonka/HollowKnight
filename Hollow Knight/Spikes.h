#pragma once
class Spikes
{
public:
	Spikes(const Rectf& spikesRect);

	Spikes(const Spikes& other) = delete;
	Spikes& operator=(const Spikes& other) = delete;
	Spikes(Spikes&& other) = delete;
	Spikes& operator=(Spikes&& other) = delete;
	void Draw();
	~Spikes();
private:

	Rectf m_Shape;

	
};

