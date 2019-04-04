#pragma once

#include <map>
#include "Common.hh"
#include "SwitchConnection.hh"
#include "Sla.hh"
#include "Vl.hh"
#include "VlSwitch.hh"

class Network {
public:
	Network();
	Network(uint8_t table);

	Network &withConnection(uint32_t id,
		runos::SwitchConnectionPtr connection);
	Network &withoutConnection(uint32_t id);
	void apply(const VlSet &vls);

private:
	of13::MeterMod addMeter(const Sla &params, uint32_t id);
	of13::FlowMod addFlow(const VlSwitch &sw, uint32_t id);
	of13::FlowMod deleteFlow(uint32_t id);

	uint8_t table;
	std::map<uint32_t, runos::SwitchConnectionPtr> connections;
};
