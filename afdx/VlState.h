#pragma once
#include <stdint.h>

struct VlState {
	VlState(uint32_t id, bool broken, uint32_t sedge)
		: id(id), broken(broken), sport(sedge)
	{}

	VlState(uint32_t id, bool broken)
		: VlState(id, broken, 0)
	{}

	VlState()
		: VlState(0, false, 0)
	{}

	uint32_t id;
	bool broken;
	uint32_t sedge;
};
