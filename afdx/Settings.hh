#pragma once
#include <vector>
#include <stdint.h>
#include "Common.hh"
#include "Sla.hh"
#include "VlSwitch.hh"

struct Settings {

	Settings(uint32_t id, Sla params, std::vector<VlSwitch> add, std::vector<VlSwitch> remove)
		: id(id), params(params), add(add), remove(remove)
	{}

	void log() const
	{
		LOG(INFO) << "------Settings----"<< id << "-----------";
		LOG(INFO) << "Delete";
		for (const auto &swtch : remove) {
			swtch.log();
		}
		LOG(INFO) << "Add";
		for (const auto &swtch : add) {
			swtch.log();
		}

	}

	uint32_t id;
	Sla params;
	std::vector<VlSwitch> add;
	std::vector<VlSwitch> remove;
};
