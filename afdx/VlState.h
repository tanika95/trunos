#pragma once
#include <stdint.h>

struct VlState {

	VlState(uint32_t id, bool broken, uint32_t sedge)
		: id(id), broken(broken), sport(sedge), brokenHeavier(false)
	{}

	VlState(uint32_t id, bool broken)
		: VlState(id, broken, 0)
	{}

	VlState()
		: VlState(0, false, 0)
	{}

	VlState heavierMarked()
	{
		VlState heavy;
		heavy.id = id;
		heavy.broken = broken;
		heavy.sedge = sedge;
		heavy.brokenHeavier = true;
		return heavy;
	}

	uint32_t id;
	bool broken;
	uint32_t sedge;
	bool brokenHeavier;
};
