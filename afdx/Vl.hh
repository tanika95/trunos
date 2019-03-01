#pragma once
#include <vector>
#include "Sla.hh"
#include "VlSwitch.hh"

class Vl {
public:
	Vl(uint32_t vid, uint32_t sid, uint32_t rid, Sla params);
	Vl();

	void log() const;

	double bw() const;
	uint32_t from() const;
	uint32_t to() const;

	Vl &withRoute(const std::vector<VlSwitch> &r);

private:
	uint32_t id [[maybe_unused]];
	uint32_t sender;
	uint32_t receiver;
	Sla params;
	std::vector<VlSwitch> route;
};

typedef std::vector<Vl> VlSet;

bool vlbwsort (Vl vl1, Vl vl2) { return vl1.bw() > vl2.bw(); }
