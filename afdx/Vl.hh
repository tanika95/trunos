#pragma once
#include <vector>
#include "Sla.hh"
#include "NetSwitch.hh"
#include "VlSwitch.hh"
#include "VlState.hh"

class Vl {
public:
	Vl(uint32_t vid, uint32_t sid, uint32_t rid, Sla params);
	Vl();

	void log() const;

	uint32_t getId() const;
	double bw() const;
	uint32_t from() const;
	uint32_t to() const;
	VlState state(const std::map<uint32_t, NetSwitch> &switches) const;

	Vl &withRoute(const std::vector<VlSwitch> &r);
	Vl &withChangedRoute(const std::vector<VlSwitch> &r, uint32_t edge);

private:
	uint32_t id [[maybe_unused]];
	uint32_t sender;
	uint32_t receiver;
	Sla params;
	std::vector<VlSwitch> route;
};

typedef std::vector<Vl> VlSet;
