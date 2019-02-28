#pragma once
#include <stdint.h>

struct VlSwitch {
	VlSwitch(uint32_t id, uint32_t rport, uint32_t sport)
		: id(id), rport(rport), sport(sport)
	{}

	VlSwitch()
		: VlSwitch(0, 0, 0)
	{}

	uint32_t id;
	uint32_t rport;
	uint32_t sport;
};
