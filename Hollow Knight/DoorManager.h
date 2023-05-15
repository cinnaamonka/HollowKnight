#pragma once
class Avatar;
class Door;
#include "BaseManager.h"
class DoorManager final : public BaseManager<Door>
{

public:
	DoorManager();
	~DoorManager();

	DoorManager(const DoorManager&) = delete;
	DoorManager& operator=(const DoorManager&) = delete;
	DoorManager(DoorManager&&) = delete;
	DoorManager& operator=(DoorManager&&) = delete;

	void Update(float elapsedSec, Avatar* actor);


};


