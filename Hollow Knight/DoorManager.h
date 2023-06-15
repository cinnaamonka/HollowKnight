#pragma once

#include "BaseManager.h"

class Avatar;
class Door;

class DoorManager final : public BaseManager<Door>
{

public:
	DoorManager();
	~DoorManager();

	DoorManager(const DoorManager&) = delete;
	DoorManager& operator=(const DoorManager&) = delete;
	DoorManager(DoorManager&&) = delete;
	DoorManager& operator=(DoorManager&&) = delete;

	void Update(float elapsedSec, Avatar* actor) const;
};


