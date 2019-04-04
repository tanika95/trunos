#pragma once
#include <vector>
#include "NetSwitch.hh"
#include "Settings.hh"
#include "Sla.hh"
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
	std::vector<uint32_t> switches() const;
	Settings getSettings() const;

	Vl &withRoute(const std::vector<VlSwitch> &r);
	Vl &withChangedRoute(const std::vector<VlSwitch> &r, uint32_t edge);
	Vl &stable();

private:
	uint32_t id;
	uint32_t sender;
	uint32_t receiver;
	Sla params;
	std::vector<VlSwitch> route;
	std::vector<VlSwitch> previous;
};

typedef std::vector<Vl> VlSet;
