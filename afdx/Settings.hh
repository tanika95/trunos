#pragma once
#include <vector>
#include <stdint.h>
#include "Sla.hh"
#include "VlSwitch.hh"

struct Settings {

	Settings(uint32_t id, Sla params, std::vector<VlSwitch> add, std::vector<VlSwitch> remove)
		: id(id), params(params), add(add), remove(remove)
	{}

	uint32_t id;
	Sla params;
	std::vector<VlSwitch> add;
	std::vector<VlSwitch> remove;
};
