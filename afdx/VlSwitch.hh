#pragma once
#include <stdint.h>

struct VlSwitch {
	VlSwitch(uint32_t id, uint32_t sport, uint32_t rport)
		: id(id), sport(sport),  rport(rport)
	{}

	VlSwitch()
		: VlSwitch(0, 0, 0)
	{}

	bool operator !=(const VlSwitch &other) const
	{
		return id != other.id || sport != other.sport || rport != other.rport;
	}

	uint32_t id;
	uint32_t sport;
	uint32_t rport;
};
