#pragma once
class Avatar;
class Door;

class DoorManager final
{

public:
	DoorManager();
	~DoorManager();

	DoorManager(const DoorManager&) = delete;
	DoorManager& operator=(const DoorManager&) = delete;
	DoorManager(DoorManager&&) = delete;
	DoorManager& operator=(DoorManager&&) = delete;


	void Update(float elapsedSec, Avatar* actor);
	void Draw() const;
	void AddItem(Door* door);

private:

	std::vector<Door*> m_pItems;

};


